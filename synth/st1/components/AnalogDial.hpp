#ifndef ST1_COMPONENTS_ANALOG_DIAL_HPP_
#define ST1_COMPONENTS_ANALOG_DIAL_HPP_

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

namespace st1
{
    namespace components
    {
        class AnalogDial :
            public juce::Slider
        {
        public:
            AnalogDial(juce::String const &name) :
                juce::Slider(name)
            {
                juce::Slider::setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
                juce::Slider::setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
            }

        private:
        };

        class AttachedAnalogDial :
            public AnalogDial
        {
        public:
            AttachedAnalogDial(juce::RangedAudioParameter *parameter, juce::String const &name, juce::UndoManager *undoManager = nullptr) :
                AnalogDial(name)
            {
                if (parameter)
                {
                    attachment_.reset(new juce::SliderParameterAttachment(*parameter, *this, undoManager));
                }
            }

            ~AttachedAnalogDial() override
            {}

        private:
            std::unique_ptr<juce::SliderParameterAttachment> attachment_;
        };
    }
}

#endif
