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

#pragma once

#include <math.h>
#include <tgmath.h>
//#include <vector>

class DelayLine {
public:
    
    DelayLine():
    fracDelaySamples{0.0, 0.0}
    {initialize();};
    
    ~DelayLine(){
        
        for(int i = 0; i < 2; ++i)
        {
            delete delayBuffer[i];
            delete delayMultitapBuffer[i];
        }
    
    };
    
    void initialize(){
        
        delayBufferLength_ = 8*mSampleRate;//3835;//(int)(30/0.345)*44.1 + 1;
        
        for(int i = 0; i < 2; ++i)
        {
            delayBuffer[i] = new double[delayBufferLength_];
        
            rptr[i] = delayBuffer[i]; // read ptr
            wptr[i] = delayBuffer[i]; // write ptr
        
            delayMultitapBuffer[i] = new double[delayBufferLength_];
            
            rptrMul[i] = delayMultitapBuffer[i]; // read ptr
            wptrMul[i] = delayMultitapBuffer[i]; // write ptr
            
            delaySyncBuffer[i] = new double[delayBufferLength_];
            
            rptrSyn[i] = delaySyncBuffer[i]; // read ptr
            wptrSyn[i] = delaySyncBuffer[i]; // write ptr
        }
        
    }
    
    void setDelay(double samples, int channel);
    
    double delayLine(double input, int channel);
    
    double delayLineRep(double input, double tempoDelay, double feedback, int channel);
    
    double delayLineRepSync(double input, double tempoDelay, double feedback, int channel);
    
    double hermiteInterpolation(double* pointer, double* buffer, int bufferLenght, double frac);
    
    inline void setSampleRate(double sampleRate){ mSampleRate = sampleRate;}
    
    // flush buffers
    inline void suspend(){
        for(int i = 0; i < 2; ++i)
        {
            memset(delayBuffer[i], 0, delayBufferLength_*sizeof(double));
            memset(delayMultitapBuffer[i], 0, delayBufferLength_*sizeof(double));
            memset(delaySyncBuffer[i], 0, delayBufferLength_*sizeof(double));
        }
    }
    
private:
    
    double mSampleRate;
    double fracDelaySamples[2];
    
    int delayBufferLength_;
    
    double *delayBuffer[2];
    double *delayMultitapBuffer[2];
    double *delaySyncBuffer[2];
    
    double *rptr[2]; // read ptr
    double *wptr[2]; // write ptr
    
    double *rptrMul[2]; // read ptr
    double *wptrMul[2]; // write ptr
    
    double *rptrSyn[2]; // read ptr
    double *wptrSyn[2]; // write ptr

};