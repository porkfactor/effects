#ifndef ST1_ENVELOPE_RELEASE_PARAMETER_HPP_
#define ST1_ENVELOPE_RELEASE_PARAMETER_HPP_

#include <juce_audio_processors/juce_audio_processors.h>

namespace st1
{
    class EnvelopeReleaseParameter
    {
    public:
        static juce::String const identifier()
        {
            static juce::String const identifier_ = "EVRE";
            return identifier_;
        }

        static std::unique_ptr<juce::AudioParameterFloat> create(juce::String const &name)
        {
            return std::make_unique<juce::AudioParameterFloat>(
                juce::ParameterID(identifier(), 1),
                name,
                juce::NormalisableRange<float>(0.0f, 1.0f, 0.1f),
                1.0f,
                juce::AudioParameterFloatAttributes()
                    .withLabel("Amplitude")
                    .withCategory(juce::AudioProcessorParameter::Category::genericParameter)
            );
        }

    private:
    };
}

#endif
