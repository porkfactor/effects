#include "OscillatorEditor.hpp"

namespace st1
{
    namespace gui
    {
        static juce::String const sawtooth("Sawtooth");

        static juce::String const perfect_unison = "P1";
        static juce::String const inc_minor_2nd = "+ m2";
        static juce::String const inc_major_2nd = "+ M2";
        static juce::String const inc_minor_3rd = "+ m3";
        static juce::String const inc_major_3rd = "+ M3";
        static juce::String const inc_perfect_4th = "+ P4";
        static juce::String const inc_diminished_5th = "+ A4/d5";
        static juce::String const inc_perfect_5th = "+ P5";
        static juce::String const inc_minor_6th = "+ m6";
        static juce::String const inc_major_6th = "+ M6";
        static juce::String const inc_minor_7th = "+ m7";
        static juce::String const inc_major_7th = "+ M7";
        static juce::String const inc_perfect_octave = "+ P8";
        static juce::String const dec_minor_2nd = "- m2";
        static juce::String const dec_major_2nd = "- M2";
        static juce::String const dec_minor_3rd = "- m3";
        static juce::String const dec_major_3rd = "- M3";
        static juce::String const dec_perfect_4th = "- P4";
        static juce::String const dec_diminished_5th = "- A4/d6";
        static juce::String const dec_perfect_5th = "- P5";
        static juce::String const dec_minor_6th = "- m6";
        static juce::String const dec_major_6th = "- M6";
        static juce::String const dec_minor_7th = "- m7";
        static juce::String const dec_major_7th = "- M7";
        static juce::String const dec_perfect_octave = "- P8";

        OscillatorEditor::OscillatorTypeControl::OscillatorTypeControl(juce::AudioProcessorValueTreeState &s, juce::String const &name) :
            ComboBox(name)
        {
            juce::StringArray choices = {
                "Sawtooth",
                "Sinusoid",
                "Square",
                "Triangle"
            };

            std::unique_ptr<juce::RangedAudioParameter> parameter(new juce::AudioParameterChoice(
                juce::ParameterID("oscillator_type", 1),
                name,
                choices,
                0,
                juce::AudioParameterChoiceAttributes{}
            ));

            if (parameter)
            {
                attachment_.reset(new juce::ComboBoxParameterAttachment(*parameter, *this, s.undoManager));
                s.createAndAddParameter(std::move(parameter));
            }
        }

        OscillatorEditor::OscillatorTypeControl::~OscillatorTypeControl()
        {}

        juce::String OscillatorEditor::OscillatorTypeControl::valueToText(float v)
        {
            switch (static_cast<OscillatorType>(v))
            {
            case OscillatorType::SAWTOOTH:
                return sawtooth;
            case OscillatorType::SINUSOID:
                return "Sinusoid";
            case OscillatorType::SQUARE:
                return "Square";
            case OscillatorType::TRIANGLE:
                return "Triangle";
            }

            return "";
        }

        float OscillatorEditor::OscillatorTypeControl::textToValue(juce::String const &v)
        {
            if (v == sawtooth)
            {
                return static_cast<float>(OscillatorType::SAWTOOTH);
            }

            return static_cast<float>(OscillatorType::SINUSOID);
        }

        OscillatorEditor::PitchShiftControl::PitchShiftControl(juce::AudioProcessorValueTreeState &s, juce::String const &name) :
            Slider(name)
        {
            juce::Slider::setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
            juce::Slider::setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
            juce::Slider::setRange(static_cast<float>(PitchShift::DEC_PERFECT_OCTAVE), static_cast<float>(PitchShift::INC_PERFECT_OCTAVE), 1.0);

            std::unique_ptr<juce::AudioParameterFloat> parameter(new juce::AudioParameterFloat(
                juce::ParameterID("pitch_shift", 1),
                name,
                juce::NormalisableRange<float>(
                    static_cast<float>(PitchShift::DEC_PERFECT_OCTAVE),
                    static_cast<float>(PitchShift::INC_PERFECT_OCTAVE),
                    1.0),
                0.0,
                juce::AudioParameterFloatAttributes()
                    .withLabel("")
                    .withCategory(juce::AudioProcessorParameter::Category::genericParameter)
                    .withStringFromValueFunction(std::bind(&PitchShiftControl::valueToText, std::placeholders::_1))
                    .withValueFromStringFunction(std::bind(&PitchShiftControl::textToValue, std::placeholders::_1))
            ));

            if (parameter)
            {
                attachment_.reset(new juce::SliderParameterAttachment(*parameter, *this, s.undoManager));
                s.createAndAddParameter(std::move(parameter));
            }
        }

        OscillatorEditor::PitchShiftControl::~PitchShiftControl()
        {}

        juce::String OscillatorEditor::PitchShiftControl::valueToText(float v)
        {
            switch (static_cast<PitchShift>(v))
            {
            case PitchShift::PERFECT_UNISON: return perfect_unison;
            case PitchShift::INC_MINOR_2ND: return inc_minor_2nd;
            case PitchShift::INC_MAJOR_2ND: return inc_major_2nd;
            case PitchShift::INC_MINOR_3RD: return inc_minor_3rd;
            case PitchShift::INC_MAJOR_3RD: return inc_major_3rd;
            case PitchShift::INC_PERFECT_4TH: return inc_perfect_4th;
            case PitchShift::INC_DIMINISHED_5TH: return inc_diminished_5th;
            case PitchShift::INC_PERFECT_5TH: return inc_perfect_5th;
            case PitchShift::INC_MINOR_6TH: return inc_minor_6th;
            case PitchShift::INC_MAJOR_6TH: return inc_major_6th;
            case PitchShift::INC_MINOR_7TH: return inc_minor_7th;
            case PitchShift::INC_MAJOR_7TH: return inc_major_7th;
            case PitchShift::INC_PERFECT_OCTAVE: return inc_perfect_octave;
            case PitchShift::DEC_MINOR_2ND: return dec_minor_2nd;
            case PitchShift::DEC_MAJOR_2ND: return dec_major_2nd;
            case PitchShift::DEC_MINOR_3RD: return dec_minor_3rd;
            case PitchShift::DEC_MAJOR_3RD: return dec_major_3rd;
            case PitchShift::DEC_PERFECT_4TH: return dec_perfect_4th;
            case PitchShift::DEC_DIMINISHED_5TH: return dec_diminished_5th;
            case PitchShift::DEC_PERFECT_5TH: return dec_perfect_5th;
            case PitchShift::DEC_MINOR_6TH: return dec_minor_6th;
            case PitchShift::DEC_MAJOR_6TH: return dec_major_6th;
            case PitchShift::DEC_MINOR_7TH: return dec_minor_7th;
            case PitchShift::DEC_MAJOR_7TH: return dec_major_7th;
            case PitchShift::DEC_PERFECT_OCTAVE: return dec_perfect_octave;
            }

            return "";
        }

        float OscillatorEditor::PitchShiftControl::textToValue(juce::String const &v)
        {
            static std::map<juce::String, PitchShift> const values =
            {
                { perfect_unison, PitchShift::PERFECT_UNISON },
                { inc_minor_2nd, PitchShift::INC_MINOR_2ND },
                { inc_major_2nd, PitchShift::INC_MAJOR_2ND },
                { inc_minor_3rd, PitchShift::INC_MINOR_3RD },
                { inc_major_3rd, PitchShift::INC_MAJOR_3RD },
                { inc_perfect_4th, PitchShift::INC_PERFECT_4TH },
                { inc_diminished_5th, PitchShift::INC_DIMINISHED_5TH },
                { inc_perfect_5th, PitchShift::INC_PERFECT_5TH },
                { inc_minor_6th, PitchShift::INC_MINOR_6TH },
                { inc_major_6th, PitchShift::INC_MAJOR_6TH },
                { inc_minor_7th, PitchShift::INC_MINOR_7TH },
                { inc_major_7th, PitchShift::INC_MAJOR_7TH },
                { inc_perfect_octave, PitchShift::INC_PERFECT_OCTAVE },
                { dec_minor_2nd, PitchShift::DEC_MINOR_2ND },
                { dec_major_2nd, PitchShift::DEC_MAJOR_2ND },
                { dec_minor_3rd, PitchShift::DEC_MINOR_3RD },
                { dec_major_3rd, PitchShift::DEC_MAJOR_3RD },
                { dec_perfect_4th, PitchShift::DEC_PERFECT_4TH },
                { dec_diminished_5th, PitchShift::DEC_DIMINISHED_5TH },
                { dec_perfect_5th, PitchShift::DEC_PERFECT_5TH },
                { dec_minor_6th, PitchShift::DEC_MINOR_6TH },
                { dec_major_6th, PitchShift::DEC_MAJOR_6TH },
                { dec_minor_7th, PitchShift::DEC_MINOR_7TH },
                { dec_major_7th, PitchShift::DEC_MAJOR_7TH },
                { dec_perfect_octave, PitchShift::DEC_PERFECT_OCTAVE },
            };

            auto it = values.find(v);

            if (it != values.end())
            {
                return static_cast<float>(it->second);
            }

            return static_cast<float>(PitchShift::PERFECT_UNISON);
        }

        OscillatorEditor::PulseWidthControl::PulseWidthControl(juce::AudioProcessorValueTreeState &s, juce::String const &name) :
            Slider(name)
        {
            juce::Slider::setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
            juce::Slider::setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);
            juce::Slider::setRange(0.0, 100.0, 1.0);

            std::unique_ptr<juce::AudioParameterFloat> parameter(new juce::AudioParameterFloat(
                juce::ParameterID("pulse_width", 1),
                name,
                juce::NormalisableRange<float>(static_cast<float>(0.0), static_cast<float>(100.0), 1.0),
                0.0,
                juce::AudioParameterFloatAttributes()
                    .withLabel("")
                    .withCategory(juce::AudioProcessorParameter::Category::genericParameter)
            ));

            if (parameter)
            {
                attachment_.reset(new juce::SliderParameterAttachment(*parameter, *this, s.undoManager));
                s.createAndAddParameter(std::move(parameter));
            }
        }

        OscillatorEditor::PulseWidthControl::~PulseWidthControl()
        {}

        OscillatorEditor::OscillatorEditor(juce::AudioProcessorValueTreeState &s, juce::Component *p) :
            parent_(p),
            oscillatorTypeControl_(s, "Oscillator Type"),
            pitchShiftControl_(s, "Pitch Shift"),
            pulseWidthControl_(s, "Pulse Width")
        {
            this->addAndMakeVisible(oscillatorTypeControl_);
            this->addAndMakeVisible(pitchShiftControl_);
            this->addAndMakeVisible(pulseWidthControl_);

            parent_->addAndMakeVisible(*this);
        }

        void OscillatorEditor::resized(void)
        {
            auto bounds = Component::getBounds();

            oscillatorTypeControl_.setBounds(bounds.removeFromTop(30));
            pitchShiftControl_.setBounds(bounds.removeFromRight(bounds.getWidth() / 2));
            pulseWidthControl_.setBounds(bounds);
        }

        void OscillatorEditor::paint(juce::Graphics &g)
        {
            g.fillAll(Component::getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
        }
    }
}