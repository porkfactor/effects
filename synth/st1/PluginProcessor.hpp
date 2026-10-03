#ifndef ST1_PLUGIN_PROCESSOR_HPP_
#define ST1_PLUGIN_PROCESSOR_HPP_

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_formats/juce_audio_formats.h>

namespace st1
{
    class PluginProcessor  : public juce::AudioProcessor
    {
    public:
        enum
        {
            maxMidiChannel = 16,
            maxNumberOfVoices = 5
        };

        PluginProcessor();

        bool canAddBus(bool isInput) const override;
        bool canRemoveBus(bool isInput) const override;

        void prepareToPlay(double newSampleRate, int samplesPerBlock) override;
        void releaseResources() override;
        void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiBuffer) override;

        juce::AudioProcessorEditor* createEditor() override          { return new juce::GenericAudioProcessorEditor (*this); }
        bool hasEditor() const override                              { return true; }

        const juce::String getName() const override                  { return "Multi Out Synth"; }
        bool acceptsMidi() const override                            { return false; }
        bool producesMidi() const override                           { return false; }
        double getTailLengthSeconds() const override                 { return 0; }
        int getNumPrograms() override                                { return 1; }
        int getCurrentProgram() override                             { return 0; }
        void setCurrentProgram (int) override                        {}
        const juce::String getProgramName (int) override             { return {}; }
        void changeProgramName (int, const juce::String&) override   {}

        void getStateInformation (juce::MemoryBlock&) override {}
        void setStateInformation (const void*, int) override {}
    private:
        static juce::MidiBuffer filterMidiMessagesForChannel (const juce::MidiBuffer& input, int channel);

        juce::OwnedArray<juce::Synthesiser> synth_;
        juce::SynthesiserSound::Ptr sound;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
    };
}

#endif
