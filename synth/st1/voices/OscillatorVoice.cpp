#include "OscillatorVoice.hpp"

namespace st1
{
    namespace voices
    {
        OscillatorVoice::OscillatorVoice()
        {}
    
        bool OscillatorVoice::canPlaySound(juce::SynthesiserSound *sound)
        {
            juce::ignoreUnused(sound);

            return true;
        }

        void OscillatorVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
        {
            juce::ignoreUnused(sound);

            velocity_ = static_cast<double>(velocity);
            currentFrequency_ = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);

            pitchWheelAdjust(currentPitchWheelPosition);
        }

        void OscillatorVoice::stopNote(float velocity, bool allowTailOff)
        {
            juce::ignoreUnused(velocity);
            juce::ignoreUnused(allowTailOff);

            SynthesiserVoice::clearCurrentNote();
            currentFrequency_ = 0.0;
            delta_ = 0.0;
        }

        void OscillatorVoice::pitchWheelMoved(int newPitchWheelValue)
        {
            pitchWheelAdjust(newPitchWheelValue);
        }

        void OscillatorVoice::controllerMoved(int controllerNumber, int newControllerValue)
        {
            juce::ignoreUnused(controllerNumber);
            juce::ignoreUnused(newControllerValue);
        }

        void OscillatorVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
        {
            if (currentFrequency_ != 0.0)
            {
                int const numChannels = outputBuffer.getNumChannels();
                int sampleIdx{};
                float currentSample = .0f;
    
                do
                {
                    int channelIdx{};
    
                    currentSample = static_cast<float>(velocity_ * ((modulo_ * 2.0) - 1.0));
    
                    modulo_ += delta_;
    
                    if (modulo_ > 1.0)
                        modulo_ -= 1.0;
    
                    do
                    {
                        outputBuffer.addSample(channelIdx, startSample + sampleIdx, currentSample);
                        ++channelIdx;
                    } while(channelIdx < numChannels);
    
                    ++sampleIdx;
                } while (sampleIdx < numSamples);
            }
        }

        void OscillatorVoice::pitchWheelAdjust(int pitchWheelValue)
        {
            if (pitchWheelValue == 0x2000)
            {
                delta_ = currentFrequency_ / SynthesiserVoice::getSampleRate();
            }
            else
            {
                double semitones = static_cast<double>(pitchWheelValue - INT32_C(0x2000)) / 4096.0;
                double frequency_adjust = std::exp2(static_cast<double>(semitones) / 12.0);

                delta_ = (currentFrequency_ * frequency_adjust) / SynthesiserVoice::getSampleRate();
            }
        }
    }
}