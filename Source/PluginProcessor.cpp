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
    
    parameters.createAndAddParameter("tubeLengthLeft_", "tubeLengthLeft", "tubeLengthLeft", NormalisableRange<float>(2.0f,30.0f), 10.0f, nullptr, nullptr);
    parameters.createAndAddParameter("tubeLengthRight_", "tubeLengthRight", "tubeLengthRight", NormalisableRange<float>(2.0f,30.0f), 10.0f, nullptr, nullptr);
    parameters.createAndAddParameter("gainLeft_", "gainLeft", "gainLeft", NormalisableRange<float>(-128.0f,19.0f), 0.0f, nullptr, nullptr);
    parameters.createAndAddParameter("gainRight_", "gainRight", "gainRight", NormalisableRange<float>(-128.0f,19.0f), 0.0f, nullptr, nullptr);
    parameters.createAndAddParameter("dryWetMix_", "dryWetMix", "dryWetMix", NormalisableRange<float>(0.0f, 1.0f), 0, nullptr, nullptr);
    parameters.createAndAddParameter("tubeSize_", "tubeSize", "tubeSize", NormalisableRange<float>(1.2,2.5), 1.2, nullptr, nullptr);
    parameters.createAndAddParameter("tubeEndLeft_", "tubeEndLeft", "tubeEndLeft", NormalisableRange<float>(1.0f,5.0f), 1.0f, nullptr, nullptr);
    parameters.createAndAddParameter("tubeEndRight_", "tubeEndRight", "tubeEndRight", NormalisableRange<float>(1.0f,5.0f), 1.0f, nullptr, nullptr);
    parameters.createAndAddParameter("gainRefLeft_", "gainRefLeft", "gainRefLeft", NormalisableRange<float>(-128.0f,25.0f), 0.0f, nullptr, nullptr);
    parameters.createAndAddParameter("gainRefRight_", "gainRefRight", "gainRefRight", NormalisableRange<float>(-128.0f,25.0f), 0.0f, nullptr, nullptr);
    parameters.createAndAddParameter("feedback_", "feedback", "feedback", NormalisableRange<float>(0.1f,0.9f), 0.1f, nullptr, nullptr);
    parameters.createAndAddParameter("tempo_", "tempo", "tempo", NormalisableRange<float>(2,32), 2, nullptr, nullptr);
    parameters.createAndAddParameter("multitap_", "multitap", "multitap", NormalisableRange<float>(0,1), false, nullptr, nullptr, true);
    parameters.createAndAddParameter("sync_", "sync", "sync", NormalisableRange<float>(0,1), false, nullptr, nullptr, true);
    
    
    parameters.state = ValueTree("SavedParams");
    
    tubeLengthLeft_ = parameters.getRawParameterValue ("tubeLengthLeft_");
    tubeLengthRight_ = parameters.getRawParameterValue ("tubeLengthRight_");
    gainLeft_ = parameters.getRawParameterValue ("gainLeft_");
    gainRight_ = parameters.getRawParameterValue ("gainRight_");
    dryWetMix_ = parameters.getRawParameterValue ("dryWetMix_");
    tubeSize_ = parameters.getRawParameterValue ("tubeSize_");
    tubeEndLeft_ = parameters.getRawParameterValue ("tubeEndLeft_");
    tubeEndRight_ = parameters.getRawParameterValue ("tubeEndRight_");
    gainRefLeft_ = parameters.getRawParameterValue ("gainRefLeft_");
    gainRefRight_ = parameters.getRawParameterValue ("gainRefRight_");
    feedback_ = parameters.getRawParameterValue ("feedback_");
    tempo_ = parameters.getRawParameterValue ("tempo_");
    multitap_ = parameters.getRawParameterValue ("multitap_");
    sync_ = parameters.getRawParameterValue ("sync_");


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
    
    for(int channel = 0; channel < getTotalNumOutputChannels(); ++channel)
    {
        mDelayLine[channel].suspend();
        mDelayLine_ref[channel].suspend();
    }
    
    // Set default values:
    for(int channel = 0; channel < getTotalNumOutputChannels(); ++channel)
    {
        leng[channel] = 10.0f;
        delayMilli[channel] = 28.985507246376812f;
        previousDelaySamples[channel] = delaySamples[channel] = 1278.2608695652175f;
        lengRef[channel] = 12.0f;
        delayMilliRef[channel] = 34.78260869565217f;
        previousDelaySamplesRef[channel] = delaySamplesRef[channel] = 1533.913043478260f;
        
        previousGain[channel] = 0.0f;
        previousGainRef[channel] = 0.0f;
        
        mDelayLine[channel].setSampleRate(getSampleRate());
        mFilter[channel].setSampleRate(getSampleRate());
        
        mDelayLine_ref[channel].setSampleRate(getSampleRate());
        mFilter_ref[channel].setSampleRate(getSampleRate());
        
        mDelayLine[channel].initialize();
        mDelayLine_ref[channel].initialize();
        
    }
    
    tempoBpm_ = 120;
    
    /*delayBufferLeft_2.setSize(1, delayBufferLength_);
    delayBufferRight_2.setSize(1, delayBufferLength_);
    delayBufferLeftRef_2.setSize(1, delayBufferLengthRef_);
    delayBufferRightRef_2.setSize(1, delayBufferLengthRef_);*/
    
    playHead = this->getPlayHead();
    playHead->getCurrentPosition (currentPositionInfo);
    
    beatLenghtInSec = tempoBpm_/60;
    beatLenghtInSamples = beatLenghtInSec * getSampleRate();
    
    //auto tubeLengthLeft_Copy = tubeLengthLeft_->get();
    
}
void VirtualTubeDelayAudioProcessor::releaseResources()
{
    for(int channel = 0; channel < getTotalNumOutputChannels(); ++channel)
    {
        mDelayLine[channel].suspend();
        mDelayLine_ref[channel].suspend();
    }
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
    
    //storing parameters values
    int sync = 0;
    if(*sync_){sync = 1;}
   
    int multitapDelay = 0;
    if(*multitap_){multitapDelay = 1;}
    
    float wetValue_ = *dryWetMix_;
    float currentFeedback = *feedback_;
    int tempo = *tempo_;
    
    rad = floor(*tubeSize_*10 - 12);
    
    currentGain[0] = powf(10, *gainLeft_ / 20);
    currentGain[1] = powf(10, *gainRight_ / 20);
    currentGainRef[0] = powf(10, *gainRefLeft_ / 20);
    currentGainRef[1] = powf(10, *gainRefRight_ / 20);
    
    applyGain(numSamples);
    
    tubeLength[0] = *tubeLengthLeft_;
    tubeLength[1] = *tubeLengthRight_;
    tubeEnd[0] = *tubeEndLeft_ *2;
    tubeEnd[1] = *tubeEndRight_ *2;
    
    tempoBpm_ = currentPositionInfo.bpm;
    beatLenghtInSec = tempoBpm_/60;
    beatLenghtInSamples = beatLenghtInSec * getSampleRate();
    tempoInSample[0] = beatLenghtInSamples/ tempo;
    tempoInSample[1] = beatLenghtInSamples/ tempo;
    
    for (int channel = 0; channel < 2; ++channel)
    {

        float* channelData = buffer.getWritePointer(channel);
        
        //computing delay samples
        leng[channel] = mFilter[channel].setLengt(tubeLength[channel]);
        delayMilli[channel] = mFilter[channel].setDelayMilliseconds(leng[channel]);
        delaySamples[channel] = mFilter[channel].setDelaySamples(delayMilli[channel]);
        
        //computing delay samples (reflection)
        lengRef[channel] = leng[channel] + mFilter_ref[channel].setLengt(tubeEnd[channel]);
        delayMilliRef[channel] = mFilter_ref[channel].setDelayMilliseconds(lengRef[channel]);
        delaySamplesRef[channel] = mFilter_ref[channel].setDelaySamples(delayMilliRef[channel]);
        
        applyFilterDelay(numSamples, channel);
        
        mDelayLine[channel].setDelay(interpolatedDelaySamples[channel], channel);
        mDelayLine_ref[channel].setDelay(interpolatedDelaySamples[channel], channel);
    
        for (int i = 0; i < numSamples; ++i)
        {
            process(channel);
        
            //computing filter coefficients
            mFilter[channel].setValues(interpolatedTubeLength[channel], rad);
            mFilter[channel].getCalculatedCoefficients();
        
            //computing filter coefficients (reflection)
            mFilter_ref[channel].setValues(interpolatedTubeEnd[channel], rad);
            mFilter_ref[channel].getCalculatedCoefficients();
        
            //setting delaylines
            mDelayLine[channel].setDelay(interpolatedDelaySamples[channel], channel);
            mDelayLine_ref[channel].setDelay(interpolatedDelaySamplesRef[channel], channel);
        
            const double in = channelData[i];
            
            double out = 0.0;
        
            double x = computeOutFilter(in, channel);
        
            double x_fin = computeOutReflectionFilter(x, rad, channel);
            
            double multitapOut = interpolatedGain[channel] * (mDelayLine[channel].delayLineRep(x, interpolatedDelaySamples[channel], currentFeedback, channel)) + interpolatedGainRef[channel] * (mDelayLine_ref[channel].delayLineRep(x_fin, interpolatedDelaySamplesRef[channel], currentFeedback, channel));
        
            double syncOut = interpolatedGain[channel] * (mDelayLine[channel].delayLineRepSync(x, tempoInSample[channel], currentFeedback, channel)) + interpolatedGainRef[channel] * (mDelayLine_ref[channel].delayLineRepSync(x_fin, tempoInSample[channel], currentFeedback, channel));
        
            double delayOut = interpolatedGain[channel] * mDelayLine[channel].delayLine(x, channel) + interpolatedGainRef[channel] * mDelayLine_ref[channel].delayLine(x_fin, channel);
            
            out = (1.0 - wetValue_) * in + wetValue_ * ((1 - multitapDelay) * delayOut + (1 - sync) * multitapDelay * multitapOut + sync * multitapDelay * syncOut);
            
            channelData[i] = out;
    
            interpolatedGain[channel] += incrementGain[channel];
        
            interpolatedGainRef[channel] += incrementGainRef[channel];
        
            interpolatedTubeLength[channel] += incrementTubeLength[channel];

            interpolatedTubeEnd[channel] += incrementTubeEnd[channel];

            interpolatedDelaySamples[channel] += incrementDelaySamples[channel];
        
            interpolatedDelaySamplesRef[channel] += incrementDelaySamplesRef[channel];

        }
    }

    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
}

void VirtualTubeDelayAudioProcessor::process(int channel) {
    
    i_0 = ptr[channel]%7;       //->6
    i_1 = (ptr[channel] + 1)%7; //->0
    i_2 = (ptr[channel] + 2)%7; //->1
    i_3 = (ptr[channel] + 3)%7; //->2
    i_4 = (ptr[channel] + 4)%7; //->3
    i_5 = (ptr[channel] + 5)%7; //->4
    i_6 = (ptr[channel] + 6)%7; //->5
    
    if (--ptr[channel] < 0) { ptr[channel] += 7; }
    
    j_0 = ptr2[channel]%4;       //->3
    j_1 = (ptr2[channel] + 1)%4; //->0
    j_2 = (ptr2[channel] + 2)%4; //->1
    j_3 = (ptr2[channel] + 3)%4; //->2
    
    if (--ptr2[channel] < 0) { ptr2[channel] += 4; }
}


double VirtualTubeDelayAudioProcessor::computeOutFilter(double input, int channel){
    
    double in = input;
    double out;
    
    bufIn[channel][i_0] = in;
    
    bufOut[channel][i_0] = bufIn[channel][i_0] * mFilter[channel].b0f + bufIn[channel][i_1] * mFilter[channel].b1f + bufIn[channel][i_2] * mFilter[channel].b2f + bufIn[channel][i_3] * mFilter[channel].b3f + bufIn[channel][i_4] * mFilter[channel].b4f + bufIn[channel][i_5] * mFilter[channel].b5f + bufIn[channel][i_6] * mFilter[channel].b6f - bufOut[channel][i_1] * mFilter[channel].a1f - bufOut[channel][i_2] * mFilter[channel].a2f - bufOut[channel][i_3] * mFilter[channel].a3f - bufOut[channel][i_4] * mFilter[channel].a4f - bufOut[channel][i_5] * mFilter[channel].a5f - bufOut[channel][i_6] * mFilter[channel].a6f;
    
    out = bufOut[channel][i_0];
    
    return out;
    
}

double VirtualTubeDelayAudioProcessor::computeOutReflectionFilter(double input, int rad, int channel){
    
    double in = input;
    double out;
    
    bufIn_Ref[channel][i_0] = in;
    
    bufOut_Ref[channel][i_0] = bufIn_Ref[channel][i_0] * mFilter_ref[channel].b0f + bufIn_Ref[channel][i_1] * mFilter_ref[channel].b1f + bufIn_Ref[channel][i_2] * mFilter_ref[channel].b2f + bufIn_Ref[channel][i_3] * mFilter_ref[channel].b3f + bufIn_Ref[channel][i_4] * mFilter_ref[channel].b4f + bufIn_Ref[channel][i_5] * mFilter_ref[channel].b5f + bufIn_Ref[channel][i_6] * mFilter_ref[channel].b6f - bufOut_Ref[channel][i_1] * mFilter_ref[channel].a1f - bufOut_Ref[channel][i_2] * mFilter_ref[channel].a2f - bufOut_Ref[channel][i_3] * mFilter_ref[channel].a3f - bufOut_Ref[channel][i_4] * mFilter_ref[channel].a4f - bufOut_Ref[channel][i_5] * mFilter_ref[channel].a5f - bufOut_Ref[channel][i_6] * mFilter_ref[channel].a6f;
    
    bufIn_Fin[channel][j_0] = bufOut_Ref[channel][i_0];
    
    bufOut_Fin[channel][j_0] = bufIn_Fin[channel][j_0] * b_Ref[rad][0] + bufIn_Fin[channel][j_1] * b_Ref[rad][1] + bufIn_Fin[channel][j_2] * b_Ref[rad][2] + bufIn_Fin[channel][j_3] * b_Ref[rad][3] - bufOut_Fin[channel][j_1] * a_Ref[rad][0] - bufOut_Fin[channel][j_2] * a_Ref[rad][1] - bufOut_Fin[channel][j_3] * a_Ref[rad][2];
    
    out = bufOut_Fin[channel][j_0];
    
    return out;
    
}

void VirtualTubeDelayAudioProcessor::applyFilterDelay(int numSamples, int channel){
    
    //interpolating lengths (filter coefficients)
    incrementTubeLength[channel] = (tubeLength[channel] - previousTubeLength[channel]) / (float) numSamples;
    interpolatedTubeLength[channel] = previousTubeLength[channel];
    
    previousTubeLength[channel] = tubeLength[channel];
    
    incrementTubeEnd[channel] = (tubeEnd[channel] - previousTubeEnd[channel]) / (float) numSamples;
    interpolatedTubeEnd[channel] = previousTubeEnd[channel];
    
    previousTubeEnd[channel] = tubeEnd[channel];
    
    //interpolating delays
    incrementDelaySamples[channel] = (delaySamples[channel] - previousDelaySamples[channel]) / (float) numSamples;
    interpolatedDelaySamples[channel] = previousDelaySamples[channel];

    previousDelaySamples[channel] = delaySamples[channel];
    
    incrementDelaySamplesRef[channel] = (delaySamplesRef[channel] - previousDelaySamplesRef[channel]) / (float) numSamples;
    interpolatedDelaySamplesRef[channel] = previousDelaySamplesRef[channel];
    
    previousDelaySamplesRef[channel] = delaySamplesRef[channel];
    
}

void VirtualTubeDelayAudioProcessor::applyGain(int numSamples){
    
    for(int i = 0; i < 2; ++i)
    {
        incrementGain[i] = (currentGain[i] - previousGain[i]) / (double) numSamples;
        interpolatedGain[i] = previousGain[i];
    
        previousGain[i] = currentGain[i];
    
        incrementGainRef[i] = (currentGainRef[i] - previousGainRef[i]) / (double) numSamples;
        interpolatedGainRef[i] = previousGainRef[i];
    
        previousGainRef[i] = currentGainRef[i];
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
