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
#include <vector>

class DelayLine {
public:
    
    DelayLine():
    fracDelaySamples{0.0, 0.0}
    {initialize();};
    
    ~DelayLine(){
        
        for(int i = 0; i < 2; ++i)
        {
            delete delayBuffer[i];
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
        }
        
    }
    
    void setDelay(double samples, int channel);
    
    double delayLine(double input, int channel);
    
    double delayLineRep(double input, double tempoDelay, double feedback, int channel);
    
    void setSampleRate(double sampleRate){ mSampleRate = sampleRate;}
    
    // flush buffers
    inline void suspend(){
        for(int i = 0; i < 2; ++i)
        {
            memset(delayBuffer[i], 0, delayBufferLength_*sizeof(double));
        }
    }
    
    inline double hermiteInterpolation(double* pointer, double* buffer, int bufferLenght, double frac){
    
        // Hermite polynomial interpolation
        // 4-point, 3rd-order Hermite (x-form)
        static double c0, c1, c2, c3;
        double y;
        double *y_1 = (pointer - 1);
        double *y_2 = (pointer - 2);
        double *y_3 = (pointer - 3);
    
        if (y_1 < buffer) { y_1 += bufferLenght; }
        if (y_2 < buffer) { y_2 += bufferLenght; }
        if (y_3 < buffer) { y_3 += bufferLenght; }
    
        c0 = *y_1;
        c1 = (1.0/2.0)*(*y_2 - *pointer);
        c2 = (*pointer - (5.0/2.0)* *y_1) + (2.0* *y_2 - (1.0/2.0)* *y_3);
        c3 = (1.0/2.0)*(*y_3- *pointer) + (3.0/2.0)*(*y_1 - *y_2);
    
        return y = ((c3*frac+c2)*frac+c1)*frac+c0;
    
    }
    
private:
    
    double mSampleRate;
    double fracDelaySamples[2];
    
    int delayBufferLength_;
    
    double *delayBuffer[2];
    double *delayMultitapBuffer[2];
    
    double *rptr[2]; // read ptr
    double *wptr[2]; // write ptr
    
    double *rptrMul[2]; // read ptr
    double *wptrMul[2]; // write ptr

};
#endif /* DelayLine_hpp */
