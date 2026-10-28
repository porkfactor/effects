#ifndef ST1_FILTERS_ENVELOPE_GENERATOR_HPP_
#define ST1_FILTERS_ENVELOPE_GENERATOR_HPP_

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_basics/juce_audio_basics.h>

namespace st1
{
    namespace filters
    {
        class Envelope
        {
        public:
            enum class envelope_state
            {
                initial,
                attack,
                decay,
                sustain,
                release,
                shutdown,
            };

            bool active() const noexcept
            {
                return state_ != envelope_state::initial;
            }

            void set_mode(void)
            {
                if (true) /* analog */
                {
                    attack_.configure(sample_rate_, std::exp(1.5), 1.0);
                    decay_.configure(sample_rate_, std::exp(-4.95), sustain_level_);
                    sustain_.configure(sample_rate_, 0.0, sustain_level_);
                    release_.configure(sample_rate_, std::exp(-4.95), -sustain_level_);
                }
                else
                {
                    attack_.configure(sample_rate_, 0.99999, 1.0);
                    decay_.configure(sample_rate_, std::exp(-11.05), sustain_level_);
                    sustain_.configure(sample_rate_, 0.0, sustain_level_);
                    release_.configure(sample_rate_, std::exp(-11.05), -sustain_level_);
                }
            }

            void reset(void)
            {
                state_ = envelope_state::initial;

                if (reset_)
                {
                    output_ = 0.0;
                }
            }

            void start(void)
            {
                switch (state_)
                {
                case envelope_state::initial:
                case envelope_state::release:
                    reset();
                    state_ = envelope_state::attack;
                    break;
                case envelope_state::attack:
                case envelope_state::decay:
                case envelope_state::sustain:
                case envelope_state::shutdown:
                    break;
                }
            }

            void stop(void)
            {
                switch (state_)
                {
                case envelope_state::attack:
                case envelope_state::decay:
                case envelope_state::sustain:
                    state_ = envelope_state::release;
                    break;
                case envelope_state::initial:
                case envelope_state::release:
                case envelope_state::shutdown:
                    break;
                }
            }

            void shutdown(void)
            {
                shutdown_.configure(sample_rate_, output_);

                state_ = envelope_state::shutdown;
            }

            double generate(void)
            {
                switch (state_)
                {
                case envelope_state::initial:
                    break;

                case envelope_state::attack:
                    output_ = attack_.perform(output_);

                    if (output_ >= 1.0)
                    {
                        state_ = envelope_state::decay;
                    }
                    break;

                case envelope_state::decay:
                    output_ = decay_.perform(output_);

                    if  (output_ <= sustain_level_)
                    {
                        state_ = envelope_state::sustain;
                    }
                    break;

                case envelope_state::sustain:
                    output_ = sustain_level_;
                    break;

                case envelope_state::release:
                    output_ = release_.perform(output_);

                    if (output_ <= 0.0)
                    {
                        output_ = 0.0;
                        state_ = envelope_state::initial;
                    }
                    break;

                case envelope_state::shutdown:
                    if (reset_)
                    {
                        output_ = shutdown_.perform(output_);
    
                        if (output_ <= 0.0)
                        {
                            state_ = envelope_state::initial;
                            output_ = 0.0;
                        }
                    }
                    else
                    {
                        state_ = envelope_state::initial;
                    }
                    break;
                }

                return output_;
            }

        private:
            struct attack
            {
                void configure(double sample_rate, double tco, double distance)
                {
                    double sample_count = sample_rate * (duration_ / 1000.0);
                    coefficient_ = std::exp(-std::log((1.0 + tco) / tco) / sample_count);
                    offset_ = (distance + tco) * (1.0 - coefficient_);
                }

                inline double perform(double x)
                {
                    return offset_ + (x * coefficient_);
                }

                double duration_;
                double offset_;
                double coefficient_;
            };

            struct decay
            {
                void configure(double sample_rate, double tco, double distance)
                {
                    double sample_count = sample_rate * (duration_ / 1000.0);
                    coefficient_ = std::exp(-std::log((1.0 + tco) / tco) / sample_count);
                    offset_ = (distance - tco) * (1.0 - coefficient_);
                }

                inline double perform(double x)
                {
                    return offset_ + (x * coefficient_);
                }

                double duration_;
                double offset_;
                double coefficient_;
            };

            struct sustain
            {
            public:
                void configure(double sample_rate, double tco, double distance)
                {
                    (void)sample_rate;
                    (void)tco;
                    (void)distance;

                    level_ = distance;
                }

                inline double perform(double x)
                {
                    return level_ * x;
                }

                inline double level() const noexcept
                {
                    return level_;
                }

            private:
                double level_;
            };

            struct release
            {
                void configure(double sample_rate, double tco, double distance)
                {
                    (void)distance;

                    double sample_count = sample_rate * (duration_ / 1000.0);
                    coefficient_ = std::exp(-std::log((1.0 + tco) / tco) / sample_count);
                    offset_ = (-tco) * (1.0 - coefficient_);
                }

                inline double perform(double x)
                {
                    return offset_ + (x * coefficient_);
                }

                double duration_;
                double offset_;
                double coefficient_;
            };

            struct shutdown
            {
                void configure(double sample_rate, double distance)
                {
                    increment_ = -(1000.0 * distance) / duration_ / sample_rate;
                }

                inline double perform(double x)
                {
                    return x + increment_;
                }

                double duration_;
                double increment_;
            };

            envelope_state state_{envelope_state::initial};

            double sample_rate_{};
            double output_{};
            double sustain_level_{};

            struct attack attack_;
            struct decay decay_;
            struct sustain sustain_;
            struct release release_;
            struct shutdown shutdown_;

            bool reset_{false};
        };

        class EnvelopeGenerator :
            public juce::AudioProcessorValueTreeState::Listener
        {
        public:
            EnvelopeGenerator(juce::AudioProcessorValueTreeState &s);
            ~EnvelopeGenerator() override;

            static std::unique_ptr<juce::AudioProcessorParameterGroup> parameters(juce::String const &);

            void startNote(void) noexcept
            {
                envelope_.start();
            }

            void stopNote(void) noexcept
            {
                envelope_.stop();
            }

            void reset(void) noexcept
            {
                envelope_.reset();
            }

            bool active(void) const noexcept
            {
                // return envelope_.active();
                return true;
            }

            inline double process(void) noexcept
            {
                // return envelope_.generate();
                return 1.0;
            }

        private:
            void parameterChanged(juce::String const &parameterID, float newValue) override;

            juce::AudioProcessorValueTreeState &state_;
            Envelope envelope_;
        };
    }
}

#endif
