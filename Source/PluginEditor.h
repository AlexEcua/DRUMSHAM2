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

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DRUMSHAM_2AudioProcessor& audioProcessor;

    juce::ComboBox styleMenu{ "Select Genre" };
    juce::ComboBox pattern{ "Choose Pattern" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DRUMSHAM_2AudioProcessorEditor)
};
