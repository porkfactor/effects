#ifndef ST1_PLUGIN_EDITOR_HPP_
#define ST1_PLUGIN_EDITOR_HPP_

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "components/EnvelopeEditor.hpp"
#include "components/OscillatorGroup.hpp"

namespace st1
{
    class PluginProcessor;

    class PluginEditor :
        public juce::AudioProcessorEditor
    {
    public:
        PluginEditor(PluginProcessor &);

        void paint(juce::Graphics &) override;
        void resized() override;

    private:
        components::OscillatorGroup oscillator_;

        // gui::EnvelopeVisualizer ev_;
    };
}

#endif
