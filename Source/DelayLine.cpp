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

void DelayLine::setDelayL(double samples){
    
    rptrLeft = wptrLeft - (long)samples;
    while (rptrLeft < delayBufferLeft_) { rptrLeft += delayBufferLength_; }
    
    fracDelaySamplesLeft = samples - (long)samples;
    
}

void DelayLine::setDelayR(double samples){
    
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


void DelayLine::suspend(){

    memset(delayBufferLeft_, 0, delayBufferLength_*sizeof(double));
    memset(delayBufferRight_, 0, delayBufferLength_*sizeof(double));
}


double DelayLine::delayLineL(double x)
{
    
    double y;
    y = hermiteInterpolation(rptrLeft, x, delayBufferLeft_, delayBufferLength_, fracDelaySamplesLeft);
    
    rptrLeft += 1;
    
    *wptrLeft++ = x;
    
    if (rptrLeft - delayBufferLeft_ >= delayBufferLength_) { rptrLeft -= delayBufferLength_; }
    if (wptrLeft - delayBufferLeft_ >= delayBufferLength_) { wptrLeft -= delayBufferLength_; }
    
    return y;
}

double DelayLine::delayLineR(double x)
{
    
    double y;
    
    y = hermiteInterpolation(rptrRight, x, delayBufferRight_, delayBufferLength_, fracDelaySamplesRight);
    
    rptrRight += 1;

    *wptrRight++ = x;
    
    if (rptrRight - delayBufferRight_ >= delayBufferLength_) { rptrRight -= delayBufferLength_; }
    if (wptrRight - delayBufferRight_ >= delayBufferLength_) { wptrRight -= delayBufferLength_; }
    
    return y;
}



double DelayLine::delayLine_Ref_L(double x)
{
    
    double y;
    
    y = hermiteInterpolation(rptrLeft_Ref, x, delayBufferLeftRef_, delayBufferLengthRef_, fracDelaySamplesLeft_Ref);
    
    *wptrLeft_Ref++ = x;
    
    rptrLeft_Ref += 1;
    
    if (rptrLeft_Ref - delayBufferLeftRef_ >= delayBufferLengthRef_) { rptrLeft_Ref -= delayBufferLengthRef_; }
    if (wptrLeft_Ref - delayBufferLeftRef_ >= delayBufferLengthRef_) { wptrLeft_Ref -= delayBufferLengthRef_; }
    
    return y;

}


double DelayLine::delayLine_Ref_R(double x)
{
    
    double y;
    
    y = hermiteInterpolation(rptrRight_Ref, x, delayBufferRightRef_, delayBufferLengthRef_, fracDelaySamplesRight_Ref);
   
    rptrRight_Ref += 1;
    
    *wptrRight_Ref++ = x;
    
    if (rptrRight_Ref - delayBufferRightRef_ >= delayBufferLengthRef_) { rptrRight_Ref -= delayBufferLengthRef_; }
    if (wptrRight_Ref - delayBufferRightRef_ >= delayBufferLengthRef_) { wptrRight_Ref -= delayBufferLengthRef_; }
    
    return y;
}

double DelayLine::delayLineRepL(double x, double tempo, int tempo_, double feedback)
{
    
    double y = 0.0;
    int len = 4*tempo_;
    
    for(int i = 0; i < len; i++){
        
        double *y1 = rptrLeft - (i+1)*(int)tempo;
        while(y1 < delayBufferLeft_) { y1 += delayBufferLength_; }
        
        y = y + pow(feedback,i+1) * *y1;
    }
    
    rptrLeft += 1;
    
    //double y0 = *rptrLeft++;
    
    *wptrLeft++ = x;
    
    if (rptrLeft - delayBufferLeft_ >= delayBufferLength_) { rptrLeft -= delayBufferLength_; }
    if (wptrLeft - delayBufferLeft_ >= delayBufferLength_) { wptrLeft -= delayBufferLength_; }
    
    //y = y0 + y;
    
    return y;
}


double DelayLine::delayLineRepR(double x, double tempo, int tempo_, double feedback)
{
    double y = 0.0;
    int len = 4*tempo_;
    
    for(int i = 0; i < len; i++){
        double *y1 = rptrRight - (i+1)*(int)tempo;
        while(y1 < delayBufferRight_) { y1 += delayBufferLength_; }
        
        y = y + pow(feedback,i+1) * *y1;
    }
    
    rptrRight += 1;
    
    //double y0 = *rptrRight++;
    
    *wptrRight++ = x;
    
    if (rptrRight - delayBufferRight_ >= delayBufferLength_) { rptrRight -= delayBufferLength_; }
    if (wptrRight - delayBufferRight_ >= delayBufferLength_) { wptrRight -= delayBufferLength_; }
    
    //y = y0 + y;
    
    return y;
}


double DelayLine::delayLineRep_Ref_L(double x, double tempo, int tempo_, double feedback)
{
    double y = 0.0;
    int len = 4*tempo_;
    
    for(int i = 0; i < len; i++){
        
        double *y1 = rptrLeft_Ref - (i+1)*(int)tempo;
        while(y1 < delayBufferLeftRef_) { y1 += delayBufferLengthRef_; }
        
        y = y + pow(feedback,i+1) * *y1;
    }
    
    rptrLeft_Ref += 1;
    //double y0 = *rptrLeft_Ref++;
    
    *wptrLeft_Ref++ = x;
    
    if (rptrLeft_Ref - delayBufferLeftRef_ >= delayBufferLengthRef_) { rptrLeft_Ref -= delayBufferLengthRef_; }
    if (wptrLeft_Ref - delayBufferLeftRef_ >= delayBufferLengthRef_) { wptrLeft_Ref -= delayBufferLengthRef_; }
    
    //y = y0 + y;
    
    return y;
}


double DelayLine::delayLineRep_Ref_R(double x, double tempo, int tempo_, double feedback)
{
    double y = 0.0;
    int len = 4*tempo_;
    
    for(int i = 0; i < len; i++){
        
        double *y1 = rptrRight_Ref - (i+1)*(int)tempo;
        while(y1 < delayBufferRightRef_) { y1 += delayBufferLengthRef_; }
        
        y = y + pow(feedback,i+1) * *y1;
    }
    
    rptrRight_Ref += 1;
    
    //double y0 = *rptrRight_Ref++;
    
    *wptrRight_Ref++ = x;
    
    if (rptrRight_Ref - delayBufferRightRef_ >= delayBufferLengthRef_) { rptrRight_Ref -= delayBufferLengthRef_; }
    if (wptrRight_Ref - delayBufferRightRef_ >= delayBufferLengthRef_) { wptrRight_Ref -= delayBufferLengthRef_; }
    
    //y = y0 + y;
    
    return y;
}
