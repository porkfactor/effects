cmake_minimum_required(VERSION 3.22)

juce_add_plugin(pf1
    # VERSION ...                               # Set this if the plugin version is different to the project version
    # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    # COMPANY_NAME ...                          # Specify the name of the plugin's author
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE                 
    # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE    
    # COPY_PLUGIN_AFTER_BUILD TRUE/FALSE        
    PLUGIN_MANUFACTURER_CODE ${JUCE_MANUFACTURER}
    PLUGIN_CODE Xpf1
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "PF1"
)

target_sources(pf1
    PRIVATE
        PluginEditor.cpp
        PluginProcessor.cpp
)

target_compile_definitions(pf1
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(pf1
    PRIVATE
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
