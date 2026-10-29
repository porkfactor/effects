#ifndef ST1_COMPONENTS_OSCILLATOR_EDITOR_HPP_
#define ST1_COMPONENTS_OSCILLATOR_EDITOR_HPP_

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "AnalogDial.hpp"

namespace st1
{
    namespace components
    {
        class OscillatorEditor :
            public juce::Component
        {
        public:
            OscillatorEditor(juce::AudioProcessorValueTreeState &, juce::String const &);

            void resized() override;

        private:
            class OscillatorTypeDial final : public AnalogDial
            {
            public:
                OscillatorTypeDial(juce::String const &name, juce::String const &label) :
                    AnalogDial(name, label)
                {}
            };

            class PitchShiftDial final : public AnalogDial
            {
            public:
                PitchShiftDial(juce::String const &name, juce::String const &label) :
                    AnalogDial(name, label)
                {}
            };

            class PulseWidthDial final : public AnalogDial
            {
            public:
                PulseWidthDial(juce::String const &name, juce::String const &label) :
                    AnalogDial(name, label)
                {}
            };

            class AmplitudeDial final : public AnalogDial
            {
            public:
                AmplitudeDial(juce::String const &name, juce::String const &label) :
                    AnalogDial(name, label)
                {}
            };

            OscillatorTypeDial oscillatorTypeDial_;
            PitchShiftDial pitchShiftDial_;
            PulseWidthDial pulseWidthDial_;
            AmplitudeDial amplitudeDial_;
        };
    }
}

#endif
