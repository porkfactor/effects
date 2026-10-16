#ifndef ST1_PLUGIN_EDITOR_HPP_
#define ST1_PLUGIN_EDITOR_HPP_

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "components/EnvelopeVisualizer.hpp"

namespace st1
{
    class PluginProcessor;

    class PluginEditor :
        public juce::AudioProcessorEditor
    {
    public:
        using super = juce::AudioProcessorEditor;

        PluginEditor(PluginProcessor &);

        void paint(juce::Graphics &) override;
        void resized() override;

    private:
        gui::EnvelopeVisualizer ev_;
    };
}

#endif
