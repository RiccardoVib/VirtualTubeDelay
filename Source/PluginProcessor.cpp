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
                  .withOutput ("Output",    AudioChannelSet::stereo(), true))
{
    // Set default values:
    tubeLengthLeft_ = 10.0;
    tubeLengthRight_ = 10.0;
    gainLeft_ = 0.0;
    gainRight_ = 0.0;
    dryWetMix_ = 0.0;
    tubeSize_ = 1.2;
    enabledReflection_ = false;
    
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
    
        delayBufferLength_ = 1;
        delayBuffer_.setSize(2, delayBufferLength_);
        delayBuffer_.clear();
        mFilter.setSampleRate(getSampleRate());
    
    //auto tubeLengthLeft_Copy = tubeLengthLeft_->get();
    
    
        //delayReadPosition_ = (int)(delayWritePosition_ - (tubeLengthLeft_ * getSampleRate())
                  //             + delayBufferLength_) %
                    //           delayBufferLength_;
    
    rad = floor(tubeSize_*10 - 12);

    leng_L = mFilter.setLengt(tubeLengthLeft_);
    delayMilli_L = mFilter.setDelayMilliseconds(leng_L);
    delaySamples_L = mFilter.setDelaySamples(delayMilli_L);
    mDelayLine.setDelayL(delaySamples_L);
    mFilter.setValues(tubeLengthLeft_, rad);
    mFilter.getCalculatedCoefficients(0);

    leng_R = mFilter.setLengt(tubeLengthRight_);
    delayMilli_R = mFilter.setDelayMilliseconds(leng_R);
    delaySamples_R = mFilter.setDelaySamples(delayMilli_R);
    mDelayLine.setDelayR(delaySamples_R);
    mFilter.setValues(tubeLengthRight_, rad);
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
    //int dpr, dpw;

    
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i){
        buffer.clear(i, 0, buffer.getNumSamples());
    }
    
    float* channelDataL = buffer.getWritePointer(0);
    float* channelDataR = buffer.getWritePointer(1);
    
    //for (int channel = 0; channel < totalNumInputChannels; ++channel)
    //{
      //  float* channelData = buffer.getWritePointer(channel);
       // double* delayData = delayBuffer_.getWritePointer(
        //               jmin (channel,delayBuffer_.getNumChannels() - 1));
        
        //dpr = delayReadPosition_;
        //dpw = delayWritePosition_;
  
    if (!enabledReflection_) {
        
    
        for (int i = 0; i < numSamples; ++i)
        {
            const float inL = channelDataL[i];
            const float inR = channelDataR[i];
            float outL = 0.0;
            float outR = 0.0;
            
            mFilter.process();
            
            bufIn_L[mFilter.i_0] = inL;
            
            bufIn_R[mFilter.i_0] = inR;
            
            bufOut_L[mFilter.i_0] = bufIn_L[mFilter.i_0] * mFilter.b0f_L + bufIn_L[mFilter.i_1] * mFilter.b1f_L + bufIn_L[mFilter.i_2] * mFilter.b2f_L + bufIn_L[mFilter.i_3] * mFilter.b3f_L + bufIn_L[mFilter.i_4] * mFilter.b4f_L + bufIn_L[mFilter.i_5] * mFilter.b5f_L + bufIn_L[mFilter.i_6] * mFilter.b6f_L - bufOut_L[mFilter.i_1] * mFilter.a1f_L - bufOut_L[mFilter.i_2] * mFilter.a2f_L - bufOut_L[mFilter.i_3] * mFilter.a3f_L - bufOut_L[mFilter.i_4] * mFilter.a4f_L - bufOut_L[mFilter.i_5] * mFilter.a5f_L - bufOut_L[mFilter.i_6] * mFilter.a6f_L;
            
            bufOut_R[mFilter.i_0] = bufIn_R[mFilter.i_0] * mFilter.b0f_R + bufIn_R[mFilter.i_1] * mFilter.b1f_R + bufIn_R[mFilter.i_2] * mFilter.b2f_R + bufIn_R[mFilter.i_3] * mFilter.b3f_R + bufIn_R[mFilter.i_4] * mFilter.b4f_R + bufIn_R[mFilter.i_5] * mFilter.b5f_R + bufIn_R[mFilter.i_6] * mFilter.b6f_R - bufOut_R[mFilter.i_1] * mFilter.a1f_R - bufOut_R[mFilter.i_2] * mFilter.a2f_R - bufOut_R[mFilter.i_3] * mFilter.a3f_R - bufOut_R[mFilter.i_4] * mFilter.a4f_R - bufOut_R[mFilter.i_5] * mFilter.a5f_R - bufOut_R[mFilter.i_6] * mFilter.a6f_R;
            
            if (dryWetMix_ == 0) {
                
                outL = inL;
                outR = inR;
                
            }else{
                
                outL = inL * (1.0 - dryWetMix_) + dryWetMix_ * gainLeft_ * mDelayLine.delayLineL(bufOut_L[mFilter.i_0]);
                
                outR  = inR * (1.0 - dryWetMix_) + dryWetMix_ * gainRight_ * mDelayLine.delayLineR(bufOut_R[mFilter.i_0]);
            }
            
            channelDataL[i] = outL;
            channelDataR[i] = outR;
            
        }
    }else{
        
        for (int i = 0; i < numSamples; ++i)
        {
        
            const float inL = channelDataL[i];
            const float inR = channelDataR[i];
            float outL = 0.0;
            float outR = 0.0;
  
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
        
            if (dryWetMix_ == 0) {
                
                outL = inL;
                outR = inR;
                
            }else{
    
                outL = inL * (1.0 - dryWetMix_) + dryWetMix_ * (gainLeft_ * mDelayLine.delayLineL(bufOut_L[mFilter.i_0]) + gainRefLeft_ * mDelayLine.delayLine_Ref_L(bufOut_Fin_L[mFilter.j_0]));
        
            outR = inR * (1.0 - dryWetMix_) + dryWetMix_ * (gainRight_ * mDelayLine.delayLineR(bufOut_R[mFilter.i_0]) + gainRefRight_ * mDelayLine.delayLine_Ref_R(bufOut_Fin_R[mFilter.j_0]));
        
            }
            
            channelDataL[i] = outL;
            channelDataR[i] = outR;
        }
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
    //MemoryOutputStream stream (destData, true);
    //stream.writeFloat (*tubeLengthLeft_);
    //stream.writeFloat (*gainLeft_);
}

void VirtualTubeDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    //MemoryInputStream stream (data, static_cast<size_t> (sizeInBytes), false);
    
    //tubeLengthLeft_->setValueNotifyingHost (stream.readFloat());
    //gainLeft_->setValueNotifyingHost (stream.readFloat());
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VirtualTubeDelayAudioProcessor();
}
