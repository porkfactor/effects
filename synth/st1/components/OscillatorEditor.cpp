#include "OscillatorEditor.hpp"

namespace st1
{
    namespace components
    {
        OscillatorEditor::OscillatorEditor(juce::AudioProcessorValueTreeState &s, juce::String const &name) :
            Component(name),
            oscillatorTypeCombo_(s.getParameter("OCOT"), name + ".oscillator_type", s.undoManager),
            pitchShiftDial_(name + ".pitch_shift", "Pitch Shift"),
            pulseWidthDial_(name + ".pulse_width", "Pulse Width"),
            amplitudeDial_(name + ".amplitude", "Amplitude")
        {
            pitchShiftDial_.attach(s, "OFPS");
            pulseWidthDial_.attach(s, "OFPW");
            amplitudeDial_.attach(s, "OFAM");

            Component::addAndMakeVisible(oscillatorTypeCombo_);
            Component::addAndMakeVisible(pitchShiftDial_);
            Component::addAndMakeVisible(pulseWidthDial_);
            Component::addAndMakeVisible(amplitudeDial_);
        }

        void OscillatorEditor::resized(void)
        {
            auto bounds = Component::getLocalBounds();
            auto width = bounds.getWidth();

            oscillatorTypeCombo_.setBounds(bounds.removeFromTop(30));

            pitchShiftDial_.setBounds(bounds.removeFromLeft(width / 3));
            pulseWidthDial_.setBounds(bounds.removeFromLeft(width / 3));
            amplitudeDial_.setBounds(bounds.removeFromLeft(width / 3));
        }
    }
}
