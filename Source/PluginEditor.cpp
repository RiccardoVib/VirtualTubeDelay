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
    : AudioProcessorEditor (&p), processor (p), tubeLengthLeftLabel_("", "Tube Length Left (m):"),
      tubeLengthRightLabel_("", "Tube Length Right (m):"),
      gainLeftLabel_("", "Gain Left Level:"),
      gainRightLabel_("", "Gain Right Level:"), tubeSizeLabel_("", "Tube Size (cm):"), dryWetMixLabel_("", "Dry/Wet Mix Level:")
{
   
    setSize (800, 350);
    
        
    
    tubeLengthLeftSlider_.setSliderStyle(Slider::LinearBar);
    tubeLengthLeftSlider_.setRange (2.0, 30.0, 0.01);
    tubeLengthLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeLengthLeftSlider_.setPopupDisplayEnabled (true, false, this);
    tubeLengthLeftSlider_.setTextValueSuffix(" Tube Length Left");
    tubeLengthLeftSlider_.setValue(10.0);
    tubeLengthLeftSlider_.setDoubleClickReturnValue(true, 10.0);
    addAndMakeVisible (&tubeLengthLeftSlider_);
    tubeLengthLeftSlider_.addListener(this);
    
    tubeLengthRightSlider_.setSliderStyle(Slider::LinearBar);
    tubeLengthRightSlider_.setRange (2.0, 30.0, 0.01);
    tubeLengthRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeLengthRightSlider_.setPopupDisplayEnabled (true, false, this);
    tubeLengthRightSlider_.setTextValueSuffix(" Tube Length Right");
    tubeLengthRightSlider_.setValue(10.0);
    tubeLengthRightSlider_.setDoubleClickReturnValue(true, 10.0);
    addAndMakeVisible (&tubeLengthRightSlider_);
    tubeLengthRightSlider_.addListener(this);
    
    gainLeftSlider_.setSliderStyle(Slider::Rotary);
    gainLeftSlider_.setRange (0.0, 10.0, 0.01);
    gainLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainLeftSlider_.setPopupDisplayEnabled (true, false, this);
    gainLeftSlider_.setTextValueSuffix(" Gain Left");
    gainLeftSlider_.setValue(0.0);
    gainLeftSlider_.setDoubleClickReturnValue(true, 0.0);
    addAndMakeVisible (&gainLeftSlider_);
    gainLeftSlider_.addListener(this);
    
    gainRightSlider_.setSliderStyle(Slider::Rotary);
    gainRightSlider_.setRange (0.0, 10.0, 0.01);
    gainRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainRightSlider_.setPopupDisplayEnabled (true, false, this);
    gainRightSlider_.setTextValueSuffix(" Gain Right");
    gainRightSlider_.setValue(0.0);
    gainRightSlider_.setDoubleClickReturnValue(true, 0.0);
    addAndMakeVisible (&gainRightSlider_);
    gainRightSlider_.addListener(this);
    
    tubeSizeSlider_.setSliderStyle(Slider::Rotary);
    tubeSizeSlider_.setRange (1.2, 2.5, 0.1);
    tubeSizeSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeSizeSlider_.setPopupDisplayEnabled (true, false, this);
    tubeSizeSlider_.setTextValueSuffix(" Tube Size");
    tubeSizeSlider_.setValue(0.0);
    tubeSizeSlider_.setDoubleClickReturnValue(true, 0.0);
    addAndMakeVisible (&tubeSizeSlider_);
    tubeSizeSlider_.addListener(this);
    
    dryWetMixSlider_.setSliderStyle(Slider::Rotary);
    dryWetMixSlider_.setRange (0.0, 1.0, 0.01);
    dryWetMixSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    dryWetMixSlider_.setPopupDisplayEnabled (true, false, this);
    dryWetMixSlider_.setTextValueSuffix(" Dry/Wet");
    dryWetMixSlider_.setValue(0.0);
    dryWetMixSlider_.setDoubleClickReturnValue(true, 0.0);
    addAndMakeVisible (&dryWetMixSlider_);
    dryWetMixSlider_.addListener(this);
    
    tubeLengthLeftLabel_.attachToComponent(&tubeLengthLeftSlider_, false);
    tubeLengthLeftLabel_.setFont(Font (11.0f));
    tubeLengthRightLabel_.attachToComponent(&tubeLengthRightSlider_, false);
    tubeLengthRightLabel_.setFont(Font (11.0f));
    gainLeftLabel_.attachToComponent(&gainLeftSlider_, false);
    gainLeftLabel_.setFont(Font (11.0f));
    gainRightLabel_.attachToComponent(&gainRightSlider_, false);
    gainRightLabel_.setFont(Font (11.0f));
    //gainLeftLabel_.setColour(1, Colours::black);    
    gainRightLabel_.attachToComponent(&gainRightSlider_, false);
    gainRightLabel_.setFont(Font (11.0f));
    tubeSizeLabel_.attachToComponent(&tubeSizeSlider_, false);
    tubeSizeLabel_.setFont(Font (11.0f));
    dryWetMixLabel_.attachToComponent(&dryWetMixSlider_, false);
    dryWetMixLabel_.setFont(Font (11.0f));
 
}

VirtualTubeDelayAudioProcessorEditor::~VirtualTubeDelayAudioProcessorEditor()
{
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
    tubeLengthLeftSlider_.setBounds (30, 30, getWidth()-550, 20);
    
    tubeLengthRightSlider_.setBounds (getWidth()-500, 30, getWidth()-550, 20);
    
    gainLeftSlider_.setBounds (600, 30, 80, 80);
    
    gainRightSlider_.setBounds (700, 30, 80, 80);
    
    dryWetMixSlider_.setBounds (700, 250, 80, 80);
    
    tubeSizeSlider_.setBounds (700, 150, 80, 80);
}
