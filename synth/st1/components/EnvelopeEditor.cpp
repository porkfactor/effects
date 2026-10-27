#include "EnvelopeEditor.hpp"

namespace st1
{
    namespace components
    {
        EnvelopeEditor::EnvelopeEditor(juce::AudioProcessorValueTreeState &s, juce::String const &name) :
            juce::Component(name),
            attackDial_(name + ".attack", "Attack"),
            decayDial_(name + ".decay", "Decay"),
            sustainDial_(name + ".sustain", "Sustain"),
            releaseDial_(name + ".release", "Release")
        {
            attackDial_.attach(s, "EGAT");
            decayDial_.attach(s, "EGDE");
            sustainDial_.attach(s, "EGSU");
            releaseDial_.attach(s, "EGRE");

            Component::addAndMakeVisible(attackDial_);
            Component::addAndMakeVisible(decayDial_);
            Component::addAndMakeVisible(sustainDial_);
            Component::addAndMakeVisible(releaseDial_);
        }

        void EnvelopeEditor::resized(void)
        {
            auto bounds = Component::getLocalBounds();
            auto width = bounds.getWidth();

            attackDial_.setBounds(bounds.removeFromLeft(width / 4));
            decayDial_.setBounds(bounds.removeFromLeft(width / 4));
            sustainDial_.setBounds(bounds.removeFromLeft(width / 4));
            releaseDial_.setBounds(bounds.removeFromLeft(width / 4));
        }
    }
}
