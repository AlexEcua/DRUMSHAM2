/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DRUMSHAM_2AudioProcessorEditor::DRUMSHAM_2AudioProcessorEditor (DRUMSHAM_2AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(styleMenu);
    styleMenu.setText("Select Genre:");
    styleMenu.addItem("Hip-hop", 1);
    styleMenu.addItem("Reggaeton", 2);

    addAndMakeVisible(pattern);
    pattern.setText("Choose Pattern:");
    pattern.addItem("Pattern 1", 1);
    pattern.addItem("Pattern 2", 2);
    pattern.addItem("Pattern 3", 3);

    setSize (400, 500);
}

DRUMSHAM_2AudioProcessorEditor::~DRUMSHAM_2AudioProcessorEditor()
{
}

//==============================================================================
void DRUMSHAM_2AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawFittedText ("Welcome to DRUMSHAM!", getLocalBounds(), juce::Justification::centredTop, 1);
}

void DRUMSHAM_2AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
   
    styleMenu .setBounds (10, 45, getWidth() - 20, 30);
    pattern .setBounds (10, 90, getWidth() - 20, 30);
}
