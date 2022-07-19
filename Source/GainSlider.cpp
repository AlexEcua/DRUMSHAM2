/*
  ==============================================================================

    GainSlider.cpp
    Created: 12 Jul 2022 6:15:58pm
    Author:  lenin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GainSlider.h"

//==============================================================================
GainSlider::GainSlider(juce::AudioProcessorValueTreeState& apvts) : parameters(apvts)
{
    vSlider.reset(new juce::Slider("GainSlider"));
    vSlider->setSliderStyle(juce::Slider::LinearHorizontal);
    vSlider->addListener(this);
    sliderAttachment = std::make_unique<SliderAttachment>(parameters, "gain", *vSlider);
    vSlider->setValue(parameters.getRawParameterValue("gain")->load());
    addAndMakeVisible(vSlider.get());


}

GainSlider::~GainSlider()
{
    sliderAttachment.reset();
    vSlider = nullptr;

}

void GainSlider::paint (juce::Graphics& g)
{
    
}

void GainSlider::resized()
{
    vSlider->setBoundsRelative(0, 0, 1, 1);

}
void GainSlider::sliderValueChanged(juce::Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == vSlider.get())
    {
    }
}

void GainSlider::enablementChanged()
{

}

