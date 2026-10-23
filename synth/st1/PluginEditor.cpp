#include "PluginEditor.hpp"
#include "PluginProcessor.hpp"

namespace st1
{
    namespace colours
    {
        static juce::Colour const foreground { 0xff95a468 };
        static juce::Colour const highlight { 0xff9b4d67 };
        static juce::Colour const background { 0xff190613 };
        static juce::Colour const text { 0xffe6e2e5 };
    }

    class SpicyLookAndFeel : public juce::LookAndFeel_V4
    {
    public:
        static SpicyLookAndFeel &instance()
        {
            static SpicyLookAndFeel instance_;
            return instance_;
        }

    private:
        SpicyLookAndFeel() :
            LookAndFeel_V4(juce::LookAndFeel_V4::ColourScheme{
                colours::background.getARGB(), // windowBackground
                0xff502634, // widgetBackground
                colours::background.getARGB(), // menuBackground
                colours::highlight.getARGB(), // outline
                colours::text.getARGB(), // defaultText
                colours::highlight.getARGB(), // defaultFill
                colours::text.getARGB(), // highlightedText
                colours::foreground.getARGB(), // highlightedFeel
                colours::text.getARGB(), // menuText
            })
        {
            #if 0
                this->setColour(juce::Slider::ColourIds::backgroundColourId, colours::background);
                this->setColour(juce::Slider::ColourIds::thumbColourId, colours::highlight);
                this->setColour(juce::Slider::ColourIds::trackColourId, colours::foreground);
                this->setColour(juce::Slider::ColourIds::rotarySliderFillColourId, colours::highlight);
                this->setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, colours::foreground);
                this->setColour(juce::Slider::ColourIds::textBoxTextColourId, colours::foreground);
                this->setColour(juce::Slider::ColourIds::textBoxBackgroundColourId, colours::background);
                this->setColour(juce::Slider::ColourIds::textBoxHighlightColourId, colours::highlight);
                this->setColour(juce::Slider::ColourIds::textBoxOutlineColourId, colours::highlight);
            #endif

            // this->setColour(juce::Label::outlineColourId, colours::background);
            // this->setColour(juce::HyperlinkButton::ColourIds::textColourId, colours::foreground);
        }
    };

    PluginEditor::PluginEditor(PluginProcessor &p) :
        juce::AudioProcessorEditor(p),
        oscillator_(p.state(), this)
    {
        AudioProcessorEditor::setLookAndFeel(&SpicyLookAndFeel::instance());
        AudioProcessorEditor::getLookAndFeel();

        AudioProcessorEditor::setOpaque(true);
        AudioProcessorEditor::setResizable(true, false);
        AudioProcessorEditor::setSize(400, 400);
    }

    void PluginEditor::paint(juce::Graphics &g)
    {
        g.fillAll(AudioProcessorEditor::getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    }

    void PluginEditor::resized(void)
    {
        oscillator_.setBounds(AudioProcessorEditor::getLocalBounds());
        // ev_.setBounds(super::getLocalBounds());
    }
}