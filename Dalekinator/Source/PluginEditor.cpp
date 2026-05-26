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
    frequencySlider.setRange (0.2, 20000.0, 0.01);
    frequencySlider.setSkewFactorFromMidPoint(0.2 * sqrt(100000.0)); // multiplicative midpoint
    frequencySlider.setTextValueSuffix (" Hz");
    frequencySlider.addListener (this);
    frequencySlider.setValue(audioProcessor.getOscillatorFrequency());
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
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));

    frequencySlider.setBounds(getLocalBounds());
}

void DalekinatorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
