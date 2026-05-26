/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DalekinatorAudioProcessorEditor::DalekinatorAudioProcessorEditor (DalekinatorAudioProcessor& p)
: AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    addAndMakeVisible(frequencySlider);
    frequencySlider.setRange (20.0, 20000.0);
    frequencySlider.setSkewFactorFromMidPoint(20.0 * sqrt(1000.0)); // multiplicative midpoint
    frequencySlider.setTextValueSuffix (" Hz");
    frequencySlider.addListener (this);
    frequencySlider.setValue(DALEK_MODULATION_SPEED_HZ);
}

DalekinatorAudioProcessorEditor::~DalekinatorAudioProcessorEditor()
{
}

void DalekinatorAudioProcessorEditor::sliderValueChanged(juce::Slider* s)
{
    if (s == &frequencySlider)
    {
        audioProcessor.setOscillatorFrequency(frequencySlider.getValue());
    }
}

//==============================================================================
void DalekinatorAudioProcessorEditor::paint (juce::Graphics& g)
{
    frequencySlider.setBounds(getLocalBounds());
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // g.setColour (juce::Colours::white);
    // g.setFont (juce::FontOptions (15.0f));
    // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void DalekinatorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
