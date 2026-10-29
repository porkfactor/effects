#ifndef ST1_ENVELOPE_DECAY_PARAMETER_HPP_
#define ST1_ENVELOPE_DECAY_PARAMETER_HPP_

#include <juce_audio_processors/juce_audio_processors.h>

namespace st1
{
    class EnvelopeDecayParameter
    {
    public:
        static juce::String const identifier()
        {
            static juce::String const identifier_ = "EVDE";
            return identifier_;
        }

        static std::unique_ptr<juce::AudioParameterFloat> create(juce::String const &name)
        {
            return std::make_unique<juce::AudioParameterFloat>(
                juce::ParameterID(identifier(), 1),
                name,
                juce::NormalisableRange<float>(0.0f, 1000.0f, 10.0f),
                70.0f,
                juce::AudioParameterFloatAttributes()
                    .withLabel("Decay")
                    .withCategory(juce::AudioProcessorParameter::Category::genericParameter)
                    .withStringFromValueFunction(std::bind(&EnvelopeDecayParameter::stringFromValue, std::placeholders::_1))
            );
        }

        static juce::String stringFromValue(float v)
        {
            return juce::String(v, 0) + " ms";
        }

    private:
    };
}

#endif
