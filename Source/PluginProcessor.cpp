/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DRUMSHAM_2AudioProcessor::DRUMSHAM_2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), parameters(*this, nullptr, "PARAMETERS", initializeGUI())
#endif
{
    audioFormatManager.registerBasicFormats();
}

DRUMSHAM_2AudioProcessor::~DRUMSHAM_2AudioProcessor()
{

}
juce::AudioProcessorValueTreeState::ParameterLayout DRUMSHAM_2AudioProcessor::initializeGUI()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterChoice>("COMBO_ID", "COMBO_NAME", juce::StringArray("Hip-Hop", "Reggaeton"), 0));

    params.push_back(std::make_unique<juce::AudioParameterChoice>("COMBO2_ID", "COMBO2_NAME", juce::StringArray("Pattern 1", "Pattern 2", "Pattern 3"), 0));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("gain",
        "Gain",
        juce::NormalisableRange<float>(0.1f, 10.0f, 0.01f),
        1.0f));

    return { params.begin(), params.end() };

}

//==============================================================================
const juce::String DRUMSHAM_2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DRUMSHAM_2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DRUMSHAM_2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DRUMSHAM_2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DRUMSHAM_2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DRUMSHAM_2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DRUMSHAM_2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void DRUMSHAM_2AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DRUMSHAM_2AudioProcessor::getProgramName (int index)
{
    return {};
}

void DRUMSHAM_2AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DRUMSHAM_2AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    transportSource.prepareToPlay(samplesPerBlock, sampleRate);


}

void DRUMSHAM_2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    transportSource.releaseResources();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DRUMSHAM_2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DRUMSHAM_2AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

   
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    if (isPlaying == true)
    {
        DBG("Is Playing");
        if (audioFileSource != nullptr)
        {
            DBG("Audio File Source");
            transportSource.start();
        }
        isPlaying = false;
    }
    /*else
    {
        transportSource.stop();
        transportSource.setPosition(0.0);
    }*/


    transportSource.getNextAudioBlock(juce::AudioSourceChannelInfo(buffer));

    transportSource.setGain(parameters.getRawParameterValue("gain")->load());


}
//==============================================================================
bool DRUMSHAM_2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DRUMSHAM_2AudioProcessor::createEditor()
{
    return new DRUMSHAM_2AudioProcessorEditor (*this,parameters);
}

//==============================================================================
void DRUMSHAM_2AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DRUMSHAM_2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}




//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DRUMSHAM_2AudioProcessor();
}

void DRUMSHAM_2AudioProcessor::loadFile(juce::File myFile)
{
    transportSource.stop();
    //transportSource.setPosition(0.0);
    transportSource.setSource(nullptr);
    audioFileSource = nullptr;

   
    DBG("Path Name" << myFile.getFullPathName());

    juce::AudioFormatReader* reader = audioFormatManager.createReaderFor(myFile);

    if (reader != nullptr)
    {
        DBG("READER");
        audioFileSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
        transportSource.setSource(audioFileSource.get());
    }

}
void DRUMSHAM_2AudioProcessor::playFile()
{
    isPlaying = true;
}

