#include "WavetableSound.hpp"

namespace st1
{
    namespace voices
    {
        static std::size_t constexpr table_size = 4096;

        struct harmonic { double order; double weight; };

        WavetableSound::WavetableSound()
        {
            data_.setSize(1, static_cast<int>(table_size + 1));
            data_.clear();

            double *samples = data_.getWritePointer(0);

            struct harmonic const harmonics[] =
            {
            #if 0
                { 1, 0.50, },
                { 3, 0.10, },
                { 5, 0.05, },
                { 6, 0.125,},
                { 7, 0.09, },
                { 9, 0.005, },
                { 13, 0.002, },
                { 15, 0.001, },
            #else
                // { 1.0, 1.0 },
                { 1.0, 0.50 },
                { 1.5, 0.05 },
                { 3.0, 0.10 },
                { 5.0, 0.05 },
                { 6.0, 0.125 },
            #endif
            };

            for (auto harmonic = 0; harmonic < juce::numElementsInArray(harmonics); ++harmonic)
            {
                double angleDelta = (juce::MathConstants<double>::twoPi / static_cast<double>(table_size)) * harmonics[harmonic].order;
                double currentAngle = 0.0;

                for (unsigned int i = 0; i < table_size; ++i)
                {
                    double sample = std::sin(currentAngle);

                    samples[i] += sample * harmonics[harmonic].weight;
                    currentAngle += angleDelta;
                }
            }

            samples[table_size] = samples[0];
        }

        double const *WavetableSound::data() const noexcept
        {
            return data_.getReadPointer(0);
        }

        std::size_t WavetableSound::size() const noexcept
        {
            return table_size;
        }

        bool WavetableSound::appliesToNote(int midiNoteNumber)
        {
            juce::ignoreUnused(midiNoteNumber);

            return true;
        }

        bool WavetableSound::appliesToChannel(int midiChannel)
        {
            juce::ignoreUnused(midiChannel);

            return true;
        }
    }
}
