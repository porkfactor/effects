#include "WavetableVoice.hpp"
#include "WavetableSound.hpp"

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
            juce::ignoreUnused(currentPitchWheelPosition);

            sound_ = WavetableSound::upcast(sound);
            velocity_ = static_cast<double>(velocity);
            delta_ = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) / SynthesiserVoice::getSampleRate();
        }

        void WavetableVoice::stopNote(float velocity, bool allowTailOff)
        {
            juce::ignoreUnused(velocity);
            juce::ignoreUnused(allowTailOff);

            SynthesiserVoice::clearCurrentNote();

            velocity_ = 0.0;
            delta_ = 0.0;
            readIndex_ = 0.0;
            sound_ = nullptr;
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

        inline double linear_interpolate(double x1, double y1, double x2, double y2, double x)
        {
            double delta_x = (x2 - x1);

            if (delta_x == 0.0f)
                return y1;

            double dx = (x - x1) / delta_x;

            return dx * y2 + (1 - dx) * y1;
        }

        double WavetableVoice::nextSample(double const *samples, double nSamples)
        {
            double dOut = 0;

            double modulatedSampleIndex = readIndex_; // + (phase_modulation_ * nSamples);

            // if (modulatedSampleIndex < 0.0)
            //     modulatedSampleIndex += nSamples;

            if (modulatedSampleIndex >= nSamples)
                modulatedSampleIndex -= nSamples;

            std::size_t sampleIndex = static_cast<std::size_t>(modulatedSampleIndex);

            // double fFrac = modulatedSampleIndex - static_cast<double>(sampleIndex);

            /* note: sample data is opaquely over-allocated by one sample */
            // dOut = linear_interpolate(0.0, samples[sampleIndex], 1.0, samples[sampleIndex + 1], fFrac);
            dOut = samples[sampleIndex];

            readIndex_ += (delta_ * nSamples);

            if (readIndex_ >= nSamples)
                readIndex_ -= nSamples;

            return dOut;
        }

        void WavetableVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
        {
            if (sound_)
            {
                int const numChannels = outputBuffer.getNumChannels();
                int sampleIdx{};
                float currentSample = 0.0f;
    
                do
                {
                    int channelIdx{};

                    currentSample = static_cast<float>(velocity_ * this->nextSample(sound_->data(), static_cast<double>(sound_->size())));

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