#ifndef ST1_COMPONENTS_ENVELOPE_VISUALIZER_HPP_
#define ST1_COMPONENTS_ENVELOPE_VISUALIZER_HPP_

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

namespace st1
{
    namespace gui
    {
        template<typename _Unit>
        class EnvelopeSegment
        {
        public:
            using value_type = _Unit;

            enum line_type
            {
                linear,
                quadratic,
            };

            EnvelopeSegment(value_type, value_type);
            EnvelopeSegment(value_type, value_type, value_type, value_type);

            inline juce::Point<value_type> const &start() const noexcept
            {
                return start_;
            }

            inline juce::Point<value_type> const &end() const noexcept
            {
                return end_;
            }

            inline juce::Point<value_type> const &start() const noexcept
            {
                return intercept_;
            }

        private:
            juce::Point<value_type> start_;
            juce::Point<value_type> end_;
            juce::Point<value_type> intercept_;
            line_type type_{line_type::linear};
        };

        class EnvelopeVisualizer :
            public juce::Component
        {
        public:
            static constexpr std::size_t npos = static_cast<std::size_t>(-1);
            EnvelopeVisualizer();

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
            const float grabTolerance = 15.0f; // Click target radius padding
        };
    }
}


#endif
