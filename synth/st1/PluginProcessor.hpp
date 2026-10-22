#ifndef ST1_PLUGIN_PROCESSOR_HPP_
#define ST1_PLUGIN_PROCESSOR_HPP_

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_formats/juce_audio_formats.h>

namespace st1
{
    class PluginProcessor  :
        public juce::AudioProcessor
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
        void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiBuffer) override;

        juce::AudioProcessorEditor* createEditor() override;
        bool hasEditor() const override;
        const juce::String getName() const override;
        bool acceptsMidi() const override;
        bool producesMidi() const override;
        double getTailLengthSeconds() const override;
        int getNumPrograms() override;
        int getCurrentProgram() override;
        void setCurrentProgram(int) override;
        const juce::String getProgramName(int) override;
        void changeProgramName(int, const juce::String&) override;
        void getStateInformation (juce::MemoryBlock&) override;
        void setStateInformation (const void*, int) override;

        juce::AudioProcessorValueTreeState &state();

    private:
        static juce::MidiBuffer filterMidiMessagesForChannel(const juce::MidiBuffer &input, int channel);
        juce::AudioProcessorValueTreeState state_;

        juce::OwnedArray<juce::Synthesiser> synth_;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginProcessor)
    };
}

#endif
