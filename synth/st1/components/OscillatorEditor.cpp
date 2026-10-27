#include "OscillatorEditor.hpp"

namespace st1
{
    namespace components
    {
        OscillatorEditor::OscillatorEditor(juce::AudioProcessorValueTreeState &s, juce::String const &name) :
            Component(name),
            oscillatorTypeCombo_(s.getParameter("OCOT"), "Oscillator Type"),
            pitchShiftDial_(s.getParameter("OFPS"), "Pitch Shift"),
            pulseWidthDial_(s.getParameter("OFPW"), "Pulse Width"),
            amplitudeDial_(s.getParameter("OFAM"), "Amplitude")
        {
            Component::addAndMakeVisible(oscillatorTypeCombo_);
            Component::addAndMakeVisible(pitchShiftDial_);
            Component::addAndMakeVisible(pulseWidthDial_);
            Component::addAndMakeVisible(amplitudeDial_);
        }

        void OscillatorEditor::resized(void)
        {
            auto bounds = Component::getLocalBounds();

            oscillatorTypeCombo_.setBounds(bounds.removeFromTop(30));
            pitchShiftDial_.setBounds(bounds.removeFromLeft(bounds.getWidth() / 3));
            pulseWidthDial_.setBounds(bounds.removeFromLeft(bounds.getWidth() / 2));
            amplitudeDial_.setBounds(bounds);
        }

        void OscillatorEditor::paint(juce::Graphics &g)
        {
            g.fillAll(Component::getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
        }
    }
}
