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
    
    createGUI();
    addAndMakeVisible(gainSlider);
    addAndMakeVisible(button1);
    addAndMakeVisible(button2);

    setSize (400, 400);
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

    button1.setBounds(210, 300, getWidth() - 250, 30);
    button2.setBounds(40, 300, getWidth() - 250, 30);

    gainSlider.setBounds(90, 240, getWidth() - 170, 20);
}

void DRUMSHAM_2AudioProcessorEditor::createGUI()
{
    addAndMakeVisible(menu);
    menu.setText("Select Genre:");
    menu.addItem("Hip-Hop", 1);
    menu.addItem("Reggaeton", 2);
    menu.setJustificationType(juce::Justification::centred);
    menu.setBounds(80, getWidth() + 60, 250, 25);


    miComboBoxAttachment = std::make_unique < juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.parameters, "COMBO_ID", menu);

    addAndMakeVisible(pattern);
    pattern.setText("Choose Pattern:");
    pattern.addItem("Pattern 1", 1);
    pattern.addItem("Pattern 2", 2);
    pattern.addItem("Pattern 3", 3);
    pattern.setJustificationType(juce::Justification::centred);
    pattern.setBounds(80, getWidth() + 110, 250, 25);

    elComboBoxAttachment = std::make_unique < juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.parameters, "COMBO2_ID", pattern);


}
