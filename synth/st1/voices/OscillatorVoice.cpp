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

            velocity_ = static_cast<double>(velocity) * 0.8;
            pitchFrequency_ = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
            modulo_ = 0.0;

            pitchWheelAdjust(currentPitchWheelPosition);
        }

        void OscillatorVoice::stopNote(float velocity, bool allowTailOff)
        {
            juce::ignoreUnused(velocity);
            juce::ignoreUnused(allowTailOff);

            if (allowTailOff)
            {
                if (tailOff_ == 0.0)
                {
                    tailOff_ = 1.0;
                }
            }
            else
            {
                SynthesiserVoice::clearCurrentNote();
                reset();
            }
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
            if (pitchFrequency_ != 0.0)
            {
                int const numChannels = outputBuffer.getNumChannels();
                int sampleIdx{};
                float currentSample = 0.0f;

                do
                {
                    int channelIdx{};

                    if (tailOff_ != 0.0)
                    {
                        tailOff_ *= 0.99;

                        if (tailOff_ <= 0.05)
                        {
                            clearCurrentNote();
                            reset();
                            break;
                        }

                        currentSample = static_cast<float>(nextSample() * tailOff_);
                    }
                    else
                    {
                        currentSample = static_cast<float>(nextSample());
                    }

                    do
                    {
                        outputBuffer.addSample(channelIdx, startSample + sampleIdx, currentSample);
                        ++channelIdx;
                    } while(channelIdx < numChannels);
    
                    ++sampleIdx;
                } while (sampleIdx < numSamples);
            }
        }

        void OscillatorVoice::reset(void)
        {
            pitchFrequency_ = 0.0;
            delta_ = 0.0;
            tailOff_ = 0.0;
            modulo_ = 0.0;
        }

        double OscillatorVoice::nextSample(void)
        {
            double sample;

            switch (type_)
            {
            case wave_type::sinusoid:
                sample = std::sin(modulo_ * 2.0 * M_PI);
                break;
            case wave_type::sawtooth:
                sample = (modulo_ * 2.0) - 1.0;
                break;
            case wave_type::square:
                sample = (modulo_ > pulseWidth_) ? 1.0 : -1.0;
                break;
            case wave_type::triangle:
                sample = (2.0 * abs((2.0 * modulo_) - 1.0)) - 1.0;
                break;
            }

            modulo_ += delta_;

            if (modulo_ > 1.0)
                modulo_ -= 1.0;

            return sample * velocity_;
        }

        void OscillatorVoice::pitchWheelAdjust(int pitchWheelValue)
        {
            if (pitchWheelValue == 0x2000)
            {
                delta_ = pitchFrequency_ / SynthesiserVoice::getSampleRate();
            }
            else
            {
                double semitones = static_cast<double>(pitchWheelValue - INT32_C(0x2000)) / 4096.0;
                double frequency_adjust = std::exp2(static_cast<double>(semitones) / 12.0);

                delta_ = (pitchFrequency_ * frequency_adjust) / SynthesiserVoice::getSampleRate();
            }
        }
    }
}