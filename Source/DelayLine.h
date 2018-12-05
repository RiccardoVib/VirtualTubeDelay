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
    y_1_L(0.0),
    y_1_R(0.0),
    y_1_L_ref(0.0),
    y_1_R_ref(0.0),
    fracDelaySamplesLeft(0.0),
    fracDelaySamplesRight(0.0),
    fracDelaySamplesLeft_Ref(0.0),
    fracDelaySamplesRight_Ref(0.0){initialize();};
    
    ~DelayLine(){
    
        delete delayBufferLeft_;
        delete delayBufferRight_;
        
        delete delayBufferLeftRef_;
        delete delayBufferRightRef_;
        
        //delete rptrLeft; // read ptr
        //delete wptrLeft; // write ptr
        
        //delete rptrRight; // read ptr
        //delete wptrRight; // write ptr
        
        //delete rptrLeft_Ref;
        //delete rptrRight_Ref;
        
        //delete wptrLeft_Ref;
        //delete wptrRight_Ref;
    
    };
    
    void setDelay_L(double samples);
    void setDelay_R(double samples);
    
    double delayLine_L(double input);
    double delayLine_R(double input);
    
    double delayLineRep_L(double input, double tempoDelay, double feedback);
    double delayLineRep_R(double input, double tempoDelay, double feedback);
    
    void setDelay_Ref_L(double samples);
    void setDelay_Ref_R(double samples);
    
    double delayLine_Ref_L(double input);
    double delayLine_Ref_R(double input);
    
    double delayLineRep_Ref_L(double input, double tempoDelay, double feedback);
    double delayLineRep_Ref_R(double input, double tempoDelay, double feedback);
    
    void setSampleRate(double sampleRate){ mSampleRate = sampleRate;}
    
    void suspend(); // flush buffers
    
    
    inline double hermiteInterpolation(double* pointer, double x, double* buffer, int bufferLenght, double frac){
    
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
    
        return y = ((c3*x+c2)*x+c1)*frac+c0;
    
    }

    void initialize(){
        
        delayBufferLength_ = 6*mSampleRate;//3835;//(int)(30/0.345)*44.1 + 1;
        delayBufferLengthRef_ = 6*mSampleRate;//5114;//(int)(40/0.345)*44.1 + 1;
        
        delayBufferLeft_ = new double[delayBufferLength_];
        delayBufferRight_ = new double[delayBufferLength_];
        
        delayBufferLeftRef_ = new double[delayBufferLengthRef_];
        delayBufferRightRef_ = new double[delayBufferLengthRef_];
        
        rptrLeft = delayBufferLeft_; // read ptr
        wptrLeft = delayBufferLeft_; // write ptr
        
        rptrRight = delayBufferRight_; // read ptr
        wptrRight = delayBufferRight_; // write ptr
        
        rptrLeft_Ref = delayBufferLeftRef_;
        rptrRight_Ref = delayBufferRightRef_;
        
        wptrLeft_Ref = delayBufferLeftRef_;
        wptrRight_Ref = delayBufferRightRef_;
        
    }
    
private:
    
    double mSampleRate;
    double y_1_L;
    double y_1_R;
    double y_1_L_ref;
    double y_1_R_ref;
    double fracDelaySamplesLeft;
    double fracDelaySamplesRight;
    double fracDelaySamplesLeft_Ref;
    double fracDelaySamplesRight_Ref;
    
    int delayBufferLength_;
    int delayBufferLengthRef_;
    
    double *delayBufferLeft_;
    double *delayBufferRight_;
    
    double *delayBufferLeftRef_;
    double *delayBufferRightRef_;
    
    double *rptrLeft; // read ptr
    double *wptrLeft; // write ptr
    
    double *rptrRight; // read ptr
    double *wptrRight; // write ptr
    
    double *rptrLeft_Ref;
    double *rptrRight_Ref;
    
    double *wptrLeft_Ref;
    double *wptrRight_Ref;


};
#endif /* DelayLine_hpp */
