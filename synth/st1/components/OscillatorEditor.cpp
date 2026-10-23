#include "OscillatorEditor.hpp"

namespace st1
{
    namespace gui
    {
        OscillatorEditor::OscillatorTypeControl::OscillatorTypeControl(juce::AudioProcessorValueTreeState &s, juce::String const &name) :
            ComboBox(name)
        {
            auto parameter = s.getParameter("OCOT");

            if (parameter)
            {
                ComboBox::addItemList(parameter->getAllValueStrings(), 1);
                attachment_.reset(new juce::ComboBoxParameterAttachment(*parameter, *this, s.undoManager));
            }
        }

        OscillatorEditor::OscillatorTypeControl::~OscillatorTypeControl()
        {}

        OscillatorEditor::PitchShiftControl::PitchShiftControl(juce::AudioProcessorValueTreeState &s, juce::String const &name) :
            Slider(name)
        {
            juce::Slider::setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
            juce::Slider::setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);

            auto parameter = s.getParameter("OFPS");

            if (parameter)
            {
                attachment_.reset(new juce::SliderParameterAttachment(*parameter, *this, s.undoManager));
            }
        }

        OscillatorEditor::PitchShiftControl::~PitchShiftControl()
        {}

        OscillatorEditor::PulseWidthControl::PulseWidthControl(juce::AudioProcessorValueTreeState &s, juce::String const &name) :
            Slider(name)
        {
            juce::Slider::setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
            juce::Slider::setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);

            auto parameter = s.getParameter("OFPW");

            if (parameter)
            {
                attachment_.reset(new juce::SliderParameterAttachment(*parameter, *this, s.undoManager));
            }
        }

        OscillatorEditor::PulseWidthControl::~PulseWidthControl()
        {}

        OscillatorEditor::OscillatorEditor(juce::AudioProcessorValueTreeState &s, juce::Component *p) :
            parent_(p),
            oscillatorTypeControl_(s, "Oscillator Type"),
            pitchShiftControl_(s, "Pitch Shift"),
            pulseWidthControl_(s, "Pulse Width")
        {
            this->addAndMakeVisible(oscillatorTypeControl_);
            this->addAndMakeVisible(pitchShiftControl_);
            this->addAndMakeVisible(pulseWidthControl_);

            parent_->addAndMakeVisible(*this);
        }

        void OscillatorEditor::resized(void)
        {
            auto bounds = Component::getBounds();

            oscillatorTypeControl_.setBounds(bounds.removeFromTop(30));
            pitchShiftControl_.setBounds(bounds.removeFromRight(bounds.getWidth() / 2));
            pulseWidthControl_.setBounds(bounds);
        }

        void OscillatorEditor::paint(juce::Graphics &g)
        {
            g.fillAll(Component::getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
        }
    }
}