/*
  ==============================================================================

    DelayLine.h
    Created: 17 Oct 2018 1:56:13pm
    Author:  Riccardo Simionato

  ==============================================================================
*/

//
//  DelayLine.hpp
//  VirtualTubeDelay
//
//  Created by Riccardo Simionato on 03/10/18.
//
//

#ifndef DelayLine_hpp
#define DelayLine_hpp
#include <math.h>
#include <tgmath.h>

const int len = (int)(31/0.345)*44.1;
const int len_ref = (int)(46/0.345)*44.1;
static double bufferLeft[len];
static double bufferRight[len];

static double bufferLeft_Ref[len_ref];
static double bufferRight_Ref[len_ref];

static double bufferLeft_copy[len];
static double bufferRight_copy[len];
static double *rptrLeft_copy = bufferLeft_copy;
static double *rptrRight_copy = bufferRight_copy;

static double *rptrLeft = bufferLeft; // read ptr
static double *wptrLeft = bufferLeft; // write ptr

static double *rptrRight = bufferRight; // read ptr
static double *wptrRight = bufferRight; // write ptr

static double *rptrLeft_Ref = bufferLeft_Ref;
static double *rptrRight_Ref = bufferRight_Ref;

static double *wptrLeft_Ref = bufferLeft_Ref;
static double *wptrRight_Ref = bufferRight_Ref;

static double alpha = 1/2048;

class DelayLine {
public:
    
    DelayLine():
    y_1_L(0.0),
    y_1_R(0.0),
    y_1_L_ref(0.0),
    y_1_R_ref(0.0),
    fracDelaySamplesLeft(0.0),
    fracDelaySamplesRight(0.0),
    fracDelaySamplesLeft_Ref(0.0),
    fracDelaySamplesRight_Ref(0.0),
    crossfadeNeededL(false),
    crossfadeNeededR(false),
    t_L(-1),
    t_R(-1){};
    ~DelayLine(){};
    
    
    void setDelayL(double samples);
    void setDelayR(double samples);
    
    double delayLineL(double input);
    double delayLineR(double input);
    
    void setDelay_Ref_L(double samples);
    void setDelay_Ref_R(double samples);
    
    double delayLine_Ref_L(double input);
    double delayLine_Ref_R(double input);
    
    void suspend(); // flush buffers
    
private:

    int t_L;
    int t_R;
    double y_1_L;
    double y_1_R;
    double y_1_L_ref;
    double y_1_R_ref;
    double fracDelaySamplesLeft;
    double fracDelaySamplesRight;
    
    double fracDelaySamplesLeft_Ref;
    double fracDelaySamplesRight_Ref;
    bool crossfadeNeededL;
    bool crossfadeNeededR;
};
#endif /* DelayLine_hpp */
