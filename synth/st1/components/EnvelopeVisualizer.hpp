#ifndef ST1_COMPONENTS_ENVELOPE_VISUALIZER_HPP_
#define ST1_COMPONENTS_ENVELOPE_VISUALIZER_HPP_

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

namespace st1
{
    namespace components
    {
        template<typename _Type>
        struct EnvelopeSegment
        {
        public:
            using value_type = _Type;

            enum line_style
            {
                linear,
                quadratic,
                cubic,
            };

            EnvelopeSegment(juce::Point<value_type> const &s, juce::Point<value_type> const &e) :
                style_{linear},
                start_{s.x, 1.0f - s.y},
                end_{e.x, 1.0f - e.y},
                control1_{0.0f, 1.0f},
                control2_{0.0f, 1.0f}
            {}

            EnvelopeSegment(juce::Point<value_type> const &s, juce::Point<value_type> const &a, juce::Point<value_type> const &e) :
                style_(quadratic),
                start_{s.x, 1.0f - s.y},
                end_{e.x, 1.0f - e.y},
                control1_(a.x, 1.0f - a.y),
                control2_{0.0f, 1.0f}
            {}

            EnvelopeSegment(juce::Point<value_type> const &s, juce::Point<value_type> const &a, juce::Point<value_type> const &b, juce::Point<value_type> const &e) :
                style_{cubic},
                start_{s.x, 1.0f - s.y},
                end_{e.x, 1.0f - e.y},
                control1_(a.x, 1.0f - a.y),
                control2_(b.x, 1.0f - b.y)
            {}

            inline line_style style() const noexcept
            {
                return style_;
            }

            inline juce::Point<value_type> const &start() const noexcept
            {
                return start_;
            }

            inline juce::Point<value_type> const &control1() const noexcept
            {
                return control1_;
            }

            inline juce::Point<value_type> const &control2() const noexcept
            {
                return control2_;
            }

            inline juce::Point<value_type> const &end() const noexcept
            {
                return end_;
            }

        private:
            enum line_style style_;
            juce::Point<value_type> start_;
            juce::Point<value_type> end_;
            juce::Point<value_type> control1_;
            juce::Point<value_type> control2_;
        };

        class EnvelopeVisualizer :
            public juce::Component,
            public juce::AudioProcessorValueTreeState::Listener,
            private juce::AsyncUpdater
        {
        public:
            static constexpr std::size_t npos = static_cast<std::size_t>(-1);
            EnvelopeVisualizer(juce::AudioProcessorValueTreeState &, juce::String const &);
            ~EnvelopeVisualizer() override;

            void mouseEnter(juce::MouseEvent const &e) override;
            void mouseExit(juce::MouseEvent const &e) override;

            void mouseDown(juce::MouseEvent const &e) override;
            void mouseUp(juce::MouseEvent const &e) override;
            void mouseDrag(juce::MouseEvent const &e) override;
            void mouseMove(juce::MouseEvent const &e) override;

            void paint(juce::Graphics &) override;

        private:
            void calculatePaths();
            void handleAsyncUpdate() override;
            void parameterChanged(juce::String const &parameterID, float newValue) override;

            juce::AudioProcessorValueTreeState &state_;
            juce::RangedAudioParameter *attackParameter_;
            juce::RangedAudioParameter *decayParamter_;
            juce::RangedAudioParameter *sustainParameter_;
            juce::RangedAudioParameter *releaseParameter_;

            std::vector<EnvelopeSegment<float>> segments_;
            std::size_t selected_ = npos;
            bool grabbed_ = false;
    
            const float anchorRadius = 6.0f;
            const float grabTolerance = 15.0f;
        };
    }
}


#endif
