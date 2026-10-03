#include "PluginProcessor.hpp"

namespace st1
{
    static uint8_t const singing_ogg[] = {};

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
        formatManager.registerBasicFormats();

        for (auto midiChannel = 0; midiChannel < maxMidiChannel; ++midiChannel)
        {
            synth.add (new juce::Synthesiser());

            for (auto i = 0; i < maxNumberOfVoices; ++i)
                synth[midiChannel]->addVoice (new juce::SamplerVoice());
        }

        loadNewSample (juce::MemoryBlock (singing_ogg, sizeof(singing_ogg)));
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new st1::PluginProcessor();
}