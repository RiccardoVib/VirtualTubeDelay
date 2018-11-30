/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Filter.h"

//==============================================================================
VirtualTubeDelayAudioProcessorEditor::VirtualTubeDelayAudioProcessorEditor (VirtualTubeDelayAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p),
        tubeLengthLeftLabel_("", "Left Channel:"), tubeLengthRightLabel_("", "Right Channel:"), gainLeftLabel_("", "Left Channel:"),
        gainRightLabel_("", "Right Channel:"), tubeSizeLabel_("", "Tube Size (cm):"), dryWetMixLabel_("", "Dry/Wet:"),
        multitapDelayLabel_("", "Multitap:"), syncLabel_("", "Sync:"),
        tubeLengthRefLeftLabel_("", "Left Channel:"),tubeLengthRefRightLabel_("", "Right Channel:"),
        gainRefLeftLabel_("", "Left Channel:"),gainRefRightLabel_("", "Right Channel:"),
        feedbackLabel_("", "Feedback:")//, dampLabel_("", "Damp:")
{
    
    setSize (800, 450);
    
    tubeLengthLeftAttachment = new SliderAttachment(processor.parameters, "tubeLengthLeft_", tubeLengthLeftSlider_);
    tubeLengthRightAttachment = new SliderAttachment(processor.parameters, "tubeLengthRight_", tubeLengthRightSlider_);
    gainLeftAttachment = new SliderAttachment(processor.parameters, "gainLeft_", gainLeftSlider_);
    gainRightAttachment = new SliderAttachment(processor.parameters, "gainRight_", gainRightSlider_);

    tubeSizeAttachment = new SliderAttachment(processor.parameters, "tubeSize_", tubeSizeSlider_);
    dryWetMixAttachment = new SliderAttachment(processor.parameters, "dryWetMix_", dryWetMixSlider_);
    tubeLengthRefLeftAttachment = new SliderAttachment(processor.parameters, "tubeLengthRefLeft_", tubeLengthRefLeftSlider_);
    tubeLengthRefRightAttachment = new SliderAttachment(processor.parameters, "tubeLengthRefRight_", tubeLengthRefRightSlider_);
    gainRefLeftAttachment = new SliderAttachment(processor.parameters, "gainRefLeft_", gainRefLeftSlider_);
    gainRefRightAttachment = new SliderAttachment(processor.parameters, "gainRefRight_", gainRefRightSlider_);
    feedbackAttachment = new SliderAttachment(processor.parameters, "feedback_", feedbackSlider_);
    tempoAttachment = new SliderAttachment(processor.parameters, "tempo_", tempoSlider_);
    
    //multitapAttachment = new ButtonAttachment(processor.parameters, "multitapDelay_", multitapDelayToggleButton_);
    //syncAttachment = new ButtonAttachment(processor.parameters, "sync_", syncToggleButton_);
    
    gainText_.setReadOnly(true);
    gainText_.setText("Gain Level");
    addAndMakeVisible (&gainText_);
    
    gainRefText_.setReadOnly(true);
    gainRefText_.setText("Reflection Level");
    addAndMakeVisible (&gainRefText_);
    
    tubeLengthText_.setReadOnly(true);
    tubeLengthText_.setText("Tube Length (m)");
    addAndMakeVisible(&tubeLengthText_);
    
    tubeEndText_.setReadOnly(true);
    tubeEndText_.setText("Tube End Distance (m)");
    addAndMakeVisible(&tubeEndText_);
    
    gainRefText_.setReadOnly(true);
    gainRefText_.setText("Gain Level (Reflection)");
    addAndMakeVisible (&gainRefText_);
    
    
    delayMsL_.setReadOnly(true);
    delayMsL_.setText("28,98 ms");
    addAndMakeVisible (&delayMsL_);
    
    delayMsR_.setReadOnly(true);
    delayMsR_.setText("28,98 ms");
    addAndMakeVisible (&delayMsR_);
    
    delayMsRefL_.setReadOnly(true);
    delayMsRefL_.setText("34,78 ms");
    addAndMakeVisible (&delayMsRefL_);
    
    delayMsRefR_.setReadOnly(true);
    delayMsRefR_.setText("34,78 ms");
    addAndMakeVisible (&delayMsRefR_);
    
    tempoText_.setReadOnly(true);
    tempoText_.setText("Tempo: 1/1");
    addAndMakeVisible (&tempoText_);
    
    tubeLengthLeftSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    tubeLengthLeftSlider_.setRange (2.0, 30.0, 0.01);
    tubeLengthLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeLengthLeftSlider_.setPopupDisplayEnabled(true, false, this);
    tubeLengthLeftSlider_.setTextValueSuffix(" m");
    //tubeLengthLeftSlider_.setValue(10.0);
    tubeLengthLeftSlider_.setDoubleClickReturnValue(true, 10.0);
    //tubeLengthLeftSlider_.setChangeNotificationOnlyOnRelease(true);
    addAndMakeVisible (&tubeLengthLeftSlider_);
    tubeLengthLeftSlider_.addListener(this);
    
    tubeLengthRightSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    tubeLengthRightSlider_.setRange (2.0, 30.0, 0.01);
    tubeLengthRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeLengthRightSlider_.setPopupDisplayEnabled (true, false, this);
    tubeLengthRightSlider_.setTextValueSuffix(" m");
    //tubeLengthRightSlider_.setValue(10.0);
    tubeLengthRightSlider_.setDoubleClickReturnValue(true, 10.0);
    //tubeLengthRightSlider_.setChangeNotificationOnlyOnRelease(true);
    addAndMakeVisible (&tubeLengthRightSlider_);
    tubeLengthRightSlider_.addListener(this);
    
    gainLeftSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    gainLeftSlider_.setRange (0.0, 10.0, 0.01);
    gainLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainLeftSlider_.setPopupDisplayEnabled (true, false, this);
    gainLeftSlider_.setTextValueSuffix(" dB");
    //gainLeftSlider_.setValue(2.0);
    gainLeftSlider_.setDoubleClickReturnValue(true, 2.0);
    addAndMakeVisible (&gainLeftSlider_);
    gainLeftSlider_.addListener(this);
    
    gainRightSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    gainRightSlider_.setRange (0.0, 10.0, 0.01);
    gainRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainRightSlider_.setPopupDisplayEnabled (true, false, this);
    gainRightSlider_.setTextValueSuffix(" dB");
    //gainRightSlider_.setValue(2.0);
    gainRightSlider_.setDoubleClickReturnValue(true, 2.0);
    addAndMakeVisible (&gainRightSlider_);
    gainRightSlider_.addListener(this);
    
    tubeSizeSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    tubeSizeSlider_.setRange (1.2, 2.5, 0.1);
    tubeSizeSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeSizeSlider_.setPopupDisplayEnabled (true, false, this);
    tubeSizeSlider_.setTextValueSuffix(" cm");
    //tubeSizeSlider_.setValue(0.0);
    tubeSizeSlider_.setDoubleClickReturnValue(true, 1.2);
    addAndMakeVisible (&tubeSizeSlider_);
    tubeSizeSlider_.addListener(this);
    
    dryWetMixSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    dryWetMixSlider_.setRange (0.0, 1.0, 0.01);
    dryWetMixSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    dryWetMixSlider_.setPopupDisplayEnabled (true, false, this);
    //dryWetMixSlider_.setValue(0.0);
    dryWetMixSlider_.setDoubleClickReturnValue(true, 0.0);
    addAndMakeVisible (&dryWetMixSlider_);
    dryWetMixSlider_.addListener(this);
    
    tubeLengthRefLeftSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    tubeLengthRefLeftSlider_.setRange (1.0, 5.0, 0.01);
    tubeLengthRefLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeLengthRefLeftSlider_.setPopupDisplayEnabled(true, false, this);
    tubeLengthRefLeftSlider_.setTextValueSuffix(" m");
    //tubeLengthRefLeftSlider_.setValue(1.0);
    tubeLengthRefLeftSlider_.setDoubleClickReturnValue(true, 10.0);
    //tubeLengthRefLeftSlider_.setChangeNotificationOnlyOnRelease(true);
    addAndMakeVisible (&tubeLengthRefLeftSlider_);
    tubeLengthRefLeftSlider_.addListener(this);
    
    tubeLengthRefRightSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    tubeLengthRefRightSlider_.setRange (1.0, 5.0, 0.01);
    tubeLengthRefRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeLengthRefRightSlider_.setPopupDisplayEnabled (true, false, this);
    tubeLengthRefRightSlider_.setTextValueSuffix(" m");
    //tubeLengthRefRightSlider_.setValue(1.0);
    tubeLengthRefRightSlider_.setDoubleClickReturnValue(true, 10.0);
    //tubeLengthRefRightSlider_.setChangeNotificationOnlyOnRelease(true);
    addAndMakeVisible (&tubeLengthRefRightSlider_);
    tubeLengthRefRightSlider_.addListener(this);
    
    gainRefLeftSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    gainRefLeftSlider_.setRange (0.0, 20.0, 0.01);
    gainRefLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainRefLeftSlider_.setPopupDisplayEnabled (true, false, this);
    gainRefLeftSlider_.setTextValueSuffix(" dB");
    //gainRefLeftSlider_.setValue(4.0);
    gainRefLeftSlider_.setDoubleClickReturnValue(true, 4.0);
    addAndMakeVisible (&gainRefLeftSlider_);
    gainRefLeftSlider_.addListener(this);
    
    gainRefRightSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    gainRefRightSlider_.setRange (0.0, 20.0, 0.01);
    gainRefRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainRefRightSlider_.setPopupDisplayEnabled (true, false, this);
    gainRefRightSlider_.setTextValueSuffix(" dB");
    //gainRefRightSlider_.setValue(4.0);
    gainRefRightSlider_.setDoubleClickReturnValue(true, 4.0);
    addAndMakeVisible (&gainRefRightSlider_);
    gainRefRightSlider_.addListener(this);
    
    tubeLengthLeftLabel_.attachToComponent(&tubeLengthLeftSlider_, false);
    tubeLengthLeftLabel_.setFont(Font (14.0f));
    tubeLengthRightLabel_.attachToComponent(&tubeLengthRightSlider_, false);
    tubeLengthRightLabel_.setFont(Font (14.0f));
    gainLeftLabel_.attachToComponent(&gainLeftSlider_, false);
    gainLeftLabel_.setFont(Font (14.0f));
    gainRightLabel_.attachToComponent(&gainRightSlider_, false);
    gainRightLabel_.setFont(Font (14.0f));
    //gainLeftLabel_.setColour(1, Colours::black);
    gainRightLabel_.attachToComponent(&gainRightSlider_, false);
    gainRightLabel_.setFont(Font (14.0f));
    tubeSizeLabel_.attachToComponent(&tubeSizeSlider_, false);
    tubeSizeLabel_.setFont(Font (14.0f));
    dryWetMixLabel_.attachToComponent(&dryWetMixSlider_, false);
    dryWetMixLabel_.setFont(Font (14.0f));
    
    tubeLengthRefLeftLabel_.attachToComponent(&tubeLengthRefLeftSlider_, false);
    tubeLengthRefLeftLabel_.setFont(Font (14.0f));
    tubeLengthRefRightLabel_.attachToComponent(&tubeLengthRefRightSlider_, false);
    tubeLengthRefRightLabel_.setFont(Font (14.0f));
    gainRefLeftLabel_.attachToComponent(&gainRefLeftSlider_, false);
    gainRefLeftLabel_.setFont(Font (14.0f));
    gainRefRightLabel_.attachToComponent(&gainRefRightSlider_, false);
    gainRefRightLabel_.setFont(Font (14.0f));
    //gainLeftLabel_.setColour(1, Colours::black);
    gainRefRightLabel_.attachToComponent(&gainRefRightSlider_, false);
    gainRefRightLabel_.setFont(Font (14.0f));
    
    
    //enabledReflectionToggleButton_.setRadioGroupId(0, sendNotification);
    //enabledRepeatedDelayToggleButton_.setRadioGroupId(0, sendNotification);
    
    //repeated
    
    feedbackSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    feedbackSlider_.setRange (0.1, 0.9, 0.01);
    feedbackSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    feedbackSlider_.setPopupDisplayEnabled (true, false, this);
    feedbackSlider_.setTextValueSuffix(" ");
    //feedbackSlider_.setValue(0.1);
    feedbackSlider_.setDoubleClickReturnValue(true, 0.1);
    addAndMakeVisible (&feedbackSlider_);
    feedbackSlider_.addListener(this);
    
    tempoSlider_.setSliderStyle(Slider:: RotaryHorizontalVerticalDrag);
    tempoSlider_.setRange (1, 30, 0.01);
    tempoSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tempoSlider_.setPopupDisplayEnabled (false, false, this);
    tempoSlider_.setTextValueSuffix(" ");
    //tempoSlider_.setValue(10);
    tempoSlider_.setDoubleClickReturnValue(true, 10);
    addAndMakeVisible (&tempoSlider_);
    tempoSlider_.addListener(this);
    
    syncToggleButton_.setButtonText("Off");
    syncToggleButton_.setClickingTogglesState(true);
    addAndMakeVisible (&syncToggleButton_);
    syncToggleButton_.addListener(this);
  
    syncLabel_.attachToComponent(&syncToggleButton_, false);
    syncLabel_.setFont(Font (14.0f));
    
    feedbackLabel_.attachToComponent(&feedbackSlider_, false);
    feedbackLabel_.setFont(Font (14.0f));
    
    multitapDelayToggleButton_.setButtonText("Off");
    multitapDelayToggleButton_.setClickingTogglesState(true);
    addAndMakeVisible (&multitapDelayToggleButton_);
    multitapDelayToggleButton_.addListener(this);
    
    multitapDelayLabel_.attachToComponent(&multitapDelayToggleButton_, false);
    multitapDelayLabel_.setFont(Font (14.0f));
    
}

VirtualTubeDelayAudioProcessorEditor::~VirtualTubeDelayAudioProcessorEditor()
{
    //delete tubeLengthRightAttachment, tubeLengthLeftAttachment, gainLeftAttachment, gainRightAttachment, tubeSizeAttachment, dryWetMixAttachment, tubeLengthRefLeftAttachment, tubeLengthRefRightAttachment, gainRefLeftAttachment, gainRefRightAttachment, feedbackAttachment, tempoAttachment, multitapAttachment, syncAttachment;
}

void VirtualTubeDelayAudioProcessorEditor::buttonClicked (Button* button)
{
 
    if(button == &multitapDelayToggleButton_){
        
        processor.multitap_ = button->getToggleState();
        
        if(processor.multitap_){
            
            processor.multitapDelay_ = 1;
            
            multitapDelayToggleButton_.setButtonText("On");
            
            processor.mDelayLine.setDelayL(processor.tempoInSamples);
            processor.mDelayLine.setDelayR(processor.tempoInSamples);
            //capire se cambiare il delay del ref
            processor.mDelayLine.setDelay_Ref_L(processor.tempoInSamples);
            processor.mDelayLine.setDelay_Ref_R(processor.tempoInSamples);
           
        }else{
            
            processor.multitapDelay_ = 0;
            
            multitapDelayToggleButton_.setButtonText("Off");
            
            processor.mDelayLine.setDelayL(processor.delaySamples_L);
            processor.mDelayLine.setDelayR(processor.delaySamples_R);
            
            processor.mDelayLine.setDelay_Ref_L(processor.delaySamplesRef_L);
            processor.mDelayLine.setDelay_Ref_R(processor.delaySamplesRef_R);
        }
        
    }else if(button == &syncToggleButton_){
        
        processor.sync_ = button->getToggleState();
        
        if(processor.sync_){
            
            syncToggleButton_.setButtonText("On");
            
            tempoSlider_.setRange (1, 32, 1);
            tempoSlider_.setValue(1);
            tempoSlider_.setDoubleClickReturnValue(true, 1);
            tempoSlider_.setValue(1);
            
            *processor.tempo_= tempoSlider_.getValue();
            processor.tempoInSamples = processor.beatLenghtInSamples/ *processor.tempo_;
            
            processor.mDelayLine.setDelayL(processor.tempoInSamples);
            processor.mDelayLine.setDelayR(processor.tempoInSamples);
            //capire se cambiare il delay del ref
            processor.mDelayLine.setDelay_Ref_L(processor.tempoInSamples);
            processor.mDelayLine.setDelay_Ref_R(processor.tempoInSamples);
            
            tempoText_.setBounds (500, 270, 85, 20);
            
        }else{
            
            syncToggleButton_.setButtonText("Off");
            
            tempoSlider_.setRange (1, 30, 0.01);
            tempoSlider_.setValue(10);
            tempoSlider_.setDoubleClickReturnValue(true, 10);
            
            *processor.tempo_= tempoSlider_.getValue();
            processor.tempoInSamples = (*processor.tempo_/345)*processor.getSampleRate();
            
            processor.mDelayLine.setDelayL(processor.tempoInSamples);
            processor.mDelayLine.setDelayR(processor.tempoInSamples);
            //capire se cambiare il delay del ref
            processor.mDelayLine.setDelay_Ref_L(processor.tempoInSamples);
            processor.mDelayLine.setDelay_Ref_R(processor.tempoInSamples);
            
            tempoText_.setBounds (500, 330, 70, 20);
        }
        
    }
    
}


void VirtualTubeDelayAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    if (slider == &tubeLengthLeftSlider_)
    {
        *processor.tubeLengthLeft_ = tubeLengthLeftSlider_.getValue();
        
        processor.leng_L = processor.mFilter.setLengt(*processor.tubeLengthLeft_);
        processor.delayMilli_L = processor.mFilter.setDelayMilliseconds(processor.leng_L);
        processor.delaySamples_L = processor.mFilter.setDelaySamples(processor.delayMilli_L);
        
        if(processor.multitapDelay_ == 0){
            processor.mDelayLine.setDelayL(processor.delaySamples_L);
        }
        else{
            processor.mDelayLine.setDelayL(processor.tempoInSamples);
        }
        
        processor.mFilter.setValues(*processor.tubeLengthLeft_, processor.rad);
        processor.mFilter.getCalculatedCoefficients(0);
        
        std::string delayText = createTextForDelays(processor.delayMilli_L);
        delayMsL_.setText(delayText);
        
        //changing the end distance
        processor.lengRef_L = processor.leng_L + processor.mFilter.setLengt(2* (*processor.tubeLengthRefLeft_));
        processor.delayMilliRef_L = processor.mFilter.setDelayMilliseconds(processor.lengRef_L);
        processor.delaySamplesRef_L = processor.mFilter.setDelaySamples(processor.delayMilliRef_L);
        
        if(processor.multitapDelay_ == 0){
            processor.mDelayLine.setDelay_Ref_L(processor.delaySamplesRef_L);
        }
        else{
            processor.mDelayLine.setDelay_Ref_L(processor.tempoInSamples);
        }
        
        processor.mFilter.setValues(2* (*processor.tubeLengthRefLeft_), processor.rad);
        processor.mFilter.getCalculatedCoefficients_Ref(0);
       
    }
    else if (slider == &tubeLengthRightSlider_)
    {
        *processor.tubeLengthRight_ = tubeLengthRightSlider_.getValue();
        
        processor.leng_R = processor.mFilter.setLengt(*processor.tubeLengthRight_);
        processor.delayMilli_R = processor.mFilter.setDelayMilliseconds(processor.leng_R);
        processor.delaySamples_R = processor.mFilter.setDelaySamples(processor.delayMilli_R);
        
        if(processor.multitapDelay_ == 0){
            processor.mDelayLine.setDelayR(processor.delaySamples_R);
        }
        else{
            processor.mDelayLine.setDelayR(processor.tempoInSamples);
        }
        
        processor.mFilter.setValues(*processor.tubeLengthRight_, processor.rad);
        processor.mFilter.getCalculatedCoefficients(1);
        
        std::string delayText = createTextForDelays(processor.delayMilli_R);
        delayMsR_.setText(delayText);
        
        //changing the end distance
        processor.lengRef_R = processor.leng_R + processor.mFilter.setLengt(2* (*processor.tubeLengthRefRight_));
        processor.delayMilliRef_R = processor.mFilter.setDelayMilliseconds(processor.lengRef_R);
        processor.delaySamplesRef_R = processor.mFilter.setDelaySamples(processor.delayMilliRef_R);
        
        if(processor.multitapDelay_ == 0){
            processor.mDelayLine.setDelay_Ref_R(processor.delaySamplesRef_R);
        }
        else{
            processor.mDelayLine.setDelay_Ref_R(processor.tempoInSamples);
        }
        
        processor.mFilter.setValues(2* (*processor.tubeLengthRefRight_), processor.rad);
        processor.mFilter.getCalculatedCoefficients_Ref(1);
        
    }
    else if (slider == &gainLeftSlider_)
    {
        *processor.gainLeft_ = gainLeftSlider_.getValue();
    }
    else if (slider == &gainRightSlider_)
    {
        *processor.gainRight_ = gainRightSlider_.getValue();
    }
    else if (slider == &dryWetMixSlider_)
    {
        *processor.dryWetMix_ = dryWetMixSlider_.getValue();
    }
    else if (slider == &tubeSizeSlider_)
    {
        *processor.tubeSize_ = tubeSizeSlider_.getValue();
        
        processor.rad = floor(*processor.tubeSize_*10 - 12);
        processor.mFilter.setValues(*processor.tubeLengthLeft_, processor.rad);
        processor.mFilter.getCalculatedCoefficients(0);
        processor.mFilter.setValues(*processor.tubeLengthRight_, processor.rad);
        processor.mFilter.getCalculatedCoefficients(1);
        //changing ref
        processor.mFilter.setValues(2* (*processor.tubeLengthRefLeft_), processor.rad);
        processor.mFilter.getCalculatedCoefficients_Ref(0);
        processor.mFilter.setValues(2* (*processor.tubeLengthRefRight_), processor.rad);
        processor.mFilter.getCalculatedCoefficients_Ref(1);
        
    }
    else if (slider == &tubeLengthRefLeftSlider_)
    {
        *processor.tubeLengthRefLeft_ = tubeLengthRefLeftSlider_.getValue();
        
        processor.lengRef_L = processor.leng_L + processor.mFilter.setLengt(2* (*processor.tubeLengthRefLeft_));
        processor.delayMilliRef_L = processor.mFilter.setDelayMilliseconds(processor.lengRef_L);
        processor.delaySamplesRef_L = processor.mFilter.setDelaySamples(processor.delayMilliRef_L);
        
        if(processor.multitapDelay_ == 0){
            processor.mDelayLine.setDelay_Ref_L(processor.delaySamplesRef_L);
        }
        else{
            processor.mDelayLine.setDelay_Ref_L(processor.tempoInSamples);
        }
        
        processor.mFilter.setValues(2* (*processor.tubeLengthRefLeft_), processor.rad);
        processor.mFilter.getCalculatedCoefficients_Ref(0);

        std::string delayText = createTextForDelays(processor.delayMilliRef_L);
        delayMsRefL_.setText(delayText);
        
    }
    else if (slider == &tubeLengthRefRightSlider_)
    {
        *processor.tubeLengthRefRight_ = tubeLengthRefRightSlider_.getValue();
        
        processor.lengRef_R = processor.leng_R + processor.mFilter.setLengt(2* (*processor.tubeLengthRefRight_));
        processor.delayMilliRef_R = processor.mFilter.setDelayMilliseconds(processor.lengRef_R);
        processor.delaySamplesRef_R = processor.mFilter.setDelaySamples(processor.delayMilliRef_R);
        
        if(processor.multitapDelay_ == 0){
            processor.mDelayLine.setDelay_Ref_R(processor.delaySamplesRef_R);
        }
        else{
            processor.mDelayLine.setDelay_Ref_R(processor.tempoInSamples);
        }
        
        processor.mFilter.setValues(2* (*processor.tubeLengthRefRight_), processor.rad);
        processor.mFilter.getCalculatedCoefficients_Ref(1);
        
        std::string delayText = createTextForDelays(processor.delayMilliRef_R);
        delayMsRefR_.setText(delayText);
        
    }
    else if (slider == &gainRefLeftSlider_)
    {
        *processor.gainRefLeft_ = gainRefLeftSlider_.getValue();
    }
    else if (slider == &gainRefRightSlider_)
    {
        *processor.gainRefRight_ = gainRefRightSlider_.getValue();
    }
    else if (slider == &feedbackSlider_)
    {
        *processor.feedback_ = feedbackSlider_.getValue();
    }
    else if (slider == &tempoSlider_)
    {
        *processor.tempo_ = tempoSlider_.getValue();
        
        if(processor.sync_){
        
            processor.tempoInSamples = processor.beatLenghtInSamples/ *processor.tempo_;
        
            int eraseNumber;
        
            if(*processor.tempo_ < 10){ eraseNumber = 10; }
            else{ eraseNumber = 11; }
        
            std::string tempoText = "Tempo: 1/";
            tempoText.append(std::to_string(*processor.tempo_));
            tempoText.erase(eraseNumber);
            tempoText_.setText(tempoText);
        
        }else{
            
            processor.tempoInSamples = (*processor.tempo_/345)*processor.getSampleRate();
            
            std::string tempoText = createTextForDelays(*processor.tempo_/0.345);
            tempoText_.setText(tempoText);
            
        }
        
        processor.mDelayLine.setDelayL(processor.tempoInSamples);
        processor.mDelayLine.setDelayR(processor.tempoInSamples);
        processor.mDelayLine.setDelay_Ref_L(processor.tempoInSamples);
        processor.mDelayLine.setDelay_Ref_R(processor.tempoInSamples);
    }
}



//==============================================================================
void VirtualTubeDelayAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(Colours::black);

    g.setColour (Colours::white);
    g.setFont(15.0f);
}

void VirtualTubeDelayAudioProcessorEditor::resized()
{
    //Texts
    
    delayMsL_.setBounds (130, 60, 70, 20);

    delayMsR_.setBounds (360, 60, 70, 20);
    
    delayMsRefL_.setBounds (130, 210, 70, 20);
    
    delayMsRefR_.setBounds (360, 210, 70, 20);
    
    gainText_.setBounds (660, 5, 70, 20);
    
    tubeLengthText_.setBounds (140, 5, 110, 20);
    
    tubeEndText_.setBounds (120, 150, 140, 20);
    
    gainRefText_.setBounds (660, 150, 110, 20);
    
    tempoText_.setBounds (500, 330, 75, 20);
    
    //Sliders
    
    //tubeLengthLeftSlider_.setBounds (30, 50, getWidth()-550, 20);
    
    tubeLengthLeftSlider_.setBounds (30, 50, 80, 100);
    
    //tubeLengthRightSlider_.setBounds (getWidth()-500, 50, getWidth()-550, 20);
    
    tubeLengthRightSlider_.setBounds (260, 50, 80, 100);
    
    gainLeftSlider_.setBounds (600, 50, 80, 100);
    
    gainRightSlider_.setBounds (700, 50, 80, 100);
    
    dryWetMixSlider_.setBounds (700, 350, 80, 100);
    
    tubeSizeSlider_.setBounds (30, 350, 80, 100);
    
    //tubeLengthRefLeftSlider_.setBounds (30, 180, getWidth()-600, 20);
    
    tubeLengthRefLeftSlider_.setBounds (30, 200, 80, 100);
    
    //tubeLengthRefRightSlider_.setBounds (getWidth()-500, 180, getWidth()-600, 20);
    
    tubeLengthRefRightSlider_.setBounds (260, 200, 80, 100);
    
    gainRefLeftSlider_.setBounds (600, 200, 80, 100);
    
    gainRefRightSlider_.setBounds (700, 200, 80, 100);
    
    feedbackSlider_.setBounds (300, 350, 80, 100);
    
    tempoSlider_.setBounds (500, 350, 80, 100);

    
    //Buttons
     
    multitapDelayToggleButton_.setBounds (600, 350, 80, 80);
    
    syncToggleButton_.setBounds (400, 350, 80, 80);
    
}
