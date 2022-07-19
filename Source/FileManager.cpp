/*
  ==============================================================================

    FileManager.cpp
    Created: 4 Jul 2022 5:49:03pm
    Author:  lenin

  ==============================================================================
*/

#include <JuceHeader.h>

struct FileManager
{
    static juce::File getApplicationDataDirectory()
    {
        auto file = juce::File::getSpecialLocation(juce::File::commonApplicationDataDirectory)
            .getChildFile("PluginDesign")
            .getChildFile("audios");


        return file;
    }

    static juce::String getPathGenre(int a_index)
    {
        if (a_index == 1)
            return "HIP-HOP";
        if (a_index == 2)
            return "REGGAETON";
    }

    static juce::String getFileNameMP3(int a_index)
    {
        if (a_index == 1)
            return "Audio1.mp3";
        if (a_index == 2)
            return "Audio2.mp3";
        if (a_index == 3)
            return "Audio3.mp3";
    }

};