#ifndef ST1_VOICES_WAVETABLE_VOICE_HPP_
#define ST1_VOICES_WAVETABLE_VOICE_HPP_

#include <juce_audio_processors/juce_audio_processors.h>

namespace st1
{
    namespace voices
    {
        class WavetableSound;

        class WavetableVoice : public juce::SynthesiserVoice
        {
        public:
            WavetableVoice();

            bool canPlaySound(juce::SynthesiserSound *) override;
            void startNote(int, float, juce::SynthesiserSound *, int) override;
            void stopNote(float, bool) override;
            void pitchWheelMoved(int) override;
            void controllerMoved(int, int) override;
            void renderNextBlock(juce::AudioBuffer<float> &, int, int) override;

        private:
            double nextSample(double const *, double);

            WavetableSound *sound_{};
            double velocity_{0.0};
            double readIndex_{0.0};
            double delta_{0.0};
            double phase_modulation_{0.0};
        };
    }
}

#endif
