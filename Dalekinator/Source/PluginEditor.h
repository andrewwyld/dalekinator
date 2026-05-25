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
class DalekinatorAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener
{
public:
    DalekinatorAudioProcessorEditor (DalekinatorAudioProcessor&);
    ~DalekinatorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DalekinatorAudioProcessor& audioProcessor;
    juce::Slider frequencySlider;

    void sliderValueChanged(juce::Slider* s) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DalekinatorAudioProcessorEditor)
};
