#include "OscillatorEditor.hpp"

#include <parameters/OscillatorAmplitudeParameter.hpp>
#include <parameters/OscillatorPulseWidthParameter.hpp>
#include <parameters/OscillatorPitchShiftParameter.hpp>
#include <parameters/OscillatorTypeParameter.hpp>

namespace st1
{
    namespace components
    {
        OscillatorEditor::OscillatorEditor(juce::AudioProcessorValueTreeState &s, juce::String const &name) :
            Component(name),
            oscillatorTypeDial_(name + ".wave_type", "Wave Type"),
            pitchShiftDial_(name + ".pitch_shift", "Pitch Shift"),
            pulseWidthDial_(name + ".pulse_width", "Pulse Width"),
            amplitudeDial_(name + ".amplitude", "Amplitude")
        {
            oscillatorTypeDial_.attach(s, OscillatorTypeParameter::identifier());
            pitchShiftDial_.attach(s, OscillatorPitchShiftParameter::identifier());
            pulseWidthDial_.attach(s, OscillatorPulseWidthParameter::identifier());
            amplitudeDial_.attach(s, OscillatorAmplitudeParameter::identifier());

            Component::addAndMakeVisible(oscillatorTypeDial_);
            Component::addAndMakeVisible(pitchShiftDial_);
            Component::addAndMakeVisible(pulseWidthDial_);
            Component::addAndMakeVisible(amplitudeDial_);
        }

        void OscillatorEditor::resized(void)
        {
            auto bounds = Component::getLocalBounds();
            auto width = bounds.getWidth();

            oscillatorTypeDial_.setBounds(bounds.removeFromLeft(width / 4));
            pitchShiftDial_.setBounds(bounds.removeFromLeft(width / 4));
            pulseWidthDial_.setBounds(bounds.removeFromLeft(width / 4));
            amplitudeDial_.setBounds(bounds.removeFromLeft(width / 4));
        }
    }
}
