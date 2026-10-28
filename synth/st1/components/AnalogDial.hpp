#ifndef ST1_COMPONENTS_ANALOG_DIAL_HPP_
#define ST1_COMPONENTS_ANALOG_DIAL_HPP_

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

namespace st1
{
    namespace components
    {
        class AnalogDial :
            public juce::Component
        {
        public:
            AnalogDial(juce::String const &name, juce::String const &label = juce::String());

            void resized(void) override;

            void attach(juce::RangedAudioParameter *parameter, juce::UndoManager *undoManager = nullptr);
            void attach(juce::AudioProcessorValueTreeState &s, juce::StringRef parameterId);

        private:
            juce::Slider slider_;
            juce::Label label_;
            std::unique_ptr<juce::SliderParameterAttachment> attachment_;
        };
    }
}

#endif
