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
        tubeEndLeftLabel_("", "Left Channel:"), tubeEndRightLabel_("", "Right Channel:"),
        gainRefLeftLabel_("", "Left Channel:"), gainRefRightLabel_("", "Right Channel:"),
        multitapDelayLabel_("", "Multitap:"), feedbackLabel_("", "Feedback:"), syncLabel_("", "Sync:")
{
    
    setSize (800, 450);
    
    tubeLengthLeftAttachment = new SliderAttachment(processor.parameters, "tubeLengthLeft_", tubeLengthLeftSlider_);
    tubeLengthRightAttachment = new SliderAttachment(processor.parameters, "tubeLengthRight_", tubeLengthRightSlider_);
    gainLeftAttachment = new SliderAttachment(processor.parameters, "gainLeft_", gainLeftSlider_);
    gainRightAttachment = new SliderAttachment(processor.parameters, "gainRight_", gainRightSlider_);
    tubeSizeAttachment = new SliderAttachment(processor.parameters, "tubeSize_", tubeSizeSlider_);
    dryWetMixAttachment = new SliderAttachment(processor.parameters, "dryWetMix_", dryWetMixSlider_);
    tubeEndLeftAttachment = new SliderAttachment(processor.parameters, "tubeEndLeft_", tubeEndLeftSlider_);
    tubeEndRightAttachment = new SliderAttachment(processor.parameters, "tubeEndRight_", tubeEndRightSlider_);
    gainRefLeftAttachment = new SliderAttachment(processor.parameters, "gainRefLeft_", gainRefLeftSlider_);
    gainRefRightAttachment = new SliderAttachment(processor.parameters, "gainRefRight_", gainRefRightSlider_);
    feedbackAttachment = new SliderAttachment(processor.parameters, "feedback_", feedbackSlider_);
    tempoAttachment = new SliderAttachment(processor.parameters, "tempo_", tempoSlider_);
    
    multitapAttachment = new ButtonAttachment(processor.parameters, "multitap_", multitapDelayToggleButton_);
    syncAttachment = new ButtonAttachment(processor.parameters, "sync_", syncToggleButton_);
    
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
    
    delayMsL_.setReadOnly(true);
    delayMsL_.setText(createTextForDelays(processor.delayMilli[0]));
    addAndMakeVisible (&delayMsL_);
    
    delayMsR_.setReadOnly(true);
    delayMsR_.setText(createTextForDelays(processor.delayMilli[1]));
    addAndMakeVisible (&delayMsR_);
    
    delayMsRefL_.setReadOnly(true);
    delayMsRefL_.setText(createTextForDelays(processor.delayMilliRef[0]));
    addAndMakeVisible (&delayMsRefL_);
    
    delayMsRefR_.setReadOnly(true);
    delayMsRefR_.setText(createTextForDelays(processor.delayMilliRef[1]));
    addAndMakeVisible (&delayMsRefR_);
    
    tempoText_.setReadOnly(true);
    addAndMakeVisible (&tempoText_);
    tempoText_.setVisible(false);
    
    tubeLengthLeftSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    tubeLengthLeftSlider_.setRange (2.0f, 30.0f, 0.01f);
    tubeLengthLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeLengthLeftSlider_.setPopupDisplayEnabled(true, false, this);
    tubeLengthLeftSlider_.setTextValueSuffix(" m");
    tubeLengthLeftSlider_.setDoubleClickReturnValue(true, 10.0f);
    addAndMakeVisible (&tubeLengthLeftSlider_);
    tubeLengthLeftSlider_.addListener(this);
    
    tubeLengthRightSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    tubeLengthRightSlider_.setRange (2.0f, 30.0f, 0.01f);
    tubeLengthRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeLengthRightSlider_.setPopupDisplayEnabled (true, false, this);
    tubeLengthRightSlider_.setTextValueSuffix(" m");
    tubeLengthRightSlider_.setDoubleClickReturnValue(true, 10.0f);
    addAndMakeVisible (&tubeLengthRightSlider_);
    tubeLengthRightSlider_.addListener(this);
    
    gainLeftSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    gainLeftSlider_.setRange (0.0f, 9.0f, 0.01f);
    gainLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainLeftSlider_.setPopupDisplayEnabled (true, false, this);
    gainLeftSlider_.setTextValueSuffix(" dB");
    gainLeftSlider_.setDoubleClickReturnValue(true, 2.0f);
    addAndMakeVisible (&gainLeftSlider_);
    gainLeftSlider_.addListener(this);
    
    gainRightSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    gainRightSlider_.setRange (0.0f, 9.0f, 0.01f);
    gainRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainRightSlider_.setPopupDisplayEnabled (true, false, this);
    gainRightSlider_.setTextValueSuffix(" dB");
    gainRightSlider_.setDoubleClickReturnValue(true, 2.0f);
    addAndMakeVisible (&gainRightSlider_);
    gainRightSlider_.addListener(this);
    
    tubeSizeSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    tubeSizeSlider_.setRange (1.2, 2.5, 0.1);
    tubeSizeSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeSizeSlider_.setPopupDisplayEnabled (true, false, this);
    tubeSizeSlider_.setTextValueSuffix(" cm");
    tubeSizeSlider_.setDoubleClickReturnValue(true, 1.2);
    addAndMakeVisible (&tubeSizeSlider_);
    tubeSizeSlider_.addListener(this);
    
    dryWetMixSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    dryWetMixSlider_.setRange (0.0f, 1.0f, 0.01f);
    dryWetMixSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    dryWetMixSlider_.setPopupDisplayEnabled (true, false, this);
    dryWetMixSlider_.setDoubleClickReturnValue(true, 0.0f);
    addAndMakeVisible (&dryWetMixSlider_);
    dryWetMixSlider_.addListener(this);
    
    tubeEndLeftSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    tubeEndLeftSlider_.setRange (1.0f, 5.0f, 0.01f);
    tubeEndLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeEndLeftSlider_.setPopupDisplayEnabled(true, false, this);
    tubeEndLeftSlider_.setTextValueSuffix(" m");
    tubeEndLeftSlider_.setDoubleClickReturnValue(true, 10.0f);
    addAndMakeVisible (&tubeEndLeftSlider_);
    tubeEndLeftSlider_.addListener(this);
    
    tubeEndRightSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    tubeEndRightSlider_.setRange (1.0f, 5.0f, 0.01f);
    tubeEndRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tubeEndRightSlider_.setPopupDisplayEnabled (true, false, this);
    tubeEndRightSlider_.setTextValueSuffix(" m");
    tubeEndRightSlider_.setDoubleClickReturnValue(true, 10.0f);
    addAndMakeVisible (&tubeEndRightSlider_);
    tubeEndRightSlider_.addListener(this);
    
    gainRefLeftSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    gainRefLeftSlider_.setRange (0.0f, 18.0f, 0.01f);
    gainRefLeftSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainRefLeftSlider_.setPopupDisplayEnabled (true, false, this);
    gainRefLeftSlider_.setTextValueSuffix(" dB");
    gainRefLeftSlider_.setDoubleClickReturnValue(true, 4.0f);
    addAndMakeVisible (&gainRefLeftSlider_);
    gainRefLeftSlider_.addListener(this);
    
    gainRefRightSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    gainRefRightSlider_.setRange (0.0f, 18.0f, 0.01f);
    gainRefRightSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    gainRefRightSlider_.setPopupDisplayEnabled (true, false, this);
    gainRefRightSlider_.setTextValueSuffix(" dB");
    gainRefRightSlider_.setDoubleClickReturnValue(true, 4.0f);
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
    
    tubeSizeLabel_.attachToComponent(&tubeSizeSlider_, false);
    tubeSizeLabel_.setFont(Font (14.0f));
    
    dryWetMixLabel_.attachToComponent(&dryWetMixSlider_, false);
    dryWetMixLabel_.setFont(Font (14.0f));
    
    tubeEndLeftLabel_.attachToComponent(&tubeEndLeftSlider_, false);
    tubeEndLeftLabel_.setFont(Font (14.0f));
    
    tubeEndRightLabel_.attachToComponent(&tubeEndRightSlider_, false);
    tubeEndRightLabel_.setFont(Font (14.0f));
    
    gainRefLeftLabel_.attachToComponent(&gainRefLeftSlider_, false);
    gainRefLeftLabel_.setFont(Font (14.0f));
    
    gainRefRightLabel_.attachToComponent(&gainRefRightSlider_, false);
    gainRefRightLabel_.setFont(Font (14.0f));
    
    //multitap
    
    feedbackSlider_.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    feedbackSlider_.setRange (0.1f, 0.9f, 0.01f);
    feedbackSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    feedbackSlider_.setPopupDisplayEnabled (true, false, this);
    feedbackSlider_.setTextValueSuffix(" ");
    feedbackSlider_.setDoubleClickReturnValue(true, 0.1f);
    addAndMakeVisible (&feedbackSlider_);
    feedbackSlider_.addListener(this);
    
    
    tempoSlider_.setSliderStyle(Slider:: RotaryHorizontalVerticalDrag);
    tempoSlider_.setRange (2, 32, 2);
    tempoSlider_.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    tempoSlider_.setPopupDisplayEnabled (false, false, this);
    tempoSlider_.setTextValueSuffix(" ");
    tempoSlider_.setDoubleClickReturnValue(true, 2);
    addAndMakeVisible (&tempoSlider_);
    tempoSlider_.setVisible(false);
    tempoSlider_.addListener(this);
    
    syncToggleButton_.setButtonText("Off");
    syncToggleButton_.setClickingTogglesState(true);
    addAndMakeVisible (&syncToggleButton_);
    syncToggleButton_.addListener(this);
    
    if((bool)*processor.sync_){ tempoSlider_.setVisible(true); syncToggleButton_.setButtonText("On"); tempoText_.setText(createTextForTempo(*processor.tempo_)); tempoText_.setVisible(true);}
  
    syncLabel_.attachToComponent(&syncToggleButton_, false);
    syncLabel_.setFont(Font (14.0f));
    
    feedbackLabel_.attachToComponent(&feedbackSlider_, false);
    feedbackLabel_.setFont(Font (14.0f));
    
    multitapDelayToggleButton_.setClickingTogglesState(true);
    addAndMakeVisible (&multitapDelayToggleButton_);
    multitapDelayToggleButton_.setButtonText("Off");
    if(multitapDelayToggleButton_.getToggleState()){ multitapDelayToggleButton_.setButtonText("On");}
    multitapDelayToggleButton_.addListener(this);
    
    multitapDelayLabel_.attachToComponent(&multitapDelayToggleButton_, false);
    multitapDelayLabel_.setFont(Font (14.0f));
    
}

VirtualTubeDelayAudioProcessorEditor::~VirtualTubeDelayAudioProcessorEditor()
{
}

void VirtualTubeDelayAudioProcessorEditor::buttonClicked (Button* button)
{
 
    if(button == &multitapDelayToggleButton_){
        
        *processor.multitap_ = button->getToggleState();
        
        if(*processor.multitap_){
            
            multitapDelayToggleButton_.setButtonText("On");
           
        }else{
                        
            multitapDelayToggleButton_.setButtonText("Off");
            
        }
        
    }else if(button == &syncToggleButton_){
        
        *processor.sync_ = button->getToggleState();
        
        if(*processor.sync_){
            
            syncToggleButton_.setButtonText("On");
            
            tempoSlider_.setVisible(true);
            tempoText_.setVisible(true);
            tempoText_.setText(createTextForTempo(*processor.tempo_));
            
            *processor.tempo_= tempoSlider_.getValue();
            
        }else{
            
            syncToggleButton_.setButtonText("Off");

            tempoSlider_.setVisible(false);
            tempoText_.setVisible(false);
            
        }
        
    }
    
}


void VirtualTubeDelayAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    if (slider == &tubeLengthLeftSlider_)
    {
        *processor.tubeLengthLeft_ = tubeLengthLeftSlider_.getValue();
        
        processor.leng[0] = processor.mFilter[0].setLengt(*processor.tubeLengthLeft_);
        processor.delayMilli[0] = processor.mFilter[0].setDelayMilliseconds(processor.leng[0]);
        
        std::string delayText = createTextForDelays(processor.delayMilli[0]);
        delayMsL_.setText(delayText);
        
        processor.lengRef[0] = processor.leng[0] + processor.mFilter[0].setLengt(*processor.tubeEndLeft_);
        processor.delayMilliRef[0] = processor.mFilter[0].setDelayMilliseconds(processor.lengRef[0]);
        
        std::string delayTextRef = createTextForDelays(processor.delayMilliRef[0]);
        delayMsRefL_.setText(delayTextRef);
       
    }
    else if (slider == &tubeLengthRightSlider_)
    {
        *processor.tubeLengthRight_ = tubeLengthRightSlider_.getValue();
        
        processor.leng[1] = processor.mFilter[1].setLengt(*processor.tubeLengthRight_);
        processor.delayMilli[1] = processor.mFilter[1].setDelayMilliseconds(processor.leng[1]);
        
        std::string delayText = createTextForDelays(processor.delayMilli[1]);
        delayMsR_.setText(delayText);
        
        processor.lengRef[1] = processor.leng[1] + processor.mFilter[1].setLengt(*processor.tubeEndRight_);
        processor.delayMilliRef[1] = processor.mFilter[1].setDelayMilliseconds(processor.lengRef[1]);
        
        std::string delayTextRef = createTextForDelays(processor.delayMilliRef[1]);
        delayMsRefR_.setText(delayTextRef);
        
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
 
    }
    else if (slider == &tubeEndLeftSlider_)
    {
        *processor.tubeEndLeft_ = tubeEndLeftSlider_.getValue();
        
        processor.lengRef[0] = processor.leng[0] + processor.mFilter_ref[0].setLengt(*processor.tubeEndLeft_);
        processor.delayMilliRef[0] = processor.mFilter_ref[0].setDelayMilliseconds(processor.lengRef[0]);
        
        std::string delayText = createTextForDelays(processor.delayMilliRef[0]);
        delayMsRefL_.setText(delayText);
        
    }
    else if (slider == &tubeEndRightSlider_)
    {
        *processor.tubeEndRight_ = tubeEndRightSlider_.getValue();
        
        processor.lengRef[1] = processor.leng[1] + processor.mFilter_ref[1].setLengt(*processor.tubeEndRight_);
        processor.delayMilliRef[1] = processor.mFilter_ref[1].setDelayMilliseconds(processor.lengRef[1]);
        
        std::string delayText = createTextForDelays(processor.delayMilliRef[1]);
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
        
        std::string tempoText = createTextForTempo(*processor.tempo_);
        tempoText_.setText(tempoText);
    
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
    
    gainRefText_.setBounds (640, 150, 100, 20);
    
    tempoText_.setBounds (500, 330, 85, 20);
    
    //Sliders
    
    tubeLengthLeftSlider_.setBounds (30, 50, 80, 100);
    
    tubeLengthRightSlider_.setBounds (260, 50, 80, 100);
    
    gainLeftSlider_.setBounds (600, 50, 80, 100);
    
    gainRightSlider_.setBounds (700, 50, 80, 100);
    
    dryWetMixSlider_.setBounds (700, 350, 80, 100);
    
    tubeSizeSlider_.setBounds (30, 350, 80, 100);
    
    tubeEndLeftSlider_.setBounds (30, 200, 80, 100);
        
    tubeEndRightSlider_.setBounds (260, 200, 80, 100);
    
    gainRefLeftSlider_.setBounds (600, 200, 80, 100);
    
    gainRefRightSlider_.setBounds (700, 200, 80, 100);
    
    feedbackSlider_.setBounds (260, 350, 80, 100);
    
    tempoSlider_.setBounds (500, 350, 80, 100);

    
    //Buttons
     
    multitapDelayToggleButton_.setBounds (600, 350, 80, 80);
    
    syncToggleButton_.setBounds (400, 350, 80, 80);
    
}
