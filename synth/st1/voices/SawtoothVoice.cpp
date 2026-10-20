#include "SawtoothVoice.hpp"

namespace st1
{
    namespace voices
    {
        SawtoothVoice::SawtoothVoice()
        {}
    
        bool SawtoothVoice::canPlaySound(juce::SynthesiserSound *sound)
        {
            juce::ignoreUnused(sound);

            return true;
        }

        void SawtoothVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
        {
            juce::ignoreUnused(sound);
            juce::ignoreUnused(currentPitchWheelPosition);

            velocity_ = static_cast<double>(velocity);
            delta_ = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) / SynthesiserVoice::getSampleRate();
        }

        void SawtoothVoice::stopNote(float velocity, bool allowTailOff)
        {
            juce::ignoreUnused(velocity);
            juce::ignoreUnused(allowTailOff);

            SynthesiserVoice::clearCurrentNote();
            delta_ = 0.0;
        }

        void SawtoothVoice::pitchWheelMoved(int newPitchWheelValue)
        {
            juce::ignoreUnused(newPitchWheelValue);
        }

        void SawtoothVoice::controllerMoved(int controllerNumber, int newControllerValue)
        {
            juce::ignoreUnused(controllerNumber);
            juce::ignoreUnused(newControllerValue);
        }

        void SawtoothVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
        {
            if (delta_ != 0.0)
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
    }
}