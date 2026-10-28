#include "OscillatorVoice.hpp"

#include <parameters/OscillatorTypeParameter.hpp>
#include <parameters/OscillatorAmplitudeParameter.hpp>
#include <parameters/OscillatorPitchShiftParameter.hpp>
#include <parameters/OscillatorPulseWidthParameter.hpp>

namespace st1
{
    namespace voices
    {
        static juce::String const sawtooth("Sawtooth");
        static juce::String const sinusoid("Sinusoid");
        static juce::String const square("Square");
        static juce::String const triangle("Triangle");


        std::unique_ptr<juce::AudioProcessorParameterGroup> OscillatorVoice::parameters(juce::String const &name)
        {
            return std::make_unique<juce::AudioProcessorParameterGroup>(
                juce::String("OVPG"),
                name,
                juce::String("|"),
                OscillatorTypeParameter::create("oscillator_type"),
                OscillatorPitchShiftParameter::create("pitch_shift"),
                OscillatorPulseWidthParameter::create("pulse_width"),
                OscillatorAmplitudeParameter::create("amplitude")
            );
        }

        OscillatorVoice::OscillatorVoice(juce::AudioProcessorValueTreeState &s) :
            juce::AudioProcessorValueTreeState::Listener(),
            state_(s),
            envelope_(s)
        {
            state_.addParameterListener(OscillatorTypeParameter::identifier(), this);
            state_.addParameterListener(OscillatorPitchShiftParameter::identifier(), this);
            state_.addParameterListener(OscillatorPulseWidthParameter::identifier(), this);
            state_.addParameterListener(OscillatorAmplitudeParameter::identifier(), this);
        }

        OscillatorVoice::~OscillatorVoice()
        {
            state_.removeParameterListener(OscillatorTypeParameter::identifier(), this);
            state_.removeParameterListener(OscillatorPitchShiftParameter::identifier(), this);
            state_.removeParameterListener(OscillatorPulseWidthParameter::identifier(), this);
            state_.removeParameterListener(OscillatorAmplitudeParameter::identifier(), this);
        }

        void OscillatorVoice::parameterChanged(juce::String const &parameterID, float newValue)
        {
            juce::ignoreUnused(parameterID);
            juce::ignoreUnused(newValue);
        }

        bool OscillatorVoice::canPlaySound(juce::SynthesiserSound *sound)
        {
            juce::ignoreUnused(sound);

            return true;
        }

        void OscillatorVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
        {
            juce::ignoreUnused(sound);
            juce::ignoreUnused(velocity);

            oscillator_.startNote(SynthesiserVoice::getSampleRate(), juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
            envelope_.startNote();
            velocity_ = static_cast<double>(velocity);

            pitchWheelMoved(currentPitchWheelPosition);
        }

        void OscillatorVoice::stopNote(float velocity, bool allowTailOff)
        {
            juce::ignoreUnused(velocity);
            juce::ignoreUnused(allowTailOff);

            if (allowTailOff)
            {
                envelope_.stopNote();
                SynthesiserVoice::clearCurrentNote();
                reset();
            }
            else
            {
                SynthesiserVoice::clearCurrentNote();
                reset();
            }
        }

        void OscillatorVoice::pitchWheelMoved(int newPitchWheelValue)
        {
            if (newPitchWheelValue == 0x2000)
            {
                oscillator_.pitchShift(1.0);
                // delta_ = pitchFrequency_ / SynthesiserVoice::getSampleRate();
            }
            else
            {
                double semitones = static_cast<double>(newPitchWheelValue - INT32_C(0x2000)) / 4096.0;
                double frequency_adjust = std::exp2(static_cast<double>(semitones) / 12.0);

                oscillator_.pitchShift(frequency_adjust);
                // delta_ = (pitchFrequency_ * frequency_adjust) / SynthesiserVoice::getSampleRate();
            }
        }

        void OscillatorVoice::controllerMoved(int controllerNumber, int newControllerValue)
        {
            juce::ignoreUnused(controllerNumber);
            juce::ignoreUnused(newControllerValue);
        }

        void OscillatorVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
        {
            if (velocity_ != 0.0)
            {
                int const numChannels = outputBuffer.getNumChannels();
                int sampleIdx{};
                float currentSample = 0.0f;

                do
                {
                    int channelIdx{};

                    currentSample = static_cast<float>(envelope_.process() * oscillator_.generate() * velocity_);

                    do
                    {
                        outputBuffer.addSample(channelIdx, startSample + sampleIdx, currentSample);
                        ++channelIdx;
                    } while(channelIdx < numChannels);
    
                    ++sampleIdx;
                } while (sampleIdx < numSamples);
            }

            if (!envelope_.active())
                clearCurrentNote();
        }

        void OscillatorVoice::reset(void)
        {
            velocity_ = 0.0;
            envelope_.reset();
            oscillator_.reset();
        }
    }
}