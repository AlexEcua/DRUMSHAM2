/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "FileManager.cpp"
#include "GainSlider.h"


//==============================================================================
/**
*/
class DRUMSHAM_2AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DRUMSHAM_2AudioProcessorEditor (DRUMSHAM_2AudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~DRUMSHAM_2AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void createGUI();

    juce::AudioProcessorValueTreeState& parameters;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.


    juce::ComboBox menu{ "Select Genre:" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> miComboBoxAttachment;

    juce::ComboBox pattern{ "Choose Pattern" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> elComboBoxAttachment;
    

    juce::TextButton button1{"Export MIDI Master Audio"};
    juce::TextButton button2{ "Export Master Audio" };

    juce::File mainDirectory;
    juce::String genreString = "HIP-HOP";
    juce::String patternString = "Audio1";

    void updatePath();
    
    std::unique_ptr<GainSlider> gainSlider{ nullptr };
    
    


    DRUMSHAM_2AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DRUMSHAM_2AudioProcessorEditor)
};
