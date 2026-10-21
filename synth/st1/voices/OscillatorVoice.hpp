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
            enum class wave_type
            {
                sinusoid,
                sawtooth,
                triangle,
                square,
            };

            OscillatorVoice();
    
            bool canPlaySound(juce::SynthesiserSound *) override;
            void startNote(int, float, juce::SynthesiserSound *, int) override;
            void stopNote(float, bool) override;
            void pitchWheelMoved(int) override;
            void controllerMoved(int, int) override;
            void renderNextBlock(juce::AudioBuffer<float> &, int, int) override;

        private:
            double nextSample();
            void pitchWheelAdjust(int);

            void reset();

            double velocity_{};
            double delta_{};
            double modulo_{};
            double tailOff_{};
            double pitchFrequency_{};
            double pulseWidth_{0.5};
            enum wave_type type_{wave_type::sinusoid};
        };
    }
}

#endif
