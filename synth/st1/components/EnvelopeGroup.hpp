#ifndef ST1_COMPONENTS_ENVELOPE_GROUP_HPP_
#define ST1_COMPONENTS_ENVELOPE_GROUP_HPP_

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "EnvelopeEditor.hpp"

namespace st1
{
    namespace components
    {
        class EnvelopeGroup :
            public juce::GroupComponent
        {
        public:
            EnvelopeGroup(juce::AudioProcessorValueTreeState &, juce::String const &, juce::String const &);
            ~EnvelopeGroup() override;

            void resized() override;

        private:
            EnvelopeEditor envelope_;
        };
    }
}

#endif
