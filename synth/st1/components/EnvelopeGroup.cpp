#include "EnvelopeGroup.hpp"

namespace st1
{
    namespace components
    {
        EnvelopeGroup::EnvelopeGroup(juce::AudioProcessorValueTreeState &s, juce::String const &name, juce::String const &title) :
            GroupComponent(name, title),
            envelope_(s, name + ".envelope")
        {

        }

        EnvelopeGroup::~EnvelopeGroup()
        {

        }

        void EnvelopeGroup::resized(void)
        {
            envelope_.setBounds(GroupComponent::getLocalBounds().reduced(20));
        }
    }
}