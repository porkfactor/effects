#ifndef ST1_COMPONENTS_OSCILLATOR_GROUP_HPP_
#define ST1_COMPONENTS_OSCILLATOR_GROUP_HPP_

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "OscillatorEditor.hpp"

namespace st1
{
    namespace components
    {
        class OscillatorGroup :
            public juce::GroupComponent
        {
        public:
            OscillatorGroup(juce::AudioProcessorValueTreeState &, juce::String const &, juce::String const &);

            void resized() override;

        private:
            OscillatorEditor oscillator_;
        };
    }
}

#endif
