#include "PluginProcessor.hpp"

namespace st1
{
    struct SinWaveSound   : public juce::SynthesiserSound
    {
        SinWaveSound() {}

        bool appliesToNote(int) override
        {
            return true;
        }

        bool appliesToChannel(int) override
        {
            return true;
        }
    };

    class SinWaveVoice : public juce::SynthesiserVoice
    {
    public:
        SinWaveVoice()
        {}

        bool canPlaySound(juce::SynthesiserSound *) override
        {
            return true;
        }

        void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override
        {
            currentAngle = 0.0;
            level = velocity * 0.15;
            tailOff = 0.0;

            auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
            auto cyclesPerSample = cyclesPerSecond / getSampleRate();

            angleDelta = cyclesPerSample * 2.0 * juce::MathConstants<double>::pi;
        }

        void stopNote(float velocity, bool allowTailOff) override
        {
            if (allowTailOff)
            {
                if (tailOff == 0.0)
                    tailOff = 1.0;
            }
            else
            {
                clearCurrentNote();
                angleDelta = 0.0;
            }
        }

        void pitchWheelMoved(int newPitchWheelValue) override
        {

        }

        void controllerMoved(int controllerNumber, int newControllerValue) override
        {

        }

        void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override
        {
            if (angleDelta != 0.0)
            {
                if (tailOff > 0.0) // [7]
                {
                    while (--numSamples >= 0)
                    {
                        auto currentSample = (float) (std::sin (currentAngle) * level * tailOff);

                        for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                            outputBuffer.addSample (i, startSample, currentSample);

                        currentAngle += angleDelta;
                        ++startSample;

                        tailOff *= 0.99; // [8]

                        if (tailOff <= 0.005)
                        {
                            clearCurrentNote(); // [9]

                            angleDelta = 0.0;
                            break;
                        }
                    }
                }
                else
                {
                    while (--numSamples >= 0) // [6]
                    {
                        auto currentSample = (float) (std::sin (currentAngle) * level);

                        for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                            outputBuffer.addSample (i, startSample, currentSample);

                        currentAngle += angleDelta;
                        ++startSample;
                    }
                }
            }
        }

    private:
        double currentAngle = 0.0;
        double angleDelta = 0.0;
        double level = 0.0;
        double tailOff = 0.0;
    };

    PluginProcessor::PluginProcessor() :
        AudioProcessor(BusesProperties()
                .withOutput ("Output #1",  juce::AudioChannelSet::stereo(), true)
                .withOutput ("Output #2",  juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #3",  juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #4",  juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #5",  juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #6",  juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #7",  juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #8",  juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #9",  juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #10", juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #11", juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #12", juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #13", juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #14", juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #15", juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #16", juce::AudioChannelSet::stereo(), false)
            )
    {
        for (auto midiChannel = 0; midiChannel < maxMidiChannel; ++midiChannel)
        {
            synth_.add(new juce::Synthesiser());

            for (auto i = 0; i < maxNumberOfVoices; ++i)
            {
                synth_[midiChannel]->addVoice(new SinWaveVoice());
                synth_[midiChannel]->addSound(new SinWaveSound());
            }
        }
    }

    bool PluginProcessor::canAddBus(bool isInput) const
    {
        return !isInput && (getBusCount (false) < maxMidiChannel);
    } 

    bool PluginProcessor::canRemoveBus(bool isInput) const
    {
        return !isInput && (getBusCount (false) > 1);
    }

    void PluginProcessor::releaseResources(void)
    {}

    void PluginProcessor::prepareToPlay(double newSampleRate, int samplesPerBlock)
    {
        juce::ignoreUnused(samplesPerBlock);

        for (auto midiChannel = 0; midiChannel < maxMidiChannel; ++midiChannel)
            synth_[midiChannel]->setCurrentPlaybackSampleRate (newSampleRate);
    }

    void PluginProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiBuffer)
    {
        auto busCount = getBusCount(false);

        for (auto busNr = 0; busNr < busCount; ++busNr)
        {
            auto audioBusBuffer = getBusBuffer (buffer, false, busNr);
            auto midiChannelBuffer = filterMidiMessagesForChannel(midiBuffer, busNr + 1);

            synth_[busNr]->renderNextBlock(audioBusBuffer, midiChannelBuffer, 0, audioBusBuffer.getNumSamples()); 
        }
    }

    juce::MidiBuffer PluginProcessor::filterMidiMessagesForChannel (const juce::MidiBuffer& input, int channel)
    {
        juce::MidiBuffer output;

        for (auto metadata : input)
        {
            auto message = metadata.getMessage();

            if (message.getChannel() == channel)
                output.addEvent (message, metadata.samplePosition);
        }

        return output;
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new st1::PluginProcessor();
}