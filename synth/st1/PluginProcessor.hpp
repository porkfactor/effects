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

        //==============================================================================
        PluginProcessor();

        //==============================================================================
        bool canAddBus    (bool isInput) const override   { return (! isInput && getBusCount (false) < maxMidiChannel); }
        bool canRemoveBus (bool isInput) const override   { return (! isInput && getBusCount (false) > 1); }

        //==============================================================================
        void prepareToPlay (double newSampleRate, int samplesPerBlock) override
        {
            juce::ignoreUnused (samplesPerBlock);

            for (auto midiChannel = 0; midiChannel < maxMidiChannel; ++midiChannel)
                synth[midiChannel]->setCurrentPlaybackSampleRate (newSampleRate);
        }

        void releaseResources() override {}

        void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiBuffer) override
        {
            auto busCount = getBusCount (false);                // [11]

            for (auto busNr = 0; busNr < busCount; ++busNr)     // [12]
            {
                auto midiChannelBuffer = filterMidiMessagesForChannel (midiBuffer, busNr + 1);
                auto audioBusBuffer = getBusBuffer (buffer, false, busNr);

                synth [busNr]->renderNextBlock (audioBusBuffer, midiChannelBuffer, 0, audioBusBuffer.getNumSamples()); // [13]
            }
        }

        //==============================================================================
        juce::AudioProcessorEditor* createEditor() override          { return new juce::GenericAudioProcessorEditor (*this); }
        bool hasEditor() const override                              { return true; }

        //==============================================================================
        const juce::String getName() const override                  { return "Multi Out Synth"; }
        bool acceptsMidi() const override                            { return false; }
        bool producesMidi() const override                           { return false; }
        double getTailLengthSeconds() const override                 { return 0; }
        int getNumPrograms() override                                { return 1; }
        int getCurrentProgram() override                             { return 0; }
        void setCurrentProgram (int) override                        {}
        const juce::String getProgramName (int) override             { return {}; }
        void changeProgramName (int, const juce::String&) override   {}

        //==============================================================================
        void getStateInformation (juce::MemoryBlock&) override {}
        void setStateInformation (const void*, int) override {}

    private:
        //==============================================================================
        static juce::MidiBuffer filterMidiMessagesForChannel (const juce::MidiBuffer& input, int channel)
        {
            juce::MidiBuffer output;

            for (auto metadata : input)     // [14]
            {
                auto message = metadata.getMessage();

                if (message.getChannel() == channel)
                    output.addEvent (message, metadata.samplePosition);
            }

            return output;                  // [15]
        }

        void loadNewSample (const juce::MemoryBlock& sampleData)
        {
            auto soundBuffer = std::make_unique<juce::MemoryInputStream> (sampleData, false);   // [6]
            std::unique_ptr<juce::AudioFormatReader> formatReader (formatManager.findFormatForFileExtension ("ogg")->createReaderFor (soundBuffer.release(), true));

            juce::BigInteger midiNotes;
            midiNotes.setRange (0, 126, true);
            juce::SynthesiserSound::Ptr newSound = new juce::SamplerSound ("Voice", *formatReader, midiNotes, 0x40, 0.0, 0.0, 10.0); // [7]

            for (auto channel = 0; channel < maxMidiChannel; ++channel)             // [8]
                synth[channel]->removeSound (0);

            sound = newSound;                                                       // [9]

            for (auto channel = 0; channel < maxMidiChannel; ++channel)             // [10]
                synth[channel]->addSound (sound);
        }

        //==============================================================================
        juce::AudioFormatManager formatManager;
        juce::OwnedArray<juce::Synthesiser> synth;
        juce::SynthesiserSound::Ptr sound;

        //==============================================================================
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
    };
}

#endif
