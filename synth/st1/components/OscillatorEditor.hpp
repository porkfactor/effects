#ifndef ST1_GUI_OSCILLATOR_EDITOR_HPP_
#define ST1_GUI_OSCILLATOR_EDITOR_HPP_

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

namespace st1
{
    namespace gui
    {
        class OscillatorEditor :
            public juce::Component
        {
        public:
            OscillatorEditor(juce::AudioProcessorValueTreeState &, juce::Component *);

            void resized() override;
            void paint(juce::Graphics &) override;

        private:
            struct OscillatorTypeControl : public juce::ComboBox
            {
            public:
                enum OscillatorType
                {
                    SINUSOID = 1,
                    SQUARE = 2,
                    SAWTOOTH = 3,
                    TRIANGLE = 4,
                };

                OscillatorTypeControl(juce::AudioProcessorValueTreeState &, juce::String const &);
                ~OscillatorTypeControl();

                static juce::String valueToText(float);
                static float textToValue(juce::String const &);

            private:
                std::unique_ptr<juce::ComboBoxParameterAttachment> attachment_;
            };

            struct PitchShiftControl : public juce::Slider
            {
            public:
                enum class PitchShift : int8_t
                {
                    PERFECT_UNISON = 0,
                    INC_MINOR_2ND = 1,
                    INC_MAJOR_2ND = 2,
                    INC_MINOR_3RD = 3,
                    INC_MAJOR_3RD = 4,
                    INC_PERFECT_4TH = 5,
                    INC_DIMINISHED_5TH = 6,
                    INC_PERFECT_5TH = 7,
                    INC_MINOR_6TH = 8,
                    INC_MAJOR_6TH = 9,
                    INC_MINOR_7TH = 10,
                    INC_MAJOR_7TH = 11,
                    INC_PERFECT_OCTAVE = 12,
                    DEC_MINOR_2ND = -1,
                    DEC_MAJOR_2ND = -2,
                    DEC_MINOR_3RD = -3,
                    DEC_MAJOR_3RD = -4,
                    DEC_PERFECT_4TH = -5,
                    DEC_DIMINISHED_5TH = -6,
                    DEC_PERFECT_5TH = -7,
                    DEC_MINOR_6TH = -8,
                    DEC_MAJOR_6TH = -9,
                    DEC_MINOR_7TH = -10,
                    DEC_MAJOR_7TH = -11,
                    DEC_PERFECT_OCTAVE = -12,
                };

                PitchShiftControl(juce::AudioProcessorValueTreeState &, juce::String const &);
                ~PitchShiftControl();

                static juce::String valueToText(float);
                static float textToValue(juce::String const &);

            private:
                std::unique_ptr<juce::SliderParameterAttachment> attachment_;
            };

            struct PulseWidthControl : public juce::Slider
            {
            public:
                PulseWidthControl(juce::AudioProcessorValueTreeState &, juce::String const &);
                ~PulseWidthControl();

                static juce::String valueToText(float);
                static float textToValue(juce::String const &);

            private:
                std::unique_ptr<juce::SliderParameterAttachment> attachment_;
            };

            juce::Component *parent_;
            OscillatorTypeControl oscillatorTypeControl_;
            PitchShiftControl pitchShiftControl_;
            PulseWidthControl pulseWidthControl_;
        };
    }
}

#endif
