#include "OscillatorVoice.hpp"

namespace st1
{
    namespace voices
    {
        static juce::String const sawtooth("Sawtooth");
        static juce::String const sinusoid("Sinusoid");
        static juce::String const square("Square");
        static juce::String const triangle("Triangle");

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
        static juce::String const dec_diminished_5th = "- A4/d5";
        static juce::String const dec_perfect_5th = "- P5";
        static juce::String const dec_minor_6th = "- m6";
        static juce::String const dec_major_6th = "- M6";
        static juce::String const dec_minor_7th = "- m7";
        static juce::String const dec_major_7th = "- M7";
        static juce::String const dec_perfect_octave = "- P8";

        class OscillatorTypeParameter
        {
        public:
            enum class OscillatorType
            {
                SAWTOOTH,
                SINUSOID,
                SQUARE,
                TRIANGLE,
            };

            static juce::String const identifier()
            {
                static juce::String const identifier_ = "OCOT";
                return identifier_;
            }

            static std::unique_ptr<juce::AudioParameterChoice> create(juce::String const &name)
            {
                return std::make_unique<juce::AudioParameterChoice>(
                    juce::ParameterID(identifier(), 1),
                    name,
                    juce::StringArray{
                        sawtooth,
                        sinusoid,
                        square,
                        triangle,
                    },
                    0,
                    juce::AudioParameterChoiceAttributes()
                        .withLabel("selected")
                        .withStringFromValueFunction(std::bind(&OscillatorTypeParameter::stringFromValue, std::placeholders::_1))
                        .withValueFromStringFunction(std::bind(&OscillatorTypeParameter::valueFromString, std::placeholders::_1))
                );
            }

            static juce::String stringFromValue(float v)
            {
                switch (static_cast<OscillatorType>(v))
                {
                case OscillatorType::SAWTOOTH:
                    return sawtooth;
                case OscillatorType::SINUSOID:
                    return sinusoid;
                case OscillatorType::SQUARE:
                    return square;
                case OscillatorType::TRIANGLE:
                    return triangle;
                }

                return sinusoid;
            }

            static float valueFromString(juce::String const &v)
            {
                static std::map<juce::String, OscillatorType> const values =
                {
                    { sawtooth, OscillatorType::SAWTOOTH },
                    { sinusoid, OscillatorType::SINUSOID },
                    { square, OscillatorType::SQUARE },
                    { triangle, OscillatorType::TRIANGLE },
                };

                auto it = values.find(v);

                if (it != values.end())
                {
                    return static_cast<float>(it->second);
                }

                return static_cast<float>(OscillatorType::SINUSOID);
            }

        private:
        };

        class PulseWidthParameter
        {
        public:
            static juce::String const identifier()
            {
                static juce::String const identifier_ = "OFPW";
                return identifier_;
            }

            static std::unique_ptr<juce::AudioParameterFloat> create(juce::String const &name)
            {
                return std::make_unique<juce::AudioParameterFloat>(
                    juce::ParameterID(identifier(), 1),
                    name,
                    juce::NormalisableRange<float>(static_cast<float>(0.0), static_cast<float>(100.0), 1.0),
                    0.0,
                    juce::AudioParameterFloatAttributes()
                        .withLabel("")
                        .withCategory(juce::AudioProcessorParameter::Category::genericParameter)
                );
            }
        private:
        };

        class PitchShiftParameter
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
                        1.0),
                    0.0,
                    juce::AudioParameterFloatAttributes()
                        .withLabel("")
                        .withCategory(juce::AudioProcessorParameter::Category::genericParameter)
                        .withStringFromValueFunction(std::bind(&PitchShiftParameter::stringFromValue, std::placeholders::_1))
                        .withValueFromStringFunction(std::bind(&PitchShiftParameter::valueFromString, std::placeholders::_1))
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

        std::unique_ptr<juce::AudioProcessorParameterGroup> OscillatorVoice::parameters(juce::String const &name)
        {
            return std::make_unique<juce::AudioProcessorParameterGroup>(
                juce::String("OVPG"),
                juce::String("oscillator"),
                juce::String("|"),
                OscillatorTypeParameter::create("oscillator_type"),
                PitchShiftParameter::create("pitch_shift"),
                PulseWidthParameter::create("pulse_width")
            );
        }

        OscillatorVoice::OscillatorVoice(juce::AudioProcessorValueTreeState &s) :
            juce::AudioProcessorValueTreeState::Listener(),
            state_(s)
        {
            state_.addParameterListener(OscillatorTypeParameter::identifier(), this);
            state_.addParameterListener(PitchShiftParameter::identifier(), this);
            state_.addParameterListener(PulseWidthParameter::identifier(), this);
        }

        OscillatorVoice::~OscillatorVoice()
        {
            state_.removeParameterListener(OscillatorTypeParameter::identifier(), this);
            state_.removeParameterListener(PitchShiftParameter::identifier(), this);
            state_.removeParameterListener(PulseWidthParameter::identifier(), this);
        }

        void OscillatorVoice::parameterChanged(juce::String const&parameterID, float newValue)
        {

        }

        bool OscillatorVoice::canPlaySound(juce::SynthesiserSound *sound)
        {
            juce::ignoreUnused(sound);

            return true;
        }

        void OscillatorVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
        {
            juce::ignoreUnused(sound);

            velocity_ = static_cast<double>(velocity) * 0.8;
            pitchFrequency_ = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
            modulo_ = 0.0;

            pitchWheelAdjust(currentPitchWheelPosition);
        }

        void OscillatorVoice::stopNote(float velocity, bool allowTailOff)
        {
            juce::ignoreUnused(velocity);
            juce::ignoreUnused(allowTailOff);

            if (allowTailOff)
            {
                if (tailOff_ == 0.0)
                {
                    tailOff_ = 1.0;
                }
            }
            else
            {
                SynthesiserVoice::clearCurrentNote();
                reset();
            }
        }

        void OscillatorVoice::pitchWheelMoved(int newPitchWheelValue)
        {
            pitchWheelAdjust(newPitchWheelValue);
        }

        void OscillatorVoice::controllerMoved(int controllerNumber, int newControllerValue)
        {
            juce::ignoreUnused(controllerNumber);
            juce::ignoreUnused(newControllerValue);
        }

        void OscillatorVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
        {
            if (pitchFrequency_ != 0.0)
            {
                int const numChannels = outputBuffer.getNumChannels();
                int sampleIdx{};
                float currentSample = 0.0f;

                do
                {
                    int channelIdx{};

                    if (tailOff_ != 0.0)
                    {
                        tailOff_ *= 0.99;

                        if (tailOff_ <= 0.05)
                        {
                            clearCurrentNote();
                            reset();
                            break;
                        }

                        currentSample = static_cast<float>(nextSample() * tailOff_);
                    }
                    else
                    {
                        currentSample = static_cast<float>(nextSample());
                    }

                    do
                    {
                        outputBuffer.addSample(channelIdx, startSample + sampleIdx, currentSample);
                        ++channelIdx;
                    } while(channelIdx < numChannels);
    
                    ++sampleIdx;
                } while (sampleIdx < numSamples);
            }
        }

        void OscillatorVoice::reset(void)
        {
            pitchFrequency_ = 0.0;
            delta_ = 0.0;
            tailOff_ = 0.0;
            modulo_ = 0.0;
        }

        double OscillatorVoice::nextSample(void)
        {
            double sample;

            switch (type_)
            {
            case wave_type::sinusoid:
                sample = std::sin(modulo_ * 2.0 * M_PI);
                break;
            case wave_type::sawtooth:
                sample = (modulo_ * 2.0) - 1.0;
                break;
            case wave_type::square:
                sample = (modulo_ > pulseWidth_) ? 1.0 : -1.0;
                break;
            case wave_type::triangle:
                sample = (2.0 * abs((2.0 * modulo_) - 1.0)) - 1.0;
                break;
            }

            modulo_ += delta_;

            if (modulo_ > 1.0)
                modulo_ -= 1.0;

            return sample * velocity_;
        }

        void OscillatorVoice::pitchWheelAdjust(int pitchWheelValue)
        {
            if (pitchWheelValue == 0x2000)
            {
                delta_ = pitchFrequency_ / SynthesiserVoice::getSampleRate();
            }
            else
            {
                double semitones = static_cast<double>(pitchWheelValue - INT32_C(0x2000)) / 4096.0;
                double frequency_adjust = std::exp2(static_cast<double>(semitones) / 12.0);

                delta_ = (pitchFrequency_ * frequency_adjust) / SynthesiserVoice::getSampleRate();
            }
        }

        OscillatorVoice::wave_type OscillatorVoice::getOscillatorType() const
        {
            return type_;
        }

        double OscillatorVoice::getPulseWidth() const
        {
            return pulseWidth_;
        }

        double OscillatorVoice::getPitchShift() const
        {
            return pitchShift_;
        }

        void OscillatorVoice::setOscillatorType(OscillatorVoice::wave_type type)
        {

        }

        void OscillatorVoice::setPitchShift(double v)
        {

        }

        void OscillatorVoice::setPulseWidth(double v)
        {

        }
    }
}