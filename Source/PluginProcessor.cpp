/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
VirtualTubeDelayAudioProcessor::VirtualTubeDelayAudioProcessor()
: AudioProcessor (BusesProperties().withInput  ("Input",     AudioChannelSet::stereo(), true)
                  .withOutput ("Output",    AudioChannelSet::stereo(), true)), parameters (*this, nullptr)
{
    
    parameters.createAndAddParameter("tubeLengthLeft_", "tubeLengthLeft", "tubeLengthLeft", NormalisableRange<float>(2,30), 10, nullptr, nullptr);
    parameters.createAndAddParameter("tubeLengthRight_", "tubeLengthRight", "tubeLengthRight", NormalisableRange<float>(2,30), 10, nullptr, nullptr);
    parameters.createAndAddParameter("gainLeft_", "gainLeft", "gainLeft", NormalisableRange<float>(0,10), 2, nullptr, nullptr);
    parameters.createAndAddParameter("gainRight_", "gainRight", "gainRight", NormalisableRange<float>(0,10), 2, nullptr, nullptr);

    parameters.createAndAddParameter("dryWetMix_", "dryWetMix", "dryWetMix", NormalisableRange<float>(0.0, 1.0), 0, nullptr, nullptr);
    parameters.createAndAddParameter("tubeSize_", "tubeSize", "tubeSize", NormalisableRange<float>(1.2,2.5), 1.2, nullptr, nullptr);
    
    parameters.createAndAddParameter("tubeLengthRefLeft_", "tubeLengthRefLeft", "tubeLengthRefLeft", NormalisableRange<float>(1,5), 1, nullptr, nullptr);
    parameters.createAndAddParameter("tubeLengthRefRight_", "tubeLengthRefRight", "tubeLengthRefRight", NormalisableRange<float>(1,5), 1, nullptr, nullptr);
    parameters.createAndAddParameter("gainRefLeft_", "gainRefLeft", "gainRefLeft", NormalisableRange<float>(0,20), 4, nullptr, nullptr);
    parameters.createAndAddParameter("gainRefRight_", "gainRefRight_", "gainRefRight_", NormalisableRange<float>(0,20), 4, nullptr, nullptr);
    parameters.createAndAddParameter("feedback_", "feedback", "feedback_", NormalisableRange<float>(0.1,0.9), 0.1, nullptr, nullptr);
    parameters.createAndAddParameter("tempo_", "tempo", "tempo", NormalisableRange<float>(1,30), 10, nullptr, nullptr);
    
    //parameters.createAndAddParameter("multitap_", "multitap", "multitap", NormalisableRange<float>(0,1), false, nullptr, nullptr);
    //parameters.createAndAddParameter("sync_", "sync", "sync", NormalisableRange<float>(0,1), false, nullptr, nullptr);
    
    parameters.state = ValueTree("SavedParams");
    
    
    tubeLengthLeft_ = parameters.getRawParameterValue ("tubeLengthLeft_");
    tubeLengthRight_ = parameters.getRawParameterValue ("tubeLengthRight_");
    gainLeft_ = parameters.getRawParameterValue ("gainLeft_");
    gainRight_ = parameters.getRawParameterValue ("gainRight_");
    dryWetMix_ = parameters.getRawParameterValue ("dryWetMix_");
    tubeSize_ = parameters.getRawParameterValue ("tubeSize_");
    
    tubeLengthRefLeft_ = parameters.getRawParameterValue ("tubeLengthRefLeft_");
    tubeLengthRefRight_ = parameters.getRawParameterValue ("tubeLengthRefRight_");
    gainRefLeft_ = parameters.getRawParameterValue ("gainRefLeft_");
    gainRefRight_ = parameters.getRawParameterValue ("gainRefRight_");
    feedback_ = parameters.getRawParameterValue ("feedback_");
    tempo_ = parameters.getRawParameterValue ("tempo_");

    //multitap_ = parameters.getRawParameterValue ("multitap_");
    //sync_ = parameters.getRawParameterValue ("sync_");

    
    // Set default values:
    multitapDelay_ = 0;
    leng_L = 10.0;
    leng_R = 10.0;
    delayMilli_L = 28.985507246376812;
    delayMilli_R = 28.985507246376812;
    delaySamples_L = 1278.2608695652175;
    delaySamples_R = 1278.2608695652175;
    lengRef_L = 12.0;
    lengRef_R = 12.0;
    delayMilliRef_L = 34.78260869565217;
    delayMilliRef_R = 34.78260869565217;
    delaySamplesRef_L = 1533.913043478260;
    delaySamplesRef_R = 1533.913043478260;

    //feedback_ = 0.1;
    tempoBpm_ = 120;
    beatLenghtInSec = 2;
    beatLenghtInSamples = 88200;
    tempoInSamples = delaySamples_L;
    
    sync_ = false;
    multitap_ = false;
    //addParameter (tubeLengthLeft_ = new AudioParameterFloat ("tubeLengthLeft_", "TubeLength Left", 1.0f, 30.0f, 10.0f));
    //addParameter (gainLeft_     = new AudioParameterFloat ("gainLeft_",     "Gain Left",     0.0f, 10.0f, 5.0f));
}



VirtualTubeDelayAudioProcessor::~VirtualTubeDelayAudioProcessor()
{
}
//==============================================================================
const String VirtualTubeDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VirtualTubeDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VirtualTubeDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VirtualTubeDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double VirtualTubeDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VirtualTubeDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VirtualTubeDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VirtualTubeDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String VirtualTubeDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void VirtualTubeDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}
//==============================================================================
void VirtualTubeDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    mDelayLine.setSampleRate(getSampleRate());
    mFilter.setSampleRate(getSampleRate());
    delayBufferLength_ = (int)((31/0.345) * sampleRate/1000);
    delayBufferLengthRef_ = (int)((46/0.345) * sampleRate/1000);
    mDelayLine.initialize();
    
    /*delayBufferLeft_2.setSize(1, delayBufferLength_);
    delayBufferRight_2.setSize(1, delayBufferLength_);
    delayBufferLeftRef_2.setSize(1, delayBufferLengthRef_);
    delayBufferRightRef_2.setSize(1, delayBufferLengthRef_);*/
    
    playHead = this->getPlayHead();
    playHead->getCurrentPosition (currentPositionInfo);
    
    beatLenghtInSec = tempoBpm_/60;
    beatLenghtInSamples = beatLenghtInSec * getSampleRate();
    //tempoInSamples = beatLenghtInSamples/tempo_;
    tempoInSamples = delaySamples_L;
    
    //auto tubeLengthLeft_Copy = tubeLengthLeft_->get();
    
    rad = floor(*tubeSize_*10 - 12);

    leng_L = mFilter.setLengt(*tubeLengthLeft_);
    delayMilli_L = mFilter.setDelayMilliseconds(leng_L);
    delaySamples_L = mFilter.setDelaySamples(delayMilli_L);
    mDelayLine.setDelayL(delaySamples_L);
    mFilter.setValues(*tubeLengthLeft_, rad);
    mFilter.getCalculatedCoefficients(0);

    leng_R = mFilter.setLengt(*tubeLengthRight_);
    delayMilli_R = mFilter.setDelayMilliseconds(leng_R);
    delaySamples_R = mFilter.setDelaySamples(delayMilli_R);
    mDelayLine.setDelayR(delaySamples_R);
    mFilter.setValues(*tubeLengthRight_, rad);
    mFilter.getCalculatedCoefficients(1);
    
}
void VirtualTubeDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VirtualTubeDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void VirtualTubeDelayAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer&)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
    int numSamples = buffer.getNumSamples();
    
    playHead = this->getPlayHead();
    playHead->getCurrentPosition (currentPositionInfo);
    
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i){
        buffer.clear(i, 0, buffer.getNumSamples());
    }
    
    float* channelDataL = buffer.getWritePointer(0);
    float* channelDataR = buffer.getWritePointer(1);

    if(sync_){
        tempoBpm_ = currentPositionInfo.bpm;
        beatLenghtInSec = tempoBpm_/60;
        beatLenghtInSamples = beatLenghtInSec * getSampleRate();
        tempoInSamples = beatLenghtInSamples/ *tempo_;
    }else{
        tempoInSamples = (*tempo_/345)*getSampleRate();
    }
    
        
    for (int i = 0; i < numSamples; ++i)
    {
        
        const double inL = channelDataL[i];
        const double inR = channelDataR[i];
        double outL = 0.0;
        double outR = 0.0;
  
        mFilter.process();
        
        bufIn_L[mFilter.i_0] = inL;
        
        bufIn_R[mFilter.i_0] = inR;
        
        bufOut_L[mFilter.i_0] = bufIn_L[mFilter.i_0] * mFilter.b0f_L + bufIn_L[mFilter.i_1] * mFilter.b1f_L + bufIn_L[mFilter.i_2] * mFilter.b2f_L + bufIn_L[mFilter.i_3] * mFilter.b3f_L + bufIn_L[mFilter.i_4] * mFilter.b4f_L + bufIn_L[mFilter.i_5] * mFilter.b5f_L + bufIn_L[mFilter.i_6] * mFilter.b6f_L - bufOut_L[mFilter.i_1] * mFilter.a1f_L - bufOut_L[mFilter.i_2] * mFilter.a2f_L - bufOut_L[mFilter.i_3] * mFilter.a3f_L - bufOut_L[mFilter.i_4] * mFilter.a4f_L - bufOut_L[mFilter.i_5] * mFilter.a5f_L - bufOut_L[mFilter.i_6] * mFilter.a6f_L;
        
        bufOut_R[mFilter.i_0] = bufIn_R[mFilter.i_0] * mFilter.b0f_R + bufIn_R[mFilter.i_1] * mFilter.b1f_R + bufIn_R[mFilter.i_2] * mFilter.b2f_R + bufIn_R[mFilter.i_3] * mFilter.b3f_R + bufIn_R[mFilter.i_4] * mFilter.b4f_R + bufIn_R[mFilter.i_5] * mFilter.b5f_R + bufIn_R[mFilter.i_6] * mFilter.b6f_R - bufOut_R[mFilter.i_1] * mFilter.a1f_R - bufOut_R[mFilter.i_2] * mFilter.a2f_R - bufOut_R[mFilter.i_3] * mFilter.a3f_R - bufOut_R[mFilter.i_4] * mFilter.a4f_R - bufOut_R[mFilter.i_5] * mFilter.a5f_R - bufOut_R[mFilter.i_6] * mFilter.a6f_R;
        
        bufIn_Ref_L[mFilter.i_0] = bufOut_L[mFilter.i_0];
        bufIn_Ref_R[mFilter.i_0] = bufOut_R[mFilter.i_0];
            
        bufOut_Ref_L[mFilter.i_0] = bufIn_Ref_L[mFilter.i_0] * mFilter.b0f_Ref_L + bufIn_Ref_L[mFilter.i_1] * mFilter.b1f_Ref_L + bufIn_Ref_L[mFilter.i_2] * mFilter.b2f_Ref_L + bufIn_Ref_L[mFilter.i_3] * mFilter.b3f_Ref_L + bufIn_Ref_L[mFilter.i_4] * mFilter.b4f_Ref_L + bufIn_Ref_L[mFilter.i_5] * mFilter.b5f_Ref_L + bufIn_Ref_L[mFilter.i_6] * mFilter.b6f_Ref_L - bufOut_Ref_L[mFilter.i_1] * mFilter.a1f_Ref_L - bufOut_Ref_L[mFilter.i_2] * mFilter.a2f_Ref_L - bufOut_Ref_L[mFilter.i_3] * mFilter.a3f_Ref_L - bufOut_Ref_L[mFilter.i_4] * mFilter.a4f_Ref_L - bufOut_Ref_L[mFilter.i_5] * mFilter.a5f_Ref_L - bufOut_Ref_L[mFilter.i_6] * mFilter.a6f_Ref_L;
        
        bufOut_Ref_R[mFilter.i_0] = bufIn_Ref_R[mFilter.i_0] * mFilter.b0f_Ref_R + bufIn_Ref_R[mFilter.i_1] * mFilter.b1f_Ref_R + bufIn_Ref_R[mFilter.i_2] * mFilter.b2f_Ref_R + bufIn_Ref_R[mFilter.i_3] * mFilter.b3f_Ref_R + bufIn_Ref_R[mFilter.i_4] * mFilter.b4f_Ref_R + bufIn_Ref_R[mFilter.i_5] * mFilter.b5f_Ref_R + bufIn_Ref_R[mFilter.i_6] * mFilter.b6f_Ref_R - bufOut_Ref_R[mFilter.i_1] * mFilter.a1f_Ref_R - bufOut_Ref_R[mFilter.i_2] * mFilter.a2f_Ref_R - bufOut_Ref_R[mFilter.i_3] * mFilter.a3f_Ref_R - bufOut_Ref_R[mFilter.i_4] * mFilter.a4f_Ref_R - bufOut_Ref_R[mFilter.i_5] * mFilter.a5f_Ref_R - bufOut_Ref_R[mFilter.i_6] * mFilter.a6f_Ref_R;
        
        bufIn_Fin_L[mFilter.j_0] = bufOut_L[mFilter.i_0];
        bufIn_Fin_R[mFilter.j_0] = bufOut_R[mFilter.i_0];
        
        
        bufOut_Fin_L[mFilter.j_0] = bufIn_Fin_L[mFilter.j_0] * mFilter.b_Ref[rad][0] + bufIn_Fin_L[mFilter.j_1] * mFilter.b_Ref[rad][1] + bufIn_Fin_L[mFilter.j_2] * mFilter.b_Ref[rad][2] + bufIn_Fin_L[mFilter.j_3] * mFilter.b_Ref[rad][3] - bufOut_Fin_L[mFilter.j_1] * mFilter.a_Ref[rad][0] - bufOut_Fin_L[mFilter.j_2] * mFilter.a_Ref[rad][1] - bufOut_Fin_L[mFilter.j_3] * mFilter.a_Ref[rad][2];
        
        bufOut_Fin_R[mFilter.j_0] = bufIn_Fin_R[mFilter.j_0] * mFilter.b_Ref[rad][0] + bufIn_Fin_R[mFilter.j_1] * mFilter.b_Ref[rad][1] + bufIn_Fin_R[mFilter.j_2] * mFilter.b_Ref[rad][2] + bufIn_Fin_R[mFilter.j_3] * mFilter.b_Ref[rad][3] - bufOut_Fin_R[mFilter.j_1] * mFilter.a_Ref[rad][0] - bufOut_Fin_R[mFilter.j_2] * mFilter.a_Ref[rad][1] - bufOut_Fin_R[mFilter.j_3] * mFilter.a_Ref[rad][2];
        
        double xL = bufOut_L[mFilter.i_0];
        double xR = bufOut_R[mFilter.i_0];
        double x_fin_L = bufOut_Fin_L[mFilter.j_0];
        double x_fin_R = bufOut_Fin_R[mFilter.j_0];
        
        outL = inL * (1.0 - *dryWetMix_) + *dryWetMix_ * ((1-multitapDelay_) * (*gainLeft_ * mDelayLine.delayLineL(xL) + *gainRefLeft_ * mDelayLine.delayLine_Ref_L(x_fin_L)) + multitapDelay_ * (*gainLeft_* (mDelayLine.delayLineRepL(xL, tempoInSamples, *tempo_, *feedback_)) + *gainRefLeft_ * (mDelayLine.delayLineRep_Ref_L(x_fin_L, tempoInSamples, *tempo_, *feedback_))));
        
               
        outR = inR * (1.0 - *dryWetMix_) + *dryWetMix_ * ((1-multitapDelay_) * (*gainRight_ * mDelayLine.delayLineR(xR) + *gainRefRight_ * mDelayLine.delayLine_Ref_R(x_fin_R)) + multitapDelay_ * (*gainRight_* (mDelayLine.delayLineRepR(xR, tempoInSamples, *tempo_, *feedback_)) + *gainRefRight_ * (mDelayLine.delayLineRep_Ref_R(x_fin_R, tempoInSamples, *tempo_, *feedback_))));
        
        channelDataL[i] = outL;
        channelDataR[i] = outR;
    
    }


    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
}


//==============================================================================
bool VirtualTubeDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* VirtualTubeDelayAudioProcessor::createEditor()
{
    return new VirtualTubeDelayAudioProcessorEditor(*this);
}

//==============================================================================
void VirtualTubeDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    ScopedPointer<XmlElement> xml (parameters.state.createXml());
    copyXmlToBinary (*xml, destData);
}

void VirtualTubeDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState != nullptr){
        if (xmlState->hasTagName (parameters.state.getType()))
        {
            parameters.state = ValueTree::fromXml(*xmlState);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VirtualTubeDelayAudioProcessor();
}
