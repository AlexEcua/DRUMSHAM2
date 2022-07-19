/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DRUMSHAM_2AudioProcessorEditor::DRUMSHAM_2AudioProcessorEditor (DRUMSHAM_2AudioProcessor& p, juce::AudioProcessorValueTreeState& apvts)
    : AudioProcessorEditor (&p), audioProcessor (p), parameters(apvts)
{
    
    createGUI();
    addAndMakeVisible(button1);
    addAndMakeVisible(button2);
    updatePath();
    audioProcessor.loadFile(mainDirectory);

    gainSlider = std::make_unique<GainSlider>(parameters);
    addAndMakeVisible(gainSlider.get());


    menu.onChange = [&]()
    {
        int comboBoxID = menu.getSelectedId();
        DBG(comboBoxID);
        genreString = FileManager::getPathGenre(comboBoxID);
        updatePath();
        audioProcessor.loadFile(mainDirectory);
        audioProcessor.playFile();


    };

    pattern.onChange = [&]()
    {
        int comboBoxID = pattern.getSelectedId();
        DBG(comboBoxID);
        patternString = FileManager::getFileNameMP3(comboBoxID);
        updatePath();
        audioProcessor.loadFile(mainDirectory);
        audioProcessor.playFile();
    };


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

    gainSlider->setBoundsRelative(0.0f, 0.6f, 0.8f, 0.2f);

   
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

void DRUMSHAM_2AudioProcessorEditor::updatePath()
{
    mainDirectory = FileManager::getApplicationDataDirectory().getChildFile(genreString).getChildFile(patternString);
}

