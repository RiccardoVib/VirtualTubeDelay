/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"
#include "DelayLine.h"

//==============================================================================
/**
*/

//reflection filters coefficients values

//step_0 - 1.2 cm
const double B0r_0 = 0.00148875526585464;
const double B1r_0 = -0.00120708383241042;
const double B2r_0 = -0.00148190029224148;
const double B3r_0 = 0.00121393880602358;

const double A1r_0 = -2.89790633258181;
const double A2r_0 = 2.79802595323123;
const double A3r_0 = -0.900105910702194;

//step_1 - 1.3 cm
const double B0r_1 = 0.00335592831460436;
const double B1r_1 = -0.00277817344018852;
const double B2r_1 = -0.00334268955647620;
const double B3r_1 = 0.00279141219831668;

const double A1r_1 = -2.88825538503306;
const double A2r_1 = 2.77989104675777;
const double A3r_1 = -0.891609184208459;

//step_2 - 1.4 cm
const double B0r_2 = 0.00517270575773444;
const double B1r_2 = -0.00436824166171923;
const double B2r_2 = -0.00515548132738072;
const double B3r_2 = 0.00438546609207296;

const double A1r_2 = -2.87865489770775;
const double A2r_2 = 2.76156314738057;
const double A3r_2 = -0.882873800812105;

//step_3 - 1.5 cm
const double B0r_3 = 0.00694154483627482;
const double B1r_3 = -0.00597476665661756;
const double B2r_3 = -0.00692237672582804;
const double B3r_3 = 0.00599393476706433;

const double A1r_3 = -2.86910528623180;
const double A2r_3 = 2.74306469622661;
const double A3r_3 = -0.873921073773921;

//step_4 - 1.6 cm
const double B0r_4 = 0.00866475675339795;
const double B1r_4 = -0.00759543715065878;
const double B2r_4 = -0.00864533731394742;
const double B3r_4 = 0.00761485659010931;

const double A1r_4 = -2.85960675039235;
const double A2r_4 = 2.72441611016413;
const double A3r_4 = -0.864770520892871;

//step_5 - 1.7 cm
const double B0r_5 = 0.0103445175450547;
const double B1r_5 = -0.00922813353428962;
const double B2r_5 = -0.0103261959767865;
const double B3r_5 = 0.00924645510255783;

const double A1r_5 = -2.85015929946656;
const double A2r_5 = 2.70563596673260;
const double A3r_5 = -0.855440024129502;

//step_6 - 1.8 cm
const double B0r_6 = 0.0119828779968571;
const double B1r_6 = -0.0108709108283402;
const double B2r_6 = -0.0119666668108299;
const double B3r_6 = 0.0108871220143674;

const double A1r_6 = -2.84076277470616;
const double A2r_6 = 2.68674117057348;
const double A3r_6 = -0.845945973495265;

//step_7 - 1.9 cm
const double B0r_7 = 0.00836341467664481;
const double B1r_7 = -0.00771081517160211;
const double B2r_7 = -0.00835515175240575;
const double B3r_7 = 0.00771907809584116;

const double A1r_7 = -2.88259911416098;
const double A2r_7 = 2.76830119673105;
const double A3r_7 = -0.885685556721597;

//step_8 - 2.0 cm
const double B0r_8 = 0.00900195734508397;
const double B1r_8 = -0.00838163049001607;
const double B2r_8 = -0.00899386146161446;
const double B3r_8 = 0.00838972637348558;

const double A1r_8 = -2.88561377593316;
const double A2r_8 = 2.77407915692424;
const double A3r_8 = -0.888449189224143;

//step_9 - 2.1 cm
const double B0r_9 = 0.00969383015351482;
const double B1r_9 = -0.00910235464057830;
const double B2r_9 = -0.00968593989333203;
const double B3r_9 = 0.00911024490076109;

const double A1r_9 = -2.88827763754024;
const double A2r_9 = 2.77918335198401;
const double A3r_9 = -0.890889933923404;

//step_10 - 2.2 cm
const double B0r_10 = 0.0104428831033720;
const double B1r_10 = -0.00987777161476080;
const double B2r_10 = -0.0104352379207295;
const double B3r_10 = 0.00988541679740335;

const double A1r_10 = -2.89066491723660;
const double A2r_10 = 2.78375610909223;
const double A3r_10 = -0.893075901490345;

//step_11 - 2.3 cm
const double B0r_11 = 0.0112533756990923;
const double B1r_11 = -0.0107128762780108;
const double B2r_11 = -0.0112460156575885;
const double B3r_11 = 0.0107202363195145;

const double A1r_11 = -2.89283178576968;
const double A2r_11 = 2.78790514723905;
const double A3r_11 = -0.895058641386365;

//step_12 - 2.4 cm
const double B0r_12 = 0.0121299824661228;
const double B1r_12 = -0.0116129408030305;
const double B2r_12 = -0.0121229478695646;
const double B3r_12 = 0.0116199753995886;

const double A1r_12 = -2.89482161761424;
const double A2r_12 = 2.79171365153887;
const double A3r_12 = -0.896877964731514;

//step_13 - 2.5 cm
const double B0r_13 = 0.0130778078453958;
const double B1r_13 = -0.0125835707077660;
const double B2r_13 = -0.0130711387557259;
const double B3r_13 = 0.0125902397974359;

const double A1r_13 = -2.89666851198821;
const double A2r_13 = 2.79524702918906;
const double A3r_13 = -0.898565179021510;

static double b_Ref[14][4] = {
    {B0r_0, B1r_0, B2r_0, B3r_0},
    {B0r_1, B1r_1, B2r_1, B3r_1},
    {B0r_2, B1r_2, B2r_2, B3r_2},
    {B0r_3, B1r_3, B2r_3, B3r_3},
    {B0r_4, B1r_4, B2r_4, B3r_4},
    {B0r_5, B1r_5, B2r_5, B3r_5},
    {B0r_6, B1r_6, B2r_6, B3r_6},
    {B0r_7, B1r_7, B2r_7, B3r_7},
    {B0r_8, B1r_8, B2r_8, B3r_8},
    {B0r_9, B1r_9, B2r_9, B3r_9},
    {B0r_10, B1r_10, B2r_10, B3r_10},
    {B0r_11, B1r_11, B2r_11, B3r_11},
    {B0r_12, B1r_12, B2r_12, B3r_12},
    {B0r_13, B1r_13, B2r_13, B3r_13}
};

static double a_Ref[14][3] = {
    {A1r_0, A2r_0, A3r_0},
    {A1r_1, A2r_1, A3r_1},
    {A1r_2, A2r_2, A3r_2},
    {A1r_3, A2r_3, A3r_3},
    {A1r_4, A2r_4, A3r_4},
    {A1r_5, A2r_5, A3r_5},
    {A1r_6, A2r_6, A3r_6},
    {A1r_7, A2r_7, A3r_7},
    {A1r_8, A2r_8, A3r_8},
    {A1r_9, A2r_9, A3r_9},
    {A1r_10, A2r_10, A3r_10},
    {A1r_11, A2r_11, A3r_11},
    {A1r_12, A2r_12, A3r_12},
    {A1r_13, A2r_13, A3r_13}
};

static double bufOut[2][7];
static double bufIn[2][7];

static double bufOut_Ref[2][7];
static double bufIn_Ref[2][7];

static double bufOut_Fin[2][4];
static double bufIn_Fin[2][4];


class VirtualTubeDelayAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    VirtualTubeDelayAudioProcessor();
    ~VirtualTubeDelayAudioProcessor();
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    
   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock(AudioBuffer<float>& buffer, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    // Adjustable parameters:
    float* tubeLengthLeft_ = nullptr; // Tube length in m
    float* tubeLengthRight_ = nullptr;
    float* gainLeft_ = nullptr; // Gain
    float* gainRight_ = nullptr;
    float* dryWetMix_ = nullptr; // Mix level of original and delayed signal (0-1)
    float* tubeSize_ = nullptr; // Size of the tube (1.2-2.5 cm)
    
    float* tubeEndLeft_ = nullptr; // Tube length in m
    float* tubeEndRight_ = nullptr;
    float* gainRefLeft_ = nullptr; // Gain
    float* gainRefRight_ = nullptr;
 
    float* multitap_ = nullptr;

    float* feedback_ = nullptr;
    float* tempo_ = nullptr;
    float* sync_ = nullptr;
    
    float tempoBpm_;
    float beatLenghtInSec;
    float beatLenghtInSamples;
    
    int rad;
    float leng[2];
    float delayMilli[2];
    float delaySamples[2];
    
    float lengRef[2];
    float delayMilliRef[2];
    float delaySamplesRef[2];
    
    Filter mFilter[2];
    DelayLine mDelayLine[2];
    
    Filter mFilter_ref[2];
    DelayLine mDelayLine_ref[2];
    
    AudioProcessorValueTreeState parameters;
    
    void applyGain(int numSamples);
    void applyFilterDelay(int numSamples, int channel);
    
    double computeOutFilter(double input, int channel);
    double computeOutReflectionFilter(double input, int rad, int channel);
    void process(int channel);
    
private:
    
    int ptr[2]{0, 0};
    int ptr2[2]{0, 0};
    
    int i_0{0};
    int i_1{0};
    int i_2{0};
    int i_3{0};
    int i_4{0};
    int i_5{0};
    int i_6{0};
    
    int j_0{0};
    int j_1{0};
    int j_2{0};
    int j_3{0};
    
    float tempoInSample[2];
    
    float currentGain[2];
    float currentGainRef[2];
 
    float previousGain[2];
    float interpolatedGain[2];
    float incrementGain[2];
    
    float previousGainRef[2];
    float interpolatedGainRef[2];
    float incrementGainRef[2];
    
    float previousDelaySamples[2];
    float interpolatedDelaySamples[2];
    float incrementDelaySamples[2];
   
    float previousDelaySamplesRef[2];
    float interpolatedDelaySamplesRef[2];
    float incrementDelaySamplesRef[2];
  
    float tubeLength[2];
    float tubeEnd[2];
    
    float previousTubeLength[2];
    float interpolatedTubeLength[2];
    float incrementTubeLength[2];
    
    float previousTubeEnd[2];
    float interpolatedTubeEnd[2];
    float incrementTubeEnd[2];

    float delayGain[2];
    float incrementDelayGain[2];
    
    int delayBufferLength_;
    int delayBufferLengthRef_;
    
    AudioPlayHead* playHead;
    AudioPlayHead::CurrentPositionInfo currentPositionInfo;
    
    
     // Circular buffer variables for implementing delay
    //AudioBuffer<float> delayBufferLeft_2, delayBufferRight_2, delayBufferLeftRef_2, delayBufferRightRef_2;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VirtualTubeDelayAudioProcessor)
};
