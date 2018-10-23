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
        tubeLengthLeftLabel_("", "Tube Length Left (m):"), tubeLengthRightLabel_("", "Tube Length Right (m):"),
        gainLeftLabel_("", "Gain Left Level:"), gainRightLabel_("", "Gain Right Level:"),
        tubeSizeLabel_("", "Tube Size (cm):"), dryWetMixLabel_("", "Dry/Wet:"), enabledReflectionLabel_("", "Add Reflection:"),
        enabledVibratoLabel_("", "Add Reflection:"),
        tubeLengthRefLeftLabel_("", "Tube End Distance Left (m):"), tubeLengthRefRightLabel_("", "Tube End Distance Right (m):"),
        gainRefLeftLabel_("", "Gain Reflection Left Level:"), gainRefRightLabel_("", "Gain Reflection Right Level:")
{
   
    setSize (800, 350);
    
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
    
    tubeLengthLeftSlider_.setSliderStyle(Slider::LinearBar);
    tubeLengthLeftSlider_.setRange (2.0, 30.0, 0.01);
    tubeLengthLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeLengthLeftSlider_.setPopupDisplayEnabled(true, false, this);
    tubeLengthLeftSlider_.setTextValueSuffix(" m");
    tubeLengthLeftSlider_.setValue(10.0);
    tubeLengthLeftSlider_.setDoubleClickReturnValue(true, 10.0);
    tubeLengthLeftSlider_.setChangeNotificationOnlyOnRelease(true);
    addAndMakeVisible (&tubeLengthLeftSlider_);
    tubeLengthLeftSlider_.addListener(this);
    
    tubeLengthRightSlider_.setSliderStyle(Slider::LinearBar);
    tubeLengthRightSlider_.setRange (2.0, 30.0, 0.01);
    tubeLengthRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeLengthRightSlider_.setPopupDisplayEnabled (true, false, this);
    tubeLengthRightSlider_.setTextValueSuffix(" m");
    tubeLengthRightSlider_.setValue(10.0);
    tubeLengthRightSlider_.setDoubleClickReturnValue(true, 10.0);
    tubeLengthRightSlider_.setChangeNotificationOnlyOnRelease(true);
    addAndMakeVisible (&tubeLengthRightSlider_);
    tubeLengthRightSlider_.addListener(this);
    
    gainLeftSlider_.setSliderStyle(Slider::Rotary);
    gainLeftSlider_.setRange (0.0, 10.0, 0.01);
    gainLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainLeftSlider_.setPopupDisplayEnabled (true, false, this);
    gainLeftSlider_.setTextValueSuffix(" dB");
    gainLeftSlider_.setValue(0.0);
    gainLeftSlider_.setDoubleClickReturnValue(true, 0.0);
    addAndMakeVisible (&gainLeftSlider_);
    gainLeftSlider_.addListener(this);
    
    gainRightSlider_.setSliderStyle(Slider::Rotary);
    gainRightSlider_.setRange (0.0, 10.0, 0.01);
    gainRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainRightSlider_.setPopupDisplayEnabled (true, false, this);
    gainRightSlider_.setTextValueSuffix(" dB");
    gainRightSlider_.setValue(0.0);
    gainRightSlider_.setDoubleClickReturnValue(true, 0.0);
    addAndMakeVisible (&gainRightSlider_);
    gainRightSlider_.addListener(this);
    
    tubeSizeSlider_.setSliderStyle(Slider::Rotary);
    tubeSizeSlider_.setRange (1.2, 2.5, 0.1);
    tubeSizeSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeSizeSlider_.setPopupDisplayEnabled (true, false, this);
    tubeSizeSlider_.setTextValueSuffix(" cm");
    tubeSizeSlider_.setValue(0.0);
    tubeSizeSlider_.setDoubleClickReturnValue(true, 0.0);
    addAndMakeVisible (&tubeSizeSlider_);
    tubeSizeSlider_.addListener(this);
    
    dryWetMixSlider_.setSliderStyle(Slider::Rotary);
    dryWetMixSlider_.setRange (0.0, 1.0, 0.01);
    dryWetMixSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    dryWetMixSlider_.setPopupDisplayEnabled (true, false, this);
    //dryWetMixSlider_.setTextValueSuffix(" Dry/Wet");
    dryWetMixSlider_.setValue(0.0);
    dryWetMixSlider_.setDoubleClickReturnValue(true, 0.0);
    addAndMakeVisible (&dryWetMixSlider_);
    dryWetMixSlider_.addListener(this);
    
    enabledReflectionToggleButton_.setButtonText("Off");
    enabledReflectionToggleButton_.setClickingTogglesState(true);
    addAndMakeVisible (&enabledReflectionToggleButton_);
    enabledReflectionToggleButton_.addListener(this);
    
    enabledVibratoToggleButton_.setButtonText("Off");
    enabledVibratoToggleButton_.setClickingTogglesState(true);
    addAndMakeVisible (&enabledVibratoToggleButton_);
    enabledVibratoToggleButton_.addListener(this);
    
    tubeLengthRefLeftSlider_.setSliderStyle(Slider::LinearBar);
    tubeLengthRefLeftSlider_.setRange (1.0, 5.0, 0.01);
    tubeLengthRefLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeLengthRefLeftSlider_.setPopupDisplayEnabled(true, false, this);
    tubeLengthRefLeftSlider_.setTextValueSuffix(" m");
    tubeLengthRefLeftSlider_.setValue(1.0);
    tubeLengthRefLeftSlider_.setDoubleClickReturnValue(true, 10.0);
    tubeLengthRefLeftSlider_.setChangeNotificationOnlyOnRelease(true);
    addAndMakeVisible (&tubeLengthRefLeftSlider_);
    tubeLengthRefLeftSlider_.addListener(this);
    
    tubeLengthRefRightSlider_.setSliderStyle(Slider::LinearBar);
    tubeLengthRefRightSlider_.setRange (1.0, 5.0, 0.01);
    tubeLengthRefRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeLengthRefRightSlider_.setPopupDisplayEnabled (true, false, this);
    tubeLengthRefRightSlider_.setTextValueSuffix(" m");
    tubeLengthRefRightSlider_.setValue(1.0);
    tubeLengthRefRightSlider_.setDoubleClickReturnValue(true, 10.0);
    tubeLengthRefRightSlider_.setChangeNotificationOnlyOnRelease(true);
    addAndMakeVisible (&tubeLengthRefRightSlider_);
    tubeLengthRefRightSlider_.addListener(this);
    
    gainRefLeftSlider_.setSliderStyle(Slider::Rotary);
    gainRefLeftSlider_.setRange (0.0, 20.0, 0.01);
    gainRefLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainRefLeftSlider_.setPopupDisplayEnabled (true, false, this);
    gainRefLeftSlider_.setTextValueSuffix(" dB");
    gainRefLeftSlider_.setValue(0.0);
    gainRefLeftSlider_.setDoubleClickReturnValue(true, 0.0);
    addAndMakeVisible (&gainRefLeftSlider_);
    gainRefLeftSlider_.addListener(this);
    
    gainRefRightSlider_.setSliderStyle(Slider::Rotary);
    gainRefRightSlider_.setRange (0.0, 20.0, 0.01);
    gainRefRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainRefRightSlider_.setPopupDisplayEnabled (true, false, this);
    gainRefRightSlider_.setTextValueSuffix(" dB");
    gainRefRightSlider_.setValue(0.0);
    gainRefRightSlider_.setDoubleClickReturnValue(true, 0.0);
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
 
    
    enabledReflectionLabel_.attachToComponent(&enabledReflectionToggleButton_, false);
    enabledReflectionLabel_.setFont(Font (14.0f));
    
    enabledVibratoToggleLabel_.attachToComponent(&enabledVibratoToggleButton_, false);
    enabledVibratoToggleLabel_.setFont(Font (14.0f));

    
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
}

VirtualTubeDelayAudioProcessorEditor::~VirtualTubeDelayAudioProcessorEditor()
{
}

void VirtualTubeDelayAudioProcessorEditor::buttonClicked (Button* button)
{
    if (button == &enabledReflectionToggleButton_){
        
        processor.enabledReflection_ = button->getToggleState();
        if(processor.enabledReflection_){
        
            enabledReflectionToggleButton_.setButtonText("On");
        
        }else{
            
            enabledReflectionToggleButton_.setButtonText("Off");
        
        }
    
    }else if(button == &enabledVibratoToggleButton_){

        processor.enabledVibrato_ = button->getToggleState();
        if(processor.enabledVibrato_){
    
            enabledVibratoToggleButton_.setButtonText("On");
    
        }else{
    
            enabledVibratoToggleButton_.setButtonText("Off");
        }
        
    }

}


void VirtualTubeDelayAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    if (slider == &tubeLengthLeftSlider_)
    {
        processor.tubeLengthLeft_ = tubeLengthLeftSlider_.getValue();
        
        processor.leng_L = processor.mFilter.setLengt(processor.tubeLengthLeft_);
        processor.delayMilli_L = processor.mFilter.setDelayMilliseconds(processor.leng_L);
        processor.delaySamples_L = processor.mFilter.setDelaySamples(processor.delayMilli_L);
        processor.mDelayLine.setDelayL(processor.delaySamples_L);
        processor.mFilter.setValues(processor.tubeLengthLeft_, processor.rad);
        processor.mFilter.getCalculatedCoefficients(0);
        
        std::string delayText = std::to_string(processor.delayMilli_L);
        delayText.erase(5);
        delayText.append(" ms");
        delayMsL_.setText(delayText);
       
    }
    else if (slider == &tubeLengthRightSlider_)
    {
        processor.tubeLengthRight_ = tubeLengthRightSlider_.getValue();
        
        processor.leng_R = processor.mFilter.setLengt(processor.tubeLengthRight_);
        processor.delayMilli_R = processor.mFilter.setDelayMilliseconds(processor.leng_R);
        processor.delaySamples_R = processor.mFilter.setDelaySamples(processor.delayMilli_R);
        processor.mDelayLine.setDelayR(processor.delaySamples_R);
        processor.mFilter.setValues(processor.tubeLengthRight_, processor.rad);
        processor.mFilter.getCalculatedCoefficients(1);
        
        std::string delayText = std::to_string(processor.delayMilli_R);
        delayText.erase(5);
        delayText.append(" ms");
        delayMsR_.setText(delayText);
    }
    else if (slider == &gainLeftSlider_)
    {
        processor.gainLeft_ = gainLeftSlider_.getValue();
    }
    else if (slider == &gainRightSlider_)
    {
        processor.gainRight_ = gainRightSlider_.getValue();
    }
    else if (slider == &dryWetMixSlider_)
    {
        processor.dryWetMix_ = dryWetMixSlider_.getValue();
    }
    else if (slider == &tubeSizeSlider_)
    {
        processor.tubeSize_ = tubeSizeSlider_.getValue();
        
        processor.rad = floor(processor.tubeSize_*10 - 12);
        processor.mFilter.setValues(processor.tubeLengthLeft_, processor.rad);
        processor.mFilter.getCalculatedCoefficients(0);
        processor.mFilter.setValues(processor.tubeLengthRight_, processor.rad);
        processor.mFilter.getCalculatedCoefficients(1);
        
    }
    else if (slider == &tubeLengthRefLeftSlider_)
    {
        processor.tubeLengthRefLeft_ = tubeLengthRefLeftSlider_.getValue();
        
        processor.lengRef_L = processor.leng_L + processor.mFilter.setLengt(2*processor.tubeLengthRefLeft_);
        processor.delayMilliRef_L = processor.mFilter.setDelayMilliseconds(processor.lengRef_L);
        processor.delaySamplesRef_L = processor.mFilter.setDelaySamples(processor.delayMilliRef_L);
        processor.mDelayLine.setDelay_Ref_L(processor.delaySamplesRef_L);
        processor.mFilter.setValues(2*processor.tubeLengthRefLeft_, processor.rad);
        processor.mFilter.getCalculatedCoefficients_Ref(0);

        std::string delayText = std::to_string(processor.delayMilliRef_L);
        delayText.erase(5);
        delayText.append(" ms");
        delayMsRefL_.setText(delayText);
        
    }
    else if (slider == &tubeLengthRefRightSlider_)
    {
        processor.tubeLengthRefRight_ = tubeLengthRefRightSlider_.getValue();
        
        processor.lengRef_R = processor.leng_R + processor.mFilter.setLengt(2*processor.tubeLengthRefRight_);
        processor.delayMilliRef_R = processor.mFilter.setDelayMilliseconds(processor.lengRef_R);
        processor.delaySamplesRef_R = processor.mFilter.setDelaySamples(processor.delayMilliRef_R);
        processor.mDelayLine.setDelay_Ref_R(processor.delaySamplesRef_R);
        processor.mFilter.setValues(2*processor.tubeLengthRefRight_, processor.rad);
        processor.mFilter.getCalculatedCoefficients_Ref(1);
        
        std::string delayText = std::to_string(processor.delayMilliRef_R);
        delayText.erase(5);
        delayText.append(" ms");
        delayMsRefR_.setText(delayText);
        
    }
    else if (slider == &gainRefLeftSlider_)
    {
        processor.gainRefLeft_ = gainRefLeftSlider_.getValue();
    }
    else if (slider == &gainRefRightSlider_)
    {
        processor.gainRefRight_ = gainRefRightSlider_.getValue();
    }
}



//==============================================================================
void VirtualTubeDelayAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(Colours::black);// (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont(15.0f);
    //g.drawFittedText ("Virtual Tube Delay", getLocalBounds(), Justification::centred, 1);
}

void VirtualTubeDelayAudioProcessorEditor::resized()
{
    delayMsL_.setBounds (30, 50, 70, 20);
    
    delayMsR_.setBounds (getWidth()-500, 50, 70, 20);

    delayMsRefL_.setBounds (30, 170, 70, 20);
    
    delayMsRefR_.setBounds (getWidth()-500, 170, 70, 20);
    
    tubeLengthLeftSlider_.setBounds (30, 30, getWidth()-550, 20);
    
    tubeLengthRightSlider_.setBounds (getWidth()-500, 30, getWidth()-550, 20);
    
    gainLeftSlider_.setBounds (600, 30, 80, 100);
    
    gainRightSlider_.setBounds (700, 30, 80, 100);
    
    dryWetMixSlider_.setBounds (700, 250, 80, 100);
    
    tubeSizeSlider_.setBounds (700, 150, 80, 100);
    
    enabledReflectionToggleButton_.setBounds (600, 250, 80, 80);
    
    enabledVibratoToggleButton_.setBounds (500, 250, 80, 80);
    
    tubeLengthRefLeftSlider_.setBounds (30, 150, getWidth()-600, 20);
    
    tubeLengthRefRightSlider_.setBounds (getWidth()-500, 150, getWidth()-600, 20);
    
    gainRefLeftSlider_.setBounds (30, 250, 80, 100);
    
    gainRefRightSlider_.setBounds (230, 250, 80, 100);
}
