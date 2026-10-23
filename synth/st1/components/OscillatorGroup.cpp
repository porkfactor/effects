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
            oscillator_.setBounds(GroupComponent::getBounds().reduced(40));
        }
    }
}