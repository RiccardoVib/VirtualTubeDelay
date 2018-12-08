//
//  DelayLine.cpp
//  VirtualTubeDelay
//
//  Created by Riccardo Simionato on 03/10/18.
//
//

#include "DelayLine.h"
#include <iostream>
#include <math.h>

void DelayLine::setDelay_L(double samples){
    
    rptrLeft = wptrLeft - (long)samples;
    while (rptrLeft < delayBufferLeft_) { rptrLeft += delayBufferLength_; }
    
    fracDelaySamplesLeft = samples - (long)samples;
    
}

void DelayLine::setDelay_R(double samples){
    
    rptrRight = wptrRight - (long)samples;
    while (rptrRight < delayBufferRight_) { rptrRight += delayBufferLength_; }
    
    fracDelaySamplesRight = samples - (long)samples;

}

void DelayLine::setDelay_Ref_L(double samples){
    
    rptrLeft_Ref = wptrLeft_Ref - (long)samples;
    while (rptrLeft_Ref < delayBufferLeftRef_) { rptrLeft_Ref += delayBufferLengthRef_; }
    
    fracDelaySamplesLeft_Ref = samples - (long)samples;
}

void DelayLine::setDelay_Ref_R(double samples){
    
    rptrRight_Ref = wptrRight_Ref - (long)samples;
    while (rptrRight_Ref < delayBufferRightRef_) { rptrRight_Ref += delayBufferLengthRef_; }

    fracDelaySamplesRight_Ref = samples - (long)samples;
}


double DelayLine::delayLine_L(double x)
{
    
    double y;
    y = hermiteInterpolation(rptrLeft, delayBufferLeft_, delayBufferLength_, fracDelaySamplesLeft);
    
    rptrLeft += 1;
    
    *wptrLeft++ = x;
    
    if (rptrLeft - delayBufferLeft_ >= delayBufferLength_) { rptrLeft -= delayBufferLength_; }
    if (wptrLeft - delayBufferLeft_ >= delayBufferLength_) { wptrLeft -= delayBufferLength_; }
    
    return y;
}

double DelayLine::delayLine_R(double x)
{
    
    double y;
    
    y = hermiteInterpolation(rptrRight, delayBufferRight_, delayBufferLength_, fracDelaySamplesRight);
    
    rptrRight += 1;

    *wptrRight++ = x;
    
    if (rptrRight - delayBufferRight_ >= delayBufferLength_) { rptrRight -= delayBufferLength_; }
    if (wptrRight - delayBufferRight_ >= delayBufferLength_) { wptrRight -= delayBufferLength_; }
    
    return y;
}



double DelayLine::delayLine_Ref_L(double x)
{
    
    double y;
    
    y = hermiteInterpolation(rptrLeft_Ref, delayBufferLeftRef_, delayBufferLengthRef_, fracDelaySamplesLeft_Ref);
    
    *wptrLeft_Ref++ = x;
    
    rptrLeft_Ref += 1;
    
    if (rptrLeft_Ref - delayBufferLeftRef_ >= delayBufferLengthRef_) { rptrLeft_Ref -= delayBufferLengthRef_; }
    if (wptrLeft_Ref - delayBufferLeftRef_ >= delayBufferLengthRef_) { wptrLeft_Ref -= delayBufferLengthRef_; }
    
    return y;

}


double DelayLine::delayLine_Ref_R(double x)
{
    
    double y;
    
    y = hermiteInterpolation(rptrRight_Ref, delayBufferRightRef_, delayBufferLengthRef_, fracDelaySamplesRight_Ref);
   
    rptrRight_Ref += 1;
    
    *wptrRight_Ref++ = x;
    
    if (rptrRight_Ref - delayBufferRightRef_ >= delayBufferLengthRef_) { rptrRight_Ref -= delayBufferLengthRef_; }
    if (wptrRight_Ref - delayBufferRightRef_ >= delayBufferLengthRef_) { wptrRight_Ref -= delayBufferLengthRef_; }
    
    return y;
}

double DelayLine::delayLineRep_L(double x, double tempoDelay, double feedback)
{
    
    double y = 0.0;
    int len = 8;
    
    y = hermiteInterpolation(rptrLeft, delayBufferLeft_, delayBufferLength_, fracDelaySamplesLeft);

    for(int i = 1; i < len; i++){
        
        double *y1 = rptrLeft - i*(int)tempoDelay;
        while(y1 < delayBufferLeft_) { y1 += delayBufferLength_; }
        
        y = y + pow(feedback,i) * *y1;
    }
    
    rptrLeft += 1;
    
    *wptrLeft++ = x;
    
    if (rptrLeft - delayBufferLeft_ >= delayBufferLength_) { rptrLeft -= delayBufferLength_; }
    if (wptrLeft - delayBufferLeft_ >= delayBufferLength_) { wptrLeft -= delayBufferLength_; }
    
    return y;
}


double DelayLine::delayLineRep_R(double x, double tempoDelay, double feedback)
{
    double y = 0.0;
    int len = 8;
    
    y = hermiteInterpolation(rptrRight, delayBufferRight_, delayBufferLength_, fracDelaySamplesLeft);

    for(int i = 1; i < len; i++){
        double *y1 = rptrRight - i*(int)tempoDelay;
        while(y1 < delayBufferRight_) { y1 += delayBufferLength_; }
        
        y = y + pow(feedback,i) * *y1;
    }
    
    rptrRight += 1;
    
    *wptrRight++ = x;
    
    if (rptrRight - delayBufferRight_ >= delayBufferLength_) { rptrRight -= delayBufferLength_; }
    if (wptrRight - delayBufferRight_ >= delayBufferLength_) { wptrRight -= delayBufferLength_; }
    
    return y;
}


double DelayLine::delayLineRep_Ref_L(double x, double tempoDelay, double feedback)
{
    double y = 0.0;
    int len = 8;
    
    y = hermiteInterpolation(rptrLeft_Ref, delayBufferLeftRef_, delayBufferLengthRef_, fracDelaySamplesLeft_Ref);

    
    for(int i = 1; i < len; i++){
        
        double *y1 = rptrLeft_Ref - i*(int)tempoDelay;
        while(y1 < delayBufferLeftRef_) { y1 += delayBufferLengthRef_; }
        
        y = y + pow(feedback,i) * *y1;
    }
    
    rptrLeft_Ref += 1;
    
    *wptrLeft_Ref++ = x;
    
    if (rptrLeft_Ref - delayBufferLeftRef_ >= delayBufferLengthRef_) { rptrLeft_Ref -= delayBufferLengthRef_; }
    if (wptrLeft_Ref - delayBufferLeftRef_ >= delayBufferLengthRef_) { wptrLeft_Ref -= delayBufferLengthRef_; }
    
    return y;
}


double DelayLine::delayLineRep_Ref_R(double x, double tempoDelay, double feedback)
{
    double y = 0.0;
    int len = 8;
    
    y = hermiteInterpolation(rptrRight_Ref, delayBufferRightRef_, delayBufferLengthRef_, fracDelaySamplesRight_Ref);

    for(int i = 1; i < len; i++){
        
        double *y1 = rptrRight_Ref - i*(int)tempoDelay;
        while(y1 < delayBufferRightRef_) { y1 += delayBufferLengthRef_; }
        
        y = y + pow(feedback,i) * *y1;
    }
    
    rptrRight_Ref += 1;
    
    *wptrRight_Ref++ = x;
    
    if (rptrRight_Ref - delayBufferRightRef_ >= delayBufferLengthRef_) { rptrRight_Ref -= delayBufferLengthRef_; }
    if (wptrRight_Ref - delayBufferRightRef_ >= delayBufferLengthRef_) { wptrRight_Ref -= delayBufferLengthRef_; }
 
    return y;
}
