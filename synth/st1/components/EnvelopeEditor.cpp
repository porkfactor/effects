#include "EnvelopeEditor.hpp"

namespace st1
{
    namespace components
    {
        EnvelopeEditor::EnvelopeEditor(juce::AudioProcessorValueTreeState &s, juce::String const &name) :
            juce::Component(name),
            attackDial_(s.getParameter("EGAT"), name + ".attack", s.undoManager),
            decayDial_(s.getParameter("EGDE"), name + ".decay", s.undoManager),
            releaseDial_(s.getParameter("EGRE"), name + ".release", s.undoManager)
        {

        }

        void EnvelopeEditor::resized(void)
        {
            auto bounds = Component::getLocalBounds();
            // TODO: layout that shit. 
        }
    }
}
