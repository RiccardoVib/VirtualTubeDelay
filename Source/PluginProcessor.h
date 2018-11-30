/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"
#include "DelayLine.h"

//==============================================================================
/**
*/

static double bufOut_L[7];
static double bufIn_L[7];

static double bufOut_R[7];
static double bufIn_R[7];

static double bufOut_Ref_L[7];
static double bufIn_Ref_L[7];

static double bufOut_Ref_R[7];
static double bufIn_Ref_R[7];

static double bufOut_Fin_L[4];
static double bufIn_Fin_L[4];

static double bufOut_Fin_R[4];
static double bufIn_Fin_R[4];

class VirtualTubeDelayAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    VirtualTubeDelayAudioProcessor();
    ~VirtualTubeDelayAudioProcessor();
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    
   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock(AudioBuffer<float>& buffer, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    // Adjustable parameters:
    float* tubeLengthLeft_ = nullptr; // Tube length in m
    float* tubeLengthRight_ = nullptr;
    float* gainLeft_ = nullptr; // Gain
    float* gainRight_ = nullptr;
    float* dryWetMix_ = nullptr; // Mix level of original and delayed signal (0-1)
    float* tubeSize_ = nullptr; // Size of the tube (1.2-2.5 cm)

    int multitapDelay_;
    bool multitap_;
    
    float* tubeLengthRefLeft_ = nullptr; // Tube length in m
    float* tubeLengthRefRight_ = nullptr;
    float* gainRefLeft_ = nullptr; // Gain
    float* gainRefRight_ = nullptr;
 
    
    int rad;
    double leng_L;
    double delayMilli_L;
    double delaySamples_L;
    
    double leng_R;
    double delayMilli_R;
    double delaySamples_R;
    
    double lengRef_L;
    double delayMilliRef_L;
    double delaySamplesRef_L;
    
    double lengRef_R;
    double delayMilliRef_R;
    double delaySamplesRef_R;
    
    Filter mFilter;
    DelayLine mDelayLine;
        
    float* feedback_ = nullptr;
    double damp_;
    float* tempo_ = nullptr;
    double tempoBpm_;
    double beatLenghtInSec;
    double beatLenghtInSamples;
    double tempoInSamples;
    bool sync_;// = nullptr;
    
    AudioProcessorValueTreeState parameters;
       
private:
    
    int delayBufferLength_;
    int delayBufferLengthRef_;
    
    AudioPlayHead* playHead;
    AudioPlayHead::CurrentPositionInfo currentPositionInfo;
    
    
     // Circular buffer variables for implementing delay
    //AudioBuffer<float> delayBufferLeft_2, delayBufferRight_2, delayBufferLeftRef_2, delayBufferRightRef_2;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VirtualTubeDelayAudioProcessor)
};
