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
            class OscillatorTypeCombo :
                public juce::ComboBox
            {
            public:
                OscillatorTypeCombo(juce::RangedAudioParameter *parameter, juce::String const &name, juce::UndoManager *undoManager = nullptr) :
                    ComboBox(name)
                {
                    if (parameter)
                    {
                        ComboBox::addItemList(parameter->getAllValueStrings(), 1);
                        attachment_.reset(new juce::ComboBoxParameterAttachment(*parameter, *this, undoManager));
                    }
                }
        
                ~OscillatorTypeCombo()
                {}

            private:
                std::unique_ptr<juce::ComboBoxParameterAttachment> attachment_;
            };

            class PitchShiftDial : public AnalogDial
            {
            public:
                PitchShiftDial(juce::String const &name, juce::String const &label) :
                    AnalogDial(name, label)
                {}
            };

            class PulseWidthDial : public AnalogDial
            {
            public:
                PulseWidthDial(juce::String const &name, juce::String const &label) :
                    AnalogDial(name, label)
                {}
            };

            class AmplitudeDial : public AnalogDial
            {
            public:
                AmplitudeDial(juce::String const &name, juce::String const &label) :
                    AnalogDial(name, label)
                {}
            };

            OscillatorTypeCombo oscillatorTypeCombo_;
            PitchShiftDial pitchShiftDial_;
            PulseWidthDial pulseWidthDial_;
            AmplitudeDial amplitudeDial_;
        };
    }
}

#endif
