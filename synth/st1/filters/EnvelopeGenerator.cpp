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

            if (auto parameter = state_.getParameter(EnvelopeAttackParameter::identifier()))
            {
                setAttackDuration(static_cast<double>(parameter->convertFrom0to1(parameter->getValue())));
            }

            if (auto parameter = state_.getParameter(EnvelopeDecayParameter::identifier()))
            {
                setDecayDuration(static_cast<double>(parameter->convertFrom0to1(parameter->getValue())));
            }

            if (auto parameter = state_.getParameter(EnvelopeSustainParameter::identifier()))
            {
                setSustainLevel(static_cast<double>(parameter->convertFrom0to1(parameter->getValue())));
            }

            if (auto parameter = state_.getParameter(EnvelopeReleaseParameter::identifier()))
            {
                setReleaseDuration(static_cast<double>(parameter->convertFrom0to1(parameter->getValue())));
            }
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
            if (parameterID == EnvelopeAttackParameter::identifier())
            {
                setAttackDuration(static_cast<double>(newValue));
            }
            else if (parameterID == EnvelopeDecayParameter::identifier())
            {
                setDecayDuration(static_cast<double>(newValue));
            }
            else if (parameterID == EnvelopeSustainParameter::identifier())
            {
                setSustainLevel(static_cast<double>(newValue));
            }
            else if (parameterID == EnvelopeReleaseParameter::identifier())
            {
                setReleaseDuration(static_cast<double>(newValue));
            }
        }

        void EnvelopeGenerator::setAttackDuration(double milliseconds)
        {
            envelope_.set_attack_duration(milliseconds);
        }

        void EnvelopeGenerator::setDecayDuration(double milliseconds)
        {
            envelope_.set_decay_duration(milliseconds);
        }

        void EnvelopeGenerator::setReleaseDuration(double milliseconds)
        {
            envelope_.set_release_duration(milliseconds);
        }

        void EnvelopeGenerator::setSustainLevel(double level)
        {
            envelope_.set_sustain_level(level);
        }
    }
}
