/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DalekinatorAudioProcessor::DalekinatorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

DalekinatorAudioProcessor::~DalekinatorAudioProcessor()
{
}

//==============================================================================
const juce::String DalekinatorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DalekinatorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DalekinatorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DalekinatorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DalekinatorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DalekinatorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DalekinatorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DalekinatorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DalekinatorAudioProcessor::getProgramName (int index)
{
    return {};
}

void DalekinatorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DalekinatorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    this->sampleRate = sampleRate;
    calculateAngleMultiplier();
    lastAngle = 0;
}

void DalekinatorAudioProcessor::setOscillatorFrequency(float frequency)
{
    oscillatorFrequency = frequency;
    calculateAngleMultiplier();
}

float DalekinatorAudioProcessor::getOscillatorFrequency()
{
    return oscillatorFrequency;
}

void DalekinatorAudioProcessor::calculateAngleMultiplier()
{
    angleMultiplier = M_PI * oscillatorFrequency / sampleRate;
}

void DalekinatorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DalekinatorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void DalekinatorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    int numSamples = buffer.getNumSamples();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, numSamples);

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        auto* inputData = buffer.getReadPointer(channel);
        for (int i = 0; i < numSamples; ++i)
        {
            channelData[i] = inputData[i] * sin(lastAngle + i * angleMultiplier);
        }
    }
    
    lastAngle += angleMultiplier * (float) numSamples;
    while (lastAngle > M_TAU) // if overflowing
    {
        lastAngle -= M_TAU; // wrap
    }
}

//==============================================================================
bool DalekinatorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DalekinatorAudioProcessor::createEditor()
{
    return new DalekinatorAudioProcessorEditor (*this);
}

//==============================================================================
void DalekinatorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DalekinatorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DalekinatorAudioProcessor();
}
