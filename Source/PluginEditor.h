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
                                              private Slider::Listener,
                                              private Button::Listener

{
public:
    VirtualTubeDelayAudioProcessorEditor (VirtualTubeDelayAudioProcessor&);
    ~VirtualTubeDelayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider*) override;
    void buttonClicked (Button* button) override;
    
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VirtualTubeDelayAudioProcessor& processor;
    
    Label tubeLengthLeftLabel_, tubeLengthRightLabel_, gainLeftLabel_, gainRightLabel_, tubeSizeLabel_, dryWetMixLabel_, enabledReflectionLabel_, enabledVibratoLabel_, tubeLengthRefLeftLabel_, tubeLengthRefRightLabel_, gainRefLeftLabel_, gainRefRightLabel_, enabledVibratoToggleLabel_;
    
    Slider tubeLengthLeftSlider_, tubeLengthRightSlider_, gainLeftSlider_, gainRightSlider_, tubeSizeSlider_, dryWetMixSlider_, tubeLengthRefLeftSlider_, tubeLengthRefRightSlider_, gainRefLeftSlider_, gainRefRightSlider_;
    
    ToggleButton enabledReflectionToggleButton_, enabledVibratoToggleButton_;
    
    TextEditor delayMsL_, delayMsR_, delayMsRefL_, delayMsRefR_;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VirtualTubeDelayAudioProcessorEditor)
};
