#ifndef PF1_PLUGIN_EDITOR_HPP_
#define PF1_PLUGIN_EDITOR_HPP_

namespace pf1
{
    class AudioPluginAudioProcessor;

    //==============================================================================
    class AudioPluginAudioProcessorEditor final :
        public juce::AudioProcessorEditor
    {
    public:
        explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor&);
        ~AudioPluginAudioProcessorEditor() override;
    
        //==============================================================================
        void paint(juce::Graphics&) override;
        void resized() override;
    
    private:
        // This reference is provided as a quick way for your editor to
        // access the processor object that created it.
        AudioPluginAudioProcessor &processorRef;
    
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
    };
}

#endif
