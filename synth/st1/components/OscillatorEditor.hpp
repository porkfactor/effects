#ifndef ST1_COMPONENTS_OSCILLATOR_EDITOR_HPP_
#define ST1_COMPONENTS_OSCILLATOR_EDITOR_HPP_

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

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
            void paint(juce::Graphics &) override;

        private:
            struct OscillatorTypeControl : public juce::ComboBox
            {
            public:
                OscillatorTypeControl(juce::AudioProcessorValueTreeState &, juce::String const &);
                ~OscillatorTypeControl();

            private:
                std::unique_ptr<juce::ComboBoxParameterAttachment> attachment_;
            };

            struct PitchShiftControl : public juce::Slider
            {
                PitchShiftControl(juce::AudioProcessorValueTreeState &, juce::String const &);
                ~PitchShiftControl();

            private:
                std::unique_ptr<juce::SliderParameterAttachment> attachment_;
            };

            struct PulseWidthControl : public juce::Slider
            {
            public:
                PulseWidthControl(juce::AudioProcessorValueTreeState &, juce::String const &);
                ~PulseWidthControl();

            private:
                std::unique_ptr<juce::SliderParameterAttachment> attachment_;
            };

            OscillatorTypeControl oscillatorTypeControl_;
            PitchShiftControl pitchShiftControl_;
            PulseWidthControl pulseWidthControl_;
        };
    }
}

#endif
