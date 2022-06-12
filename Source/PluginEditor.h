/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class DRUMSHAM_2AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DRUMSHAM_2AudioProcessorEditor (DRUMSHAM_2AudioProcessor&);
    ~DRUMSHAM_2AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void createGUI();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    juce::ComboBox menu{ "Select Genre:" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> miComboBoxAttachment;


    juce::Slider gainSlider;

    juce::ComboBox pattern{ "Choose Pattern:" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> elComboBoxAttachment;
    
    DRUMSHAM_2AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DRUMSHAM_2AudioProcessorEditor)
};
