#ifndef ST1_VOICES_SINUSOIDAL_VOICE_HPP_
#define ST1_VOICES_SINUSOIDAL_VOICE_HPP_

#include <juce_audio_processors/juce_audio_processors.h>

namespace st1
{
    namespace voices
    {
        class SinusoidalVoice :
            public juce::SynthesiserVoice
        {
        public:
            SinusoidalVoice();

            bool canPlaySound(juce::SynthesiserSound *) override;
            void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
            void stopNote(float velocity, bool allowTailOff) override;
            void pitchWheelMoved(int newPitchWheelValue) override;
            void controllerMoved(int controllerNumber, int newControllerValue) override;
            void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;

        private:
            double velocity_{};
            double delta_{};
            double modulo_{};
        };
    }
}

#endif
