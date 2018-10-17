/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class VirtualTubeDelayAudioProcessorEditor  : public AudioProcessorEditor,
                                              private Slider::Listener

{
public:
    VirtualTubeDelayAudioProcessorEditor (VirtualTubeDelayAudioProcessor&);
    ~VirtualTubeDelayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider*) override;
    
    
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VirtualTubeDelayAudioProcessor& processor;
    
    Label tubeLengthLeftLabel_, tubeLengthRightLabel_, gainLeftLabel_, gainRightLabel_, tubeSizeLabel_, dryWetMixLabel_;
    
    Slider tubeLengthLeftSlider_, tubeLengthRightSlider_, gainLeftSlider_, gainRightSlider_, tubeSizeSlider_, dryWetMixSlider_;
           

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VirtualTubeDelayAudioProcessorEditor)
};
