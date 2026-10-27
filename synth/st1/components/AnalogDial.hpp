#ifndef ST1_COMPONENTS_ANALOG_DIAL_HPP_
#define ST1_COMPONENTS_ANALOG_DIAL_HPP_

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

namespace st1
{
    namespace components
    {
        class AnalogDial :
            public juce::Component
        {
        public:
            AnalogDial(juce::String const &name, juce::String const &label = juce::String()) :
                juce::Component(name),
                slider_(name + ".slider"),
                label_(name + ".label", label)
            {
                slider_.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
                slider_.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
                label_.setJustificationType(juce::Justification::centred);

                Component::addAndMakeVisible(slider_);
                Component::addAndMakeVisible(label_);
            }

            void resized(void) override
            {
                auto bounds = Component::getLocalBounds();

                label_.setBounds(bounds.removeFromTop(20));
                slider_.setBounds(bounds);
            }

            void attach(juce::RangedAudioParameter *parameter, juce::UndoManager *undoManager = nullptr)
            {
                if (parameter)
                {
                    attachment_.reset(new juce::SliderParameterAttachment(*parameter, slider_, undoManager));
                }
            }

            void attach(juce::AudioProcessorValueTreeState &s, juce::StringRef parameterId)
            {
                attach(s.getParameter(parameterId), s.undoManager);
            }

        private:
            juce::Slider slider_;
            juce::Label label_;
            std::unique_ptr<juce::SliderParameterAttachment> attachment_;
        };
    }
}

#endif
