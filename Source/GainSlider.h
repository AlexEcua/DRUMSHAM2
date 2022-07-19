/*
  ==============================================================================

    GainSlider.h
    Created: 12 Jul 2022 6:15:58pm
    Author:  lenin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class GainSlider  : public juce::Component, public juce::Slider::Listener

{
public:
    GainSlider(juce::AudioProcessorValueTreeState& apvts);
    ~GainSlider() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* sliderThatWasMoved) override;
    void enablementChanged() override;


private:

    std::unique_ptr<juce::Slider> vSlider;
    juce::AudioProcessorValueTreeState& parameters;
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> sliderAttachment{ nullptr };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainSlider)
};
