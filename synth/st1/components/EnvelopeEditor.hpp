#ifndef ST1_COMPONENTS_ENVELOPE_EDITOR_HPP_
#define ST1_COMPONENTS_ENVELOPE_EDITOR_HPP_

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "AnalogDial.hpp"
#include "EnvelopeVisualizer.hpp"

namespace st1
{
    namespace components
    {
        class EnvelopeEditor :
            public juce::Component
        {
        public:
            EnvelopeEditor(juce::AudioProcessorValueTreeState &, juce::String const &);

            void resized(void) override;

        private:
            class AttackDial : public AttachedAnalogDial
            {
            public:
                AttackDial(juce::RangedAudioParameter *parameter, juce::String const &name, juce::UndoManager *undoManager = nullptr) :
                    AttachedAnalogDial(parameter, name, undoManager)
                {}
            };

            class DecayDial : public AttachedAnalogDial
            {
            public:
                DecayDial(juce::RangedAudioParameter *parameter, juce::String const &name, juce::UndoManager *undoManager = nullptr) :
                    AttachedAnalogDial(parameter, name, undoManager)
                {}
            };

            class ReleaseDial : public AttachedAnalogDial
            {
            public:
                ReleaseDial(juce::RangedAudioParameter *parameter, juce::String const &name, juce::UndoManager *undoManager = nullptr) :
                    AttachedAnalogDial(parameter, name, undoManager)
                {}
            };

            AttackDial attackDial_;
            DecayDial decayDial_;
            ReleaseDial releaseDial_;
        };
    }
}

#endif
