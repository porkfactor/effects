#include "EnvelopeEditor.hpp"

#include <parameters/EnvelopeAttackParameter.hpp>
#include <parameters/EnvelopeDecayParameter.hpp>
#include <parameters/EnvelopeSustainParameter.hpp>
#include <parameters/EnvelopeReleaseParameter.hpp>

namespace st1
{
    namespace components
    {
        EnvelopeEditor::EnvelopeEditor(juce::AudioProcessorValueTreeState &s, juce::String const &name) :
            juce::Component(name),
            envelope_(s, name + ".envelope"),
            attackDial_(name + ".attack", "Attack"),
            decayDial_(name + ".decay", "Decay"),
            sustainDial_(name + ".sustain", "Sustain"),
            releaseDial_(name + ".release", "Release")
        {
            attackDial_.attach(s, EnvelopeAttackParameter::identifier());
            decayDial_.attach(s, EnvelopeDecayParameter::identifier());
            sustainDial_.attach(s, EnvelopeSustainParameter::identifier());
            releaseDial_.attach(s, EnvelopeReleaseParameter::identifier());

            Component::addAndMakeVisible(envelope_);
            Component::addAndMakeVisible(attackDial_);
            Component::addAndMakeVisible(decayDial_);
            Component::addAndMakeVisible(sustainDial_);
            Component::addAndMakeVisible(releaseDial_);
        }

        void EnvelopeEditor::resized(void)
        {
            auto bounds = Component::getLocalBounds();
            auto width = bounds.getWidth();

            envelope_.setBounds(bounds.removeFromTop(100));

            attackDial_.setBounds(bounds.removeFromLeft(width / 4));
            decayDial_.setBounds(bounds.removeFromLeft(width / 4));
            sustainDial_.setBounds(bounds.removeFromLeft(width / 4));
            releaseDial_.setBounds(bounds.removeFromLeft(width / 4));
        }
    }
}
