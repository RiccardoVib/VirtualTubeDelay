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
    parameters.createAndAddParameter("gainLeft_", "gainLeft", "gainLeft", NormalisableRange<float>(0,9), 2, nullptr, nullptr);
    parameters.createAndAddParameter("gainRight_", "gainRight", "gainRight", NormalisableRange<float>(0,9), 2, nullptr, nullptr);
    parameters.createAndAddParameter("dryWetMix_", "dryWetMix", "dryWetMix", NormalisableRange<float>(0.0, 1.0), 0, nullptr, nullptr);
    parameters.createAndAddParameter("tubeSize_", "tubeSize", "tubeSize", NormalisableRange<float>(1.2,2.5), 1.2, nullptr, nullptr);
    parameters.createAndAddParameter("tubeEndLeft_", "tubeEndLeft", "tubeEndLeft", NormalisableRange<float>(1,5), 1, nullptr, nullptr);
    parameters.createAndAddParameter("tubeEndRight_", "tubeEndRight", "tubeEndRight", NormalisableRange<float>(1,5), 1, nullptr, nullptr);
    parameters.createAndAddParameter("gainRefLeft_", "gainRefLeft", "gainRefLeft", NormalisableRange<float>(0,18), 4, nullptr, nullptr);
    parameters.createAndAddParameter("gainRefRight_", "gainRefRight", "gainRefRight", NormalisableRange<float>(0,18), 4, nullptr, nullptr);
    parameters.createAndAddParameter("feedback_", "feedback", "feedback", NormalisableRange<float>(0.1,0.9), 0.1, nullptr, nullptr);
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

    tempoBpm_ = 120;

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
    
    ptr = 0;
    ptr2 = 0;
    
    i_0 = 0;
    i_1 = 0;
    i_2 = 0;
    i_3 = 0;
    i_4 = 0;
    i_5 = 0;
    i_6 = 0;
    
    j_0 = 0;
    j_1 = 0;
    j_2 = 0;
    j_3 = 0;
    
    previousGain_L = 2;
    previousGain_R = 2;
    previousGainRef_L = 1;
    previousGainRef_R = 1;
    
    previousDelaySamples_L = delaySamples_L;
    previousDelaySamples_R = delaySamples_R;
    previousDelaySamplesRef_L = delaySamplesRef_L;
    previousDelaySamplesRef_L = delaySamplesRef_L;
    
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
    
    //auto tubeLengthLeft_Copy = tubeLengthLeft_->get();
    
}
void VirtualTubeDelayAudioProcessor::releaseResources()
{
    mDelayLine.suspend();
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
    
    //storing parameters values
    bool sync = *sync_;
    float wetValue_ = *dryWetMix_;
    float currentFeedback = *feedback_;
    int tempo = *tempo_;
    
    rad = floor(*tubeSize_*10 - 12);
    
    currentGain_L = *gainLeft_;
    currentGain_R = *gainRight_;
    currentGainRef_L = *gainRefLeft_;
    currentGainRef_R = *gainRefRight_;
    
    tubeLengthLeft = *tubeLengthLeft_;
    tubeLengthRight = *tubeLengthRight_;
    tubeEndLeft = *tubeEndLeft_ *2;
    tubeEndRight = *tubeEndRight_ *2;
    
        
    tempoBpm_ = currentPositionInfo.bpm;
    beatLenghtInSec = tempoBpm_/60;
    beatLenghtInSamples = beatLenghtInSec * getSampleRate();
    tempoInSample_L = 2 * beatLenghtInSamples/ tempo;
    tempoInSample_R = 2 * beatLenghtInSamples/ tempo;
    
        
    //computing delay samples
    leng_L = mFilter.setLengt(tubeLengthLeft);
    delayMilli_L = mFilter.setDelayMilliseconds(leng_L);
    delaySamples_L = mFilter.setDelaySamples(delayMilli_L);
        
    leng_R = mFilter.setLengt(tubeLengthRight);
    delayMilli_R = mFilter.setDelayMilliseconds(leng_R);
    delaySamples_R = mFilter.setDelaySamples(delayMilli_R);
        
    //computing delay samples (reflection)
    lengRef_L = leng_L + mFilter.setLengt(tubeEndLeft);
    delayMilliRef_L = mFilter.setDelayMilliseconds(lengRef_L);
    delaySamplesRef_L = mFilter.setDelaySamples(delayMilliRef_L);
        
    lengRef_R = leng_R + mFilter.setLengt(tubeEndRight);
    delayMilliRef_R = mFilter.setDelayMilliseconds(lengRef_R);
    delaySamplesRef_R = mFilter.setDelaySamples(delayMilliRef_R);
    
    applyFilterDelay_L(numSamples);
    applyFilterDelay_R(numSamples);
    
    mDelayLine.setDelay_L(interpolatedDelaySamples_L);
    mDelayLine.setDelay_R(interpolatedDelaySamples_R);
    mDelayLine.setDelay_Ref_L(interpolatedDelaySamplesRef_L);
    mDelayLine.setDelay_Ref_R(interpolatedDelaySamplesRef_R);
    
    applyGain(numSamples);
    
    for (int i = 0; i < numSamples; ++i)
    {
        process();
        
        //computing filter coefficients
        mFilter.setValues(interpolatedTubeLength_L, rad);
        mFilter.getCalculatedCoefficients(0);
        
        mFilter.setValues(interpolatedTubeLength_R, rad);
        mFilter.getCalculatedCoefficients(1);
        
        //computing filter coefficients (reflection)
        mFilter.setValues(interpolatedTubeEnd_L, rad);
        mFilter.getCalculatedCoefficients_Ref(0);
        
        mFilter.setValues(interpolatedTubeEnd_R, rad);
        mFilter.getCalculatedCoefficients_Ref(1);
        
        //setting delaylines
        mDelayLine.setDelay_L(interpolatedDelaySamples_L);
        mDelayLine.setDelay_R(interpolatedDelaySamples_R);
        
        mDelayLine.setDelay_Ref_L(interpolatedDelaySamplesRef_L);
        mDelayLine.setDelay_Ref_R(interpolatedDelaySamplesRef_R);
        
        const double inL = channelDataL[i];
        const double inR = channelDataR[i];
        
        double outL = 0.0;
        double outR = 0.0;
        
        double xL = computeOutFilter_L(inL);
        double xR = computeOutFilter_R(inR);
        
        double x_fin_L = computeOutReflectionFilter_L(outL);
        double x_fin_R = computeOutReflectionFilter_R(outR);
        
        
        double multitapOutL = interpolatedGain_L * (mDelayLine.delayLineRep_L(xL, interpolatedDelaySamples_L, currentFeedback)) + interpolatedGainRef_L * (mDelayLine.delayLineRep_Ref_L(x_fin_L, interpolatedDelaySamplesRef_L, currentFeedback));
        
        double syncOutL = interpolatedGain_L * (mDelayLine.delayLineRep_L(xL, tempoInSample_L, currentFeedback)) + interpolatedGainRef_L * (mDelayLine.delayLineRep_Ref_L(x_fin_L, tempoInSample_L, currentFeedback));
        
        double delayOutL = interpolatedGain_L  * mDelayLine.delayLine_L(xL) + interpolatedGainRef_L * mDelayLine.delayLine_Ref_L(x_fin_L);
        
        outL = (1.0 - wetValue_) * inL + wetValue_ * ((1 - multitapDelay_) * delayOutL + (1 - sync) * multitapDelay_ * multitapOutL + sync * multitapDelay_ * syncOutL);
                                                      
        //outL = (1.0 - wetValue_) * inL + wetValue_ * ((1 - multitapDelay_) * delayOutL + multitapDelay_ * multitapOutL);
            
        double multitapOutR = interpolatedGain_R * (mDelayLine.delayLineRep_R(xR, interpolatedDelaySamples_R, currentFeedback)) + interpolatedGainRef_R * (mDelayLine.delayLineRep_Ref_R(x_fin_R, interpolatedDelaySamplesRef_R, currentFeedback));
        
        double syncOutR = interpolatedGain_R * (mDelayLine.delayLineRep_R(xR, tempoInSample_R, currentFeedback)) + interpolatedGainRef_R * (mDelayLine.delayLineRep_Ref_R(x_fin_R, tempoInSample_R, currentFeedback));
        
        double delayOutR = interpolatedGain_R  * mDelayLine.delayLine_R(xR) + interpolatedGainRef_R * mDelayLine.delayLine_Ref_R(x_fin_R);
        
        outR = (1.0 - wetValue_) * inR + wetValue_ * ((1 - multitapDelay_) * delayOutR + (1 - sync) * multitapDelay_ * multitapOutR + sync * multitapDelay_ * syncOutR);
        
 
        //outR = (1.0 - wetValue_) * inR + wetValue_ * ((1 - multitapDelay_) * delayOutR + multitapDelay_ * multitapOutR);
        
        channelDataL[i] = outL;
        channelDataR[i] = outR;
    
        interpolatedGain_L += incrementGain_L;
        interpolatedGain_R += incrementGain_R;
        
        interpolatedGainRef_L += incrementGainRef_L;
        interpolatedGainRef_R += incrementGainRef_R;
        
        interpolatedTubeLength_L += incrementTubeLength_L;
        interpolatedTubeLength_R += incrementTubeLength_R;

        interpolatedTubeEnd_L += incrementTubeEnd_L;
        interpolatedTubeEnd_R += incrementTubeEnd_R;

        interpolatedDelaySamples_L += incrementDelaySamples_L;
        interpolatedDelaySamples_R += incrementDelaySamples_R;
        
        interpolatedDelaySamplesRef_L += incrementDelaySamplesRef_L;
        interpolatedDelaySamplesRef_R += incrementDelaySamplesRef_R;

    }

    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
}


void VirtualTubeDelayAudioProcessor::applyFilterDelay_L(int numSamples){
    
    //interpolating lengths (filter coefficients)
    incrementTubeLength_L = (tubeLengthLeft - previousTubeLength_L) / (float) numSamples;
    interpolatedTubeLength_L = previousTubeLength_L;
    
    previousTubeLength_L = tubeLengthLeft;
    
    incrementTubeEnd_L = (tubeEndLeft - previousTubeEnd_L) / (float) numSamples;
    interpolatedTubeEnd_L = previousTubeEnd_L;
    
    previousTubeEnd_L = tubeEndLeft;
    
    //interpolating delays
    incrementDelaySamples_L = (delaySamples_L - previousDelaySamples_L) / (float) numSamples;
    interpolatedDelaySamples_L = previousDelaySamples_L;

    previousDelaySamples_L = delaySamples_L;
    
    incrementDelaySamplesRef_L = (delaySamplesRef_L - previousDelaySamplesRef_L) / (float) numSamples;
    interpolatedDelaySamplesRef_L = previousDelaySamplesRef_L;
    
    previousDelaySamplesRef_L = delaySamplesRef_L;
    
}

void VirtualTubeDelayAudioProcessor::applyFilterDelay_R(int numSamples){
    
    //interpolating lengths (filter coefficients)
    incrementTubeLength_R = (tubeLengthRight - previousTubeLength_R) / (float) numSamples;
    interpolatedTubeLength_R = previousTubeLength_R;
    
    previousTubeLength_R = tubeLengthRight;
    
    incrementTubeEnd_R = (tubeEndRight - previousTubeEnd_R) / (float) numSamples;
    interpolatedTubeEnd_R = previousTubeEnd_R;
    
    previousTubeEnd_R = tubeEndRight;

    //interpolating delays
    incrementDelaySamples_R = (delaySamples_R - previousDelaySamples_R) / (float) numSamples;
    interpolatedDelaySamples_R = previousDelaySamples_R;
    
    previousDelaySamples_R = delaySamples_R;
    
    incrementDelaySamplesRef_R = (delaySamplesRef_R - previousDelaySamplesRef_R) / (float) numSamples;
    interpolatedDelaySamplesRef_R = previousDelaySamplesRef_R;
    
    previousDelaySamplesRef_R = delaySamplesRef_R;
}



void VirtualTubeDelayAudioProcessor::applyGain(int numSamples){
    
    //left channel
    incrementGain_L = (currentGain_L - previousGain_L) / (double) numSamples;
    interpolatedGain_L = previousGain_L;
    
    previousGain_L = currentGain_L;
    
    incrementGainRef_L = (currentGainRef_L - previousGainRef_L) / (double) numSamples;
    interpolatedGainRef_L = previousGainRef_L;
    
    previousGainRef_L = currentGainRef_L;

    //right channel
    incrementGain_R = (currentGain_R - previousGain_R) / (double) numSamples;
    interpolatedGain_R = previousGain_R;
    
    previousGain_R = currentGain_R;
    
    incrementGainRef_R = (currentGainRef_R - previousGainRef_R) / (double) numSamples;
    interpolatedGainRef_R = previousGainRef_R;
    
    previousGainRef_R = currentGainRef_R;
}

void VirtualTubeDelayAudioProcessor::process() {
    
    i_0 = ptr%7;       //->6
    i_1 = (ptr + 1)%7; //->0
    i_2 = (ptr + 2)%7; //->1
    i_3 = (ptr + 3)%7; //->2
    i_4 = (ptr + 4)%7; //->3
    i_5 = (ptr + 5)%7; //->4
    i_6 = (ptr + 6)%7; //->5
    
    if (--ptr < 0) { ptr += 7; }
    
    j_0 = ptr2%4;       //->3
    j_1 = (ptr2 + 1)%4; //->0
    j_2 = (ptr2 + 2)%4; //->1
    j_3 = (ptr2 + 3)%4; //->2
    
    if (--ptr2 < 0) { ptr2 += 4; }
}


double VirtualTubeDelayAudioProcessor::computeOutFilter_L(double input){
 
    double inL = input;
    double out;
 
    bufIn_L[i_0] = inL;
 
    bufOut_L[i_0] = bufIn_L[i_0] * mFilter.b0f_L + bufIn_L[i_1] * mFilter.b1f_L + bufIn_L[i_2] * mFilter.b2f_L + bufIn_L[i_3] * mFilter.b3f_L + bufIn_L[i_4] * mFilter.b4f_L + bufIn_L[i_5] * mFilter.b5f_L + bufIn_L[i_6] * mFilter.b6f_L - bufOut_L[i_1] * mFilter.a1f_L - bufOut_L[i_2] * mFilter.a2f_L - bufOut_L[i_3] * mFilter.a3f_L - bufOut_L[i_4] * mFilter.a4f_L - bufOut_L[i_5] * mFilter.a5f_L - bufOut_L[i_6] * mFilter.a6f_L;
 
    out = bufOut_L[i_0];
  
 return out;
 
 }

double VirtualTubeDelayAudioProcessor::computeOutFilter_R(double input){
    
    double inR = input;
    double out;
    
    bufIn_R[i_0] = inR;

    bufOut_R[i_0] = bufIn_R[i_0] * mFilter.b0f_R + bufIn_R[i_1] * mFilter.b1f_R + bufIn_R[i_2] * mFilter.b2f_R + bufIn_R[i_3] * mFilter.b3f_R + bufIn_R[i_4] * mFilter.b4f_R + bufIn_R[i_5] * mFilter.b5f_R + bufIn_R[i_6] * mFilter.b6f_R - bufOut_R[i_1] * mFilter.a1f_R - bufOut_R[i_2] * mFilter.a2f_R - bufOut_R[i_3] * mFilter.a3f_R - bufOut_R[i_4] * mFilter.a4f_R - bufOut_R[i_5] * mFilter.a5f_R - bufOut_R[i_6] * mFilter.a6f_R;

    out = bufOut_R[i_0];
    
    return out;
    
}

 double VirtualTubeDelayAudioProcessor::computeOutReflectionFilter_L(double input){
 
     double inL = input;
     double out;
 
     bufIn_Ref_L[i_0] = inL;
  
     bufOut_Ref_L[i_0] = bufIn_Ref_L[i_0] * mFilter.b0f_Ref_L + bufIn_Ref_L[i_1] * mFilter.b1f_Ref_L + bufIn_Ref_L[i_2] * mFilter.b2f_Ref_L + bufIn_Ref_L[i_3] * mFilter.b3f_Ref_L + bufIn_Ref_L[i_4] * mFilter.b4f_Ref_L + bufIn_Ref_L[i_5] * mFilter.b5f_Ref_L + bufIn_Ref_L[i_6] * mFilter.b6f_Ref_L - bufOut_Ref_L[i_1] * mFilter.a1f_Ref_L - bufOut_Ref_L[i_2] * mFilter.a2f_Ref_L - bufOut_Ref_L[i_3] * mFilter.a3f_Ref_L - bufOut_Ref_L[i_4] * mFilter.a4f_Ref_L - bufOut_Ref_L[i_5] * mFilter.a5f_Ref_L - bufOut_Ref_L[i_6] * mFilter.a6f_Ref_L;
 
     bufIn_Fin_L[j_0] = bufOut_Ref_L[i_0];
 
     bufOut_Fin_L[j_0] = bufIn_Fin_L[j_0] * mFilter.b_Ref[rad][0] + bufIn_Fin_L[j_1] * mFilter.b_Ref[rad][1] + bufIn_Fin_L[j_2] * mFilter.b_Ref[rad][2] + bufIn_Fin_L[j_3] * mFilter.b_Ref[rad][3] - bufOut_Fin_L[j_1] * mFilter.a_Ref[rad][0] - bufOut_Fin_L[j_2] * mFilter.a_Ref[rad][1] - bufOut_Fin_L[j_3] * mFilter.a_Ref[rad][2];
 
     out = bufOut_Fin_L[j_0];
 
     return out;
 
 }

double VirtualTubeDelayAudioProcessor::computeOutReflectionFilter_R(double input){

    double inR = input;
    double out;

    bufIn_Ref_R[i_0] = inR;

    bufOut_Ref_R[i_0] = bufIn_Ref_R[i_0] * mFilter.b0f_Ref_R + bufIn_Ref_R[i_1] * mFilter.b1f_Ref_R + bufIn_Ref_R[i_2] * mFilter.b2f_Ref_R + bufIn_Ref_R[i_3] * mFilter.b3f_Ref_R + bufIn_Ref_R[i_4] * mFilter.b4f_Ref_R + bufIn_Ref_R[i_5] * mFilter.b5f_Ref_R + bufIn_Ref_R[i_6] * mFilter.b6f_Ref_R - bufOut_Ref_R[i_1] * mFilter.a1f_Ref_R - bufOut_Ref_R[i_2] * mFilter.a2f_Ref_R - bufOut_Ref_R[i_3] * mFilter.a3f_Ref_R - bufOut_Ref_R[i_4] * mFilter.a4f_Ref_R - bufOut_Ref_R[i_5] * mFilter.a5f_Ref_R - bufOut_Ref_R[i_6] * mFilter.a6f_Ref_R;

    bufIn_Fin_R[j_0] = bufOut_Ref_R[i_0];

    bufOut_Fin_R[j_0] = bufIn_Fin_R[j_0] * mFilter.b_Ref[rad][0] + bufIn_Fin_R[j_1] * mFilter.b_Ref[rad][1] + bufIn_Fin_R[j_2] * mFilter.b_Ref[rad][2] + bufIn_Fin_R[j_3] * mFilter.b_Ref[rad][3] - bufOut_Fin_R[j_1] * mFilter.a_Ref[rad][0] - bufOut_Fin_R[j_2] * mFilter.a_Ref[rad][1] - bufOut_Fin_R[j_3] * mFilter.a_Ref[rad][2];
    
    out = bufOut_Fin_R[j_0];
    
    return out;
    
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
