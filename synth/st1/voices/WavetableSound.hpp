#ifndef ST1_VOICES_WAVETABLE_SOUND_HPP_
#define ST1_VOICES_WAVETABLE_SOUND_HPP_

#include <juce_audio_processors/juce_audio_processors.h>

namespace st1
{
    namespace voices
    {
        class WavetableSound :
            public juce::SynthesiserSound
        {
        public:
            WavetableSound();

            bool appliesToNote(int) override;
            bool appliesToChannel(int) override;

            static inline WavetableSound *upcast(juce::SynthesiserSound *sound)
            {
                return static_cast<WavetableSound *>(sound);
            }

            double const *data() const noexcept;
            std::size_t size() const noexcept;

        private:
            juce::AudioBuffer<double> data_;
        };
    }
}

#endif
