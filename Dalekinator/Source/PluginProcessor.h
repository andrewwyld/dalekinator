/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#define DALEK_MODULATION_SPEED_HZ 30.f

#define OSCILLATOR_MINIMUM_HZ 0.2f // Hz
#define OSCILLATOR_MAXIMUM_HZ 20000.f // Hz
#define OSCILLATOR_INCREMENT_HZ 0.01f // Hz
#define OSCILLATOR_SKEW 63.24555 // geometric mean of max and min

//==============================================================================
/**
*/
class DalekinatorAudioProcessor  : public juce::AudioProcessor
{
public:
    constexpr static const double M_TAU = M_PI * 2.0;
    //==============================================================================
    DalekinatorAudioProcessor();
    ~DalekinatorAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    void setOscillatorFrequency(float frequency);
    float getOscillatorFrequency();

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DalekinatorAudioProcessor)
    
    juce::AudioParameterFloat* oscillatorFrequency;
    double sampleRate;
    float lastAngle;
    float angleMultiplier;

    void calculateAngleMultiplier();
};
