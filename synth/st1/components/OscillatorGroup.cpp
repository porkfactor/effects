#include "OscillatorGroup.hpp"

namespace st1
{
    namespace components
    {
        OscillatorGroup::OscillatorGroup(juce::AudioProcessorValueTreeState &s, juce::String const &name, juce::String const &title) :
            GroupComponent(name, title),
            oscillator_(s, name + ".editor")
        {
            GroupComponent::addAndMakeVisible(oscillator_);
        }

        void OscillatorGroup::resized(void)
        {
            /**
             * the base OscillatorGroup component doesn't propagate the drawing
             * space to the child for some reason.
             */
            oscillator_.setBounds(GroupComponent::getLocalBounds().reduced(20));
        }
    }
}
