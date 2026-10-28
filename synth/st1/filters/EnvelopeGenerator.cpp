#include "EnvelopeGenerator.hpp"

#include <parameters/EnvelopeAttackParameter.hpp>
#include <parameters/EnvelopeDecayParameter.hpp>
#include <parameters/EnvelopeSustainParameter.hpp>
#include <parameters/EnvelopeReleaseParameter.hpp>

namespace st1
{
    namespace filters
    {
        std::unique_ptr<juce::AudioProcessorParameterGroup> EnvelopeGenerator::parameters(juce::String const &name)
        {
            return std::make_unique<juce::AudioProcessorParameterGroup>(
                juce::String("EVPG"),
                name,
                juce::String("|"),
                EnvelopeAttackParameter::create("attack"),
                EnvelopeDecayParameter::create("decay"),
                EnvelopeSustainParameter::create("sustain"),
                EnvelopeReleaseParameter::create("release")
            );
        }

        EnvelopeGenerator::EnvelopeGenerator(juce::AudioProcessorValueTreeState &s) :
            state_(s)
        {
            state_.addParameterListener(EnvelopeAttackParameter::identifier(), this);
            state_.addParameterListener(EnvelopeDecayParameter::identifier(), this);
            state_.addParameterListener(EnvelopeSustainParameter::identifier(), this);
            state_.addParameterListener(EnvelopeReleaseParameter::identifier(), this);
        }

        EnvelopeGenerator::~EnvelopeGenerator()
        {
            state_.removeParameterListener(EnvelopeAttackParameter::identifier(), this);
            state_.removeParameterListener(EnvelopeDecayParameter::identifier(), this);
            state_.removeParameterListener(EnvelopeSustainParameter::identifier(), this);
            state_.removeParameterListener(EnvelopeReleaseParameter::identifier(), this);
        }

        void EnvelopeGenerator::parameterChanged(juce::String const &parameterID, float newValue)
        {
            juce::ignoreUnused(parameterID);
            juce::ignoreUnused(newValue);
        }
    }
}
