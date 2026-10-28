#ifndef ST1_OSCILLATOR_PITCH_SHIFT_PARAMETER_HPP_
#define ST1_OSCILLATOR_PITCH_SHIFT_PARAMETER_HPP_

#include <juce_audio_processors/juce_audio_processors.h>

namespace st1
{
    class OscillatorPitchShiftParameter
    {
    public:
        static inline juce::String const perfect_unison = "P1";
        static inline juce::String const inc_minor_2nd = "+ m2";
        static inline juce::String const inc_major_2nd = "+ M2";
        static inline juce::String const inc_minor_3rd = "+ m3";
        static inline juce::String const inc_major_3rd = "+ M3";
        static inline juce::String const inc_perfect_4th = "+ P4";
        static inline juce::String const inc_diminished_5th = "+ A4/d5";
        static inline juce::String const inc_perfect_5th = "+ P5";
        static inline juce::String const inc_minor_6th = "+ m6";
        static inline juce::String const inc_major_6th = "+ M6";
        static inline juce::String const inc_minor_7th = "+ m7";
        static inline juce::String const inc_major_7th = "+ M7";
        static inline juce::String const inc_perfect_octave = "+ P8";
        static inline juce::String const dec_minor_2nd = "- m2";
        static inline juce::String const dec_major_2nd = "- M2";
        static inline juce::String const dec_minor_3rd = "- m3";
        static inline juce::String const dec_major_3rd = "- M3";
        static inline juce::String const dec_perfect_4th = "- P4";
        static inline juce::String const dec_diminished_5th = "- A4/d5";
        static inline juce::String const dec_perfect_5th = "- P5";
        static inline juce::String const dec_minor_6th = "- m6";
        static inline juce::String const dec_major_6th = "- M6";
        static inline juce::String const dec_minor_7th = "- m7";
        static inline juce::String const dec_major_7th = "- M7";
        static inline juce::String const dec_perfect_octave = "- P8";

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

        static juce::String const identifier()
        {
            static juce::String const identifier_ = "OFPS";
            return identifier_;
        }

        static std::unique_ptr<juce::AudioParameterFloat> create(juce::String const &name)
        {
            return std::make_unique<juce::AudioParameterFloat>(
                juce::ParameterID("OFPS", 1),
                name,
                juce::NormalisableRange<float>(
                    static_cast<float>(PitchShift::DEC_PERFECT_OCTAVE),
                    static_cast<float>(PitchShift::INC_PERFECT_OCTAVE),
                    1.0f),
                0.0f,
                juce::AudioParameterFloatAttributes()
                    .withLabel("Pitch Shift")
                    .withCategory(juce::AudioProcessorParameter::Category::genericParameter)
                    .withStringFromValueFunction(std::bind(&OscillatorPitchShiftParameter::stringFromValue, std::placeholders::_1))
                    .withValueFromStringFunction(std::bind(&OscillatorPitchShiftParameter::valueFromString, std::placeholders::_1))
            );
        }

    private:
        static juce::String stringFromValue(float v)
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

        static float valueFromString(juce::String const &v)
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


    };
}

#endif
