#ifndef ST1_VOICES_OSCILLATOR_VOICE_HPP_
#define ST1_VOICES_OSCILLATOR_VOICE_HPP_

#include <juce_audio_processors/juce_audio_processors.h>

#include <filters/EnvelopeGenerator.hpp>

namespace st1
{
    namespace voices
    {
        /**
         * TODO: move this to DSP following refactor
         */
        class Oscillator
        {
        public:
            enum class wave_type
            {
                sinusoid,
                sawtooth,
                triangle,
                square,
            };

            void startNote(double sampleRate, double pitchFrequency)
            {
                pitchFrequency_ = pitchFrequency;
                delta_ = pitchFrequency / sampleRate;
            }

            void reset(void)
            {

            }

            void pitchShift(double cents)
            {
                pitchShift_ = cents;
            }

            double generate(void)
            {
                double sample;

                switch (type_)
                {
                case wave_type::sinusoid:
                    sample = std::sin(modulo_ * 2.0 * M_PI);
                    break;
                case wave_type::sawtooth:
                    sample = (modulo_ * 2.0) - 1.0;
                    break;
                case wave_type::square:
                    sample = (modulo_ > pulseWidth_) ? 1.0 : -1.0;
                    break;
                case wave_type::triangle:
                    sample = (2.0 * abs((2.0 * modulo_) - 1.0)) - 1.0;
                    break;
                }

                modulo_ += (delta_ * pitchShift_);

                if (modulo_ > 1.0)
                    modulo_ -= 1.0;

                return sample;
            }

        private:
            double delta_{};
            double modulo_{};
            double pitchFrequency_{};
            double pulseWidth_{0.5};
            double pitchShift_{0.0};
            enum wave_type type_{wave_type::sinusoid};
        };

        class OscillatorVoice :
            public juce::SynthesiserVoice,
            public juce::AudioProcessorValueTreeState::Listener
        {
        public:
            OscillatorVoice(juce::AudioProcessorValueTreeState &);
            ~OscillatorVoice() override;
    
            void parameterChanged(juce::String const &parameterID, float newValue) override;

            bool canPlaySound(juce::SynthesiserSound *) override;
            void startNote(int, float, juce::SynthesiserSound *, int) override;
            void stopNote(float, bool) override;
            void pitchWheelMoved(int) override;
            void controllerMoved(int, int) override;
            void renderNextBlock(juce::AudioBuffer<float> &, int, int) override;

            static std::unique_ptr<juce::AudioProcessorParameterGroup> parameters(juce::String const &);

        private:
            void reset();

            juce::AudioProcessorValueTreeState &state_;
            Oscillator oscillator_;
            filters::EnvelopeGenerator envelope_;
            double velocity_;
        };
    }
}

#endif
