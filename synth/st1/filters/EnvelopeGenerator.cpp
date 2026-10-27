#include "EnvelopeGenerator.hpp"

namespace st1
{
    namespace filters
    {
        struct AttackParameter
        {
        public:
            static juce::String const identifier()
            {
                static juce::String const identifier_ = "EGAT";
                return identifier_;
            }

            static std::unique_ptr<juce::AudioParameterFloat> create(juce::String const &name)
            {
                return std::make_unique<juce::AudioParameterFloat>(
                    juce::ParameterID(identifier(), 1),
                    name,
                    juce::NormalisableRange<float>(static_cast<float>(0.0), static_cast<float>(1.0), 0.1),
                    1.0,
                    juce::AudioParameterFloatAttributes()
                        .withLabel("Attack")
                        .withCategory(juce::AudioProcessorParameter::Category::genericParameter)
                );
            }

        private:
        };

        struct DecayParameter
        {
        public:
            static juce::String const identifier()
            {
                static juce::String const identifier_ = "EGDE";
                return identifier_;
            }

            static std::unique_ptr<juce::AudioParameterFloat> create(juce::String const &name)
            {
                return std::make_unique<juce::AudioParameterFloat>(
                    juce::ParameterID(identifier(), 1),
                    name,
                    juce::NormalisableRange<float>(static_cast<float>(0.0), static_cast<float>(1.0), 0.1),
                    1.0,
                    juce::AudioParameterFloatAttributes()
                        .withLabel("Decay")
                        .withCategory(juce::AudioProcessorParameter::Category::genericParameter)
                );
            }

        private:
        };

        struct SustainParameter
        {
        public:
            static juce::String const identifier()
            {
                static juce::String const identifier_ = "EGSU";
                return identifier_;
            }

            static std::unique_ptr<juce::AudioParameterFloat> create(juce::String const &name)
            {
                return std::make_unique<juce::AudioParameterFloat>(
                    juce::ParameterID(identifier(), 1),
                    name,
                    juce::NormalisableRange<float>(static_cast<float>(0.0), static_cast<float>(1.0), 0.1),
                    1.0,
                    juce::AudioParameterFloatAttributes()
                        .withLabel("Sustain")
                        .withCategory(juce::AudioProcessorParameter::Category::genericParameter)
                );
            }

        private:
        };

        struct ReleaseParameter
        {
        public:
            static juce::String const identifier()
            {
                static juce::String const identifier_ = "EGRE";
                return identifier_;
            }

            static std::unique_ptr<juce::AudioParameterFloat> create(juce::String const &name)
            {
                return std::make_unique<juce::AudioParameterFloat>(
                    juce::ParameterID(identifier(), 1),
                    name,
                    juce::NormalisableRange<float>(static_cast<float>(0.0), static_cast<float>(1.0), 0.1),
                    1.0,
                    juce::AudioParameterFloatAttributes()
                        .withLabel("Release")
                        .withCategory(juce::AudioProcessorParameter::Category::genericParameter)
                );
            }

        private:
        };

        std::unique_ptr<juce::AudioProcessorParameterGroup> EnvelopeGenerator::parameters(juce::String const &name)
        {
            return std::make_unique<juce::AudioProcessorParameterGroup>(
                juce::String("EVPG"),
                juce::String("envelope"),
                juce::String("|"),
                AttackParameter::create("attack"),
                DecayParameter::create("decay"),
                SustainParameter::create("sustain"),
                ReleaseParameter::create("release")
            );
        }
    }
}
