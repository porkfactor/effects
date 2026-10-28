#ifndef ST1_OSCILLATOR_TYPE_PARAMETER_HPP_
#define ST1_OSCILLATOR_TYPE_PARAMETER_HPP_

#include <juce_audio_processors/juce_audio_processors.h>

namespace st1
{
    class OscillatorTypeParameter
    {
    public:
        static inline juce::String const sawtooth = "Sawtooth";
        static inline juce::String const sinusoid = "Sinusoid";
        static inline juce::String const square = "Square";
        static inline juce::String const triangle = "Triangle";

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
}

#endif
