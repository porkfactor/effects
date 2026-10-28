#include "AnalogDial.hpp"

namespace st1
{
    namespace components
    {
        AnalogDial::AnalogDial(juce::String const &name, juce::String const &label) :
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

        void AnalogDial::resized(void)
        {
            auto bounds = Component::getLocalBounds().withSizeKeepingCentre(110, 130);

            label_.setBounds(bounds.removeFromTop(20));
            slider_.setBounds(bounds);
        
        }

        void AnalogDial::attach(juce::RangedAudioParameter *parameter, juce::UndoManager *undoManager)
        {
            if (parameter)
            {
                attachment_.reset(new juce::SliderParameterAttachment(*parameter, slider_, undoManager));
            }
        }

        void AnalogDial::attach(juce::AudioProcessorValueTreeState &s, juce::StringRef parameterId)
        {
            attach(s.getParameter(parameterId), s.undoManager);
        }
    }
}
