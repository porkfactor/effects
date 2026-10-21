#ifndef ST1_VOICES_OSCILLATOR_VOICE_HPP_
#define ST1_VOICES_OSCILLATOR_VOICE_HPP_

#include <juce_audio_processors/juce_audio_processors.h>

namespace st1
{
    namespace voices
    {
        class OscillatorVoice :
            public juce::SynthesiserVoice
        {
        public:
            OscillatorVoice();
    
            bool canPlaySound(juce::SynthesiserSound *) override;
            void startNote(int, float, juce::SynthesiserSound *, int) override;
            void stopNote(float, bool) override;
            void pitchWheelMoved(int) override;
            void controllerMoved(int, int) override;
            void renderNextBlock(juce::AudioBuffer<float> &, int, int) override;

        private:
            void pitchWheelAdjust(int cents);

            double velocity_{};
            double delta_{};
            double modulo_{};
            double currentFrequency_{};
        };
    }
}

#endif
