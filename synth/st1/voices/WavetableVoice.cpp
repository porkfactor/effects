#include "WavetableVoice.hpp"

namespace st1
{
    namespace voices
    {
        WavetableVoice::WavetableVoice()
        {}

        bool WavetableVoice::canPlaySound(juce::SynthesiserSound *sound)
        {
            juce::ignoreUnused(sound);

            return true;
        }

        void WavetableVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
        {
            juce::ignoreUnused(midiNoteNumber);
            juce::ignoreUnused(velocity);
            juce::ignoreUnused(sound);
            juce::ignoreUnused(currentPitchWheelPosition);
        }

        void WavetableVoice::stopNote(float velocity, bool allowTailOff)
        {
            juce::ignoreUnused(velocity);
            juce::ignoreUnused(allowTailOff);
        }

        void WavetableVoice::pitchWheelMoved(int newPitchWheelValue)
        {
            juce::ignoreUnused(newPitchWheelValue);
        }

        void WavetableVoice::controllerMoved(int controllerNumber, int newControllerValue)
        {
            juce::ignoreUnused(controllerNumber);
            juce::ignoreUnused(newControllerValue);
        }

        void WavetableVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
        {
            juce::ignoreUnused(outputBuffer);
            juce::ignoreUnused(startSample);
            juce::ignoreUnused(numSamples);
        }
    }
}