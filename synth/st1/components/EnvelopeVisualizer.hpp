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
            using value_type = _Type;

            EnvelopeSegment(value_type, value_type);

            inline juce::Point<value_type> start() const noexcept
            {
                return juce::Point<value_type>{};
            }

            inline juce::Point<value_type> end() const noexcept
            {
                return juce::Point<value_type>{};
            }
        };

        class EnvelopeVisualizer :
            public juce::Component
        {
        public:
            static constexpr std::size_t npos = static_cast<std::size_t>(-1);
            EnvelopeVisualizer(juce::AudioProcessorValueTreeState &, juce::String const &);

            void mouseEnter(juce::MouseEvent const &e) override;
            void mouseExit(juce::MouseEvent const &e) override;

            void mouseDown(juce::MouseEvent const &e) override;
            void mouseUp(juce::MouseEvent const &e) override;
            void mouseDrag(juce::MouseEvent const &e) override;
            void mouseMove(juce::MouseEvent const &e) override;

            void paint(juce::Graphics &) override;

        private:
            std::vector<EnvelopeSegment<float>> segments_;
            std::size_t selected_ = npos;
            bool grabbed_ = false;
    
            const float anchorRadius = 6.0f;
            const float grabTolerance = 15.0f;
        };
    }
}


#endif
