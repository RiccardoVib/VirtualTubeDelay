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
    
    inline std::string createTextForDelays(double value){
        
        std::string valueText = std::to_string(value);
        valueText.erase(5);
        valueText.append(" ms");
        return valueText;
    }
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    
private:
    
    VirtualTubeDelayAudioProcessor& processor;
    
    Label tubeLengthLeftLabel_, tubeLengthRightLabel_, gainLeftLabel_, gainRightLabel_, tubeSizeLabel_, dryWetMixLabel_, tubeLengthRefLeftLabel_, tubeLengthRefRightLabel_, gainRefLeftLabel_, gainRefRightLabel_, multitapDelayLabel_;
    
    Label feedbackLabel_, dampLabel_, tempoLabel_, syncLabel_;
    
    Slider tubeLengthLeftSlider_, tubeLengthRightSlider_, gainLeftSlider_, gainRightSlider_, tubeSizeSlider_, dryWetMixSlider_, tubeLengthRefLeftSlider_, tubeLengthRefRightSlider_, gainRefLeftSlider_, gainRefRightSlider_;
    
    Slider feedbackSlider_, dampSlider_, tempoSlider_;
    
    ToggleButton multitapDelayToggleButton_, syncToggleButton_;
    
    TextEditor delayMsL_, delayMsR_, delayMsRefL_, delayMsRefR_, gainText_, gainRefText_, tubeLengthText_, tubeEndText_, tempoText_;
    
    
    SliderAttachment* tubeLengthLeftAttachment;
    SliderAttachment* tubeLengthRightAttachment;
    SliderAttachment* gainLeftAttachment;
    SliderAttachment* gainRightAttachment;
    SliderAttachment* tubeSizeAttachment;
    SliderAttachment* dryWetMixAttachment;
    SliderAttachment* tubeLengthRefLeftAttachment;
    SliderAttachment* tubeLengthRefRightAttachment;
    SliderAttachment* gainRefLeftAttachment;
    SliderAttachment* gainRefRightAttachment;
    SliderAttachment* feedbackAttachment;
    SliderAttachment* tempoAttachment;
    
    //ButtonAttachment* multitapAttachment;
    //ButtonAttachment* syncAttachment;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VirtualTubeDelayAudioProcessorEditor)
};
