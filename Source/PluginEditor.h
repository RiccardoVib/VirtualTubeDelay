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
    
    inline std::string createTextForDelays(float value){
        
        std::string valueText = std::to_string(value);
        valueText.erase(5);
        valueText.append(" ms");
        return valueText;
    }
    
    inline std::string createTextForTempo(float value){
    
        int eraseNumber;
    
        if(value < 10){ eraseNumber = 10; }
        else{ eraseNumber = 11; }
    
        std::string tempoText = "Tempo: 1/";
        tempoText.append(std::to_string(value));
        tempoText.erase(eraseNumber);
        
        return tempoText;
    }
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    
private:
    
    VirtualTubeDelayAudioProcessor& processor;
    
    Label tubeLengthLeftLabel_, tubeLengthRightLabel_, gainLeftLabel_, gainRightLabel_, tubeSizeLabel_, dryWetMixLabel_, tubeEndLeftLabel_, tubeEndRightLabel_, gainRefLeftLabel_, gainRefRightLabel_, multitapDelayLabel_;
    
    Label feedbackLabel_, tempoLabel_, syncLabel_;
    
    Slider tubeLengthLeftSlider_, tubeLengthRightSlider_, gainLeftSlider_, gainRightSlider_, tubeSizeSlider_, dryWetMixSlider_, tubeEndLeftSlider_, tubeEndRightSlider_, gainRefLeftSlider_, gainRefRightSlider_;
    
    Slider feedbackSlider_, tempoSlider_;
    
    ToggleButton multitapDelayToggleButton_, syncToggleButton_;
    
    TextEditor delayMsL_, delayMsR_, delayMsRefL_, delayMsRefR_, gainText_, gainRefText_, tubeLengthText_, tubeEndText_, tempoText_;
    
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tubeLengthLeftAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tubeLengthRightAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainLeftAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainRightAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tubeSizeAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> dryWetMixAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tubeEndLeftAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tubeEndRightAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainRefLeftAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainRefRightAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> tempoAttachment;
    
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> multitapAttachment;
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> syncAttachment;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VirtualTubeDelayAudioProcessorEditor)
};
