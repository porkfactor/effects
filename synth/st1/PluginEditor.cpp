#include "PluginEditor.hpp"
#include "PluginProcessor.hpp"

namespace st1
{
    PluginEditor::PluginEditor(PluginProcessor &p) :
        super(p)
    {
        super::setOpaque(true);
        super::addAndMakeVisible(ev_);

        super::setResizable(true, false);
        super::setSize(400, 400);
    }

    void PluginEditor::paint(juce::Graphics &g)
    {
        g.fillAll(super::getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    }

    void PluginEditor::resized(void)
    {
        ev_.setBounds(super::getLocalBounds());
    }
}