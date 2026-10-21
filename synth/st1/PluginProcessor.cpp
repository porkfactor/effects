#include "PluginProcessor.hpp"
#include "PluginEditor.hpp"

#include "voices/SinusoidalVoice.hpp"
#include "voices/WavetableVoice.hpp"
#include "voices/WavetableSound.hpp"

namespace st1
{
    /**
     * Use `SynthesiserSound to store sound data associated with
     * a voice type (e.g. wavetable data that is shared across voices)
     * 
     * Calling it 'SoundData' would make more sense to me.
     * 
     * Use `SynthesiserVoice to render a sound. Seems that the voice is
     * re-used on a whim so it's critical that SynthesiserVoice::clearCurrentNote()
     * is invoked to mark the voice as unused.
     * 
     * Calling it 'SoundGenerator' would make more sense to me.
     * 
     * Anyway. Squishing these down so that we have a small number of fundamental
     * voice types seems like a good idea. 
     * 
     * - Wavetable
     * - FM
     * - Subtractive
     * - etc.
     * 
     * 
     */

    PluginProcessor::PluginProcessor() :
        AudioProcessor(BusesProperties()
                .withOutput ("Output #1", juce::AudioChannelSet::stereo(), true)
                .withOutput ("Output #2", juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #3", juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #4", juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #5", juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #6", juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #7", juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #8", juce::AudioChannelSet::stereo(), false)
                .withOutput ("Output #9", juce::AudioChannelSet::stereo(), false)
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
                synth_[midiChannel]->addVoice(new st1::voices::WavetableVoice());
                synth_[midiChannel]->addSound(new st1::voices::WavetableSound());
            }
        }
    }

    juce::AudioProcessorEditor *PluginProcessor::createEditor()
    {
        return new PluginEditor(*this);
    }

    bool PluginProcessor::hasEditor() const
    {
        return true;
    }

    juce::String const PluginProcessor::getName() const
    {
        return "Multi Out Synth";
    }

    bool PluginProcessor::acceptsMidi() const
    {
        return false;
    }

    bool PluginProcessor::producesMidi() const
    {
        return false;
    }

    double PluginProcessor::getTailLengthSeconds() const
    {
        return 0;
    }

    int PluginProcessor::getNumPrograms()
    {
        return 1; 
    }

    int PluginProcessor::getCurrentProgram()
    {
        return 0;
    }

    void PluginProcessor::setCurrentProgram(int)
    {}

    juce::String const PluginProcessor::getProgramName(int)
    {
        return {};
    }

    void PluginProcessor::changeProgramName(int, const juce::String &)
    {}

    void PluginProcessor::getStateInformation(juce::MemoryBlock &)
    {}

    void PluginProcessor::setStateInformation(void const *, int)
    {}

    bool PluginProcessor::canAddBus(bool isInput) const
    {
        return !isInput && (AudioProcessor::getBusCount(false) < maxMidiChannel);
    } 

    bool PluginProcessor::canRemoveBus(bool isInput) const
    {
        return !isInput && (AudioProcessor::getBusCount(false) > 1);
    }

    void PluginProcessor::releaseResources(void)
    {}

    void PluginProcessor::prepareToPlay(double newSampleRate, int samplesPerBlock)
    {
        juce::ignoreUnused(samplesPerBlock);

        for (auto midiChannel = 0; midiChannel < maxMidiChannel; ++midiChannel)
            synth_[midiChannel]->setCurrentPlaybackSampleRate(newSampleRate);
    }

    void PluginProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer& midiBuffer)
    {
        auto busCount = getBusCount(false);

        for (auto busNr = 0; busNr < busCount; ++busNr)
        {
            auto audioBusBuffer = getBusBuffer (buffer, false, busNr);
            auto midiChannelBuffer = filterMidiMessagesForChannel(midiBuffer, busNr + 1);

            synth_[busNr]->renderNextBlock(audioBusBuffer, midiChannelBuffer, 0, audioBusBuffer.getNumSamples()); 
        }
    }

    juce::MidiBuffer PluginProcessor::filterMidiMessagesForChannel(const juce::MidiBuffer& input, int channel)
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