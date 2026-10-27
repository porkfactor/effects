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
            class AttackDial : public AnalogDial
            {
            public:
                AttackDial(juce::String const &name, juce::String const &label) :
                    AnalogDial(name, label)
                {}
            };

            class DecayDial : public AnalogDial
            {
            public:
                DecayDial(juce::String const &name, juce::String const &label) :
                    AnalogDial(name, label)
                {}
            };

            class SustainDial : public AnalogDial
            {
            public:
                SustainDial(juce::String const &name, juce::String const &label) :
                    AnalogDial(name, label)
                {}
            };

            class ReleaseDial : public AnalogDial
            {
            public:
                ReleaseDial(juce::String const &name, juce::String const &label) :
                    AnalogDial(name, label)
                {}
            };

            AttackDial attackDial_;
            DecayDial decayDial_;
            SustainDial sustainDial_;
            ReleaseDial releaseDial_;
        };
    }
}

#endif
