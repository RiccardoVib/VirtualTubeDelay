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
    //while (wptrLeft - bufferLeft >= len) { wptrLeft -= len; }
    while (rptrLeft < delayBufferLeft_) { rptrLeft += delayBufferLength_; }
    
    fracDelaySamplesLeft = samples - (long)samples;
}

void DelayLine::setDelayR(double samples){
    
    rptrRight = wptrRight - (long)samples;
    //while (wptrRight - bufferRight >= len) { wptrRight -= len; }
    while (rptrRight < delayBufferRight_) { rptrRight += delayBufferLength_; }
    
    fracDelaySamplesRight = samples - (long)samples;
}


void DelayLine::setDelay_Ref_L(double samples){
    
    rptrLeft_Ref = wptrLeft_Ref - (long)samples;
    //while (wptrLeft_Ref - bufferLeft >= len) { wptrLeft_Ref -= len; }
    while (rptrLeft_Ref < delayBufferLeftRef_) { rptrLeft_Ref += delayBufferLengthRef_; }
    
    fracDelaySamplesLeft_Ref = samples - (long)samples;
}

void DelayLine::setDelay_Ref_R(double samples){
    
    rptrRight_Ref = wptrRight_Ref - (long)samples;
    //while (wptrRight_Ref - bufferRight >= len) { wptrRight_Ref -= len; }
    while (rptrRight_Ref < delayBufferRightRef_) { rptrRight_Ref += delayBufferLengthRef_; }
    
    fracDelaySamplesRight_Ref = samples - (long)samples;
}


void suspend(){

   // memset(delayBufferLeft_, 0, delayBufferLength_*sizeof(double));
   // memset(delayBufferRight_, 0, delayBufferLength_*sizeof(double));
}


double DelayLine::delayLineL(double x)
{
    
    double y;
    
    /*  y = *rptrLeft++; //better first read
     *wptrLeft++ = x;
     if (rptrLeft - bufferLeft >= len) { rptrLeft -= len; }
     if (wptrLeft - bufferLeft >= len) { wptrLeft -= len; }*/
    
    double *rpi = (rptrLeft+1);
    if (rpi - delayBufferLeft_ >= delayBufferLength_) { rpi -= delayBufferLength_; }
    
    /*double *z1 = (rptrLeft-1);
    double *z2 = (rptrLeft-2);
    if(z1 < bufferLeft) { z1 += len; }
    if(z2 < bufferLeft) { z2 += len; }
    
    double a = pow(fracDelaySamplesLeft,3)/6;
    double a0 = (pow(1 + fracDelaySamplesLeft, 3) - 4*pow(fracDelaySamplesLeft,3))/6;
    double a1 = (pow(2 - fracDelaySamplesLeft, 3) - 4*pow(1 - fracDelaySamplesLeft, 3))/6;
    double a2 = pow(1 - fracDelaySamplesLeft,3)/6;*/
    
    //y = sqrt(0.5f * (1.0f + t_L)) * (1 - fracDelaySamplesLeft) * *rptrLeft + fracDelaySamplesLeft * *(rpi) - y_1_L * (1 - fracDelaySamplesLeft);
    y = (1 - fracDelaySamplesLeft) * *rptrLeft + fracDelaySamplesLeft * *(rpi) - y_1_L * (1 - fracDelaySamplesLeft);

    //y = *rpi * a + *rptrLeft * a0 + *z1 * a1 + *z2 * a2;
    
    y_1_L = y;
    rptrLeft += 1;
    
    *wptrLeft++ = x;
    
    if (rptrLeft - delayBufferLeft_ >= delayBufferLength_) { rptrLeft -= delayBufferLength_; }
    if (wptrLeft - delayBufferLeft_ >= delayBufferLength_) { wptrLeft -= delayBufferLength_; }
    
    return y;
}

double DelayLine::delayLineR(double x)
{
    
    double y;
    
    double *rpi = (rptrRight+1);
    if (rpi - delayBufferRight_ >= delayBufferLength_) { rpi -= delayBufferLength_; }
    
    y = (1 - fracDelaySamplesRight) * *rptrRight + fracDelaySamplesRight * *(rpi) - y_1_R * (1 - fracDelaySamplesRight);
    y_1_R = y;
    rptrRight += 1;

    *wptrRight++ = x;
    
    if (rptrRight - delayBufferRight_ >= delayBufferLength_) { rptrRight -= delayBufferLength_; }
    if (wptrRight - delayBufferRight_ >= delayBufferLength_) { wptrRight -= delayBufferLength_; }
    
    return y;
}

double DelayLine::delayLine_Ref_L(double x)
{
    
    double y;
    
    *wptrLeft_Ref++ = x;
    
    double *rpi = (rptrLeft_Ref+1);
    if (rpi - delayBufferLeftRef_ >= delayBufferLengthRef_) { rpi -= delayBufferLengthRef_; }
    
    y = (1 - fracDelaySamplesLeft_Ref) * *rptrLeft_Ref + fracDelaySamplesLeft_Ref * *(rpi) - y_1_L_ref * (1 - fracDelaySamplesLeft_Ref);
    
    y_1_L_ref = y;
    rptrLeft_Ref += 1;
    
    if (rptrLeft_Ref - delayBufferLeftRef_ >= delayBufferLengthRef_) { rptrLeft_Ref -= delayBufferLengthRef_; }
    if (wptrLeft_Ref - delayBufferLeftRef_ >= delayBufferLengthRef_) { wptrLeft_Ref -= delayBufferLengthRef_; }
    
    return y;

}

double DelayLine::delayLine_Ref_R(double x)
{
    
    double y;
    
    double *rpi = (rptrRight_Ref+1);
    if (rpi - delayBufferRightRef_ >= delayBufferLengthRef_) { rpi -= delayBufferLengthRef_; }
    
    y = (1 - fracDelaySamplesRight_Ref) * *rptrRight_Ref + fracDelaySamplesRight_Ref * *(rpi) - y_1_R_ref * (1 - fracDelaySamplesRight_Ref);
    
    y_1_R_ref = y;
    rptrRight_Ref += 1;
    
    *wptrRight_Ref++ = x;
    
    if (rptrRight_Ref - delayBufferRightRef_ >= delayBufferLengthRef_) { rptrRight_Ref -= delayBufferLengthRef_; }
    if (wptrRight_Ref - delayBufferRightRef_ >= delayBufferLengthRef_) { wptrRight_Ref -= delayBufferLengthRef_; }
    
    return y;
}



double DelayLine::delayLine_Vibrato_L(double x, double samples){
    
    double y;
    
    rptrLeft = wptrLeft - (long)samples + delayBufferLength_;// - 3;
    while (rptrLeft < delayBufferLeft_) { rptrLeft += delayBufferLength_; }
    
    double fraction = samples - (long)samples;
    
    double *nextSample = (rptrLeft + 1);
    
    if (nextSample - delayBufferLeft_ >= delayBufferLength_) { nextSample -= delayBufferLength_; }

    
    y = fraction * *nextSample + (1.0f-fraction) * *rptrLeft;
    
    
    *wptrLeft++ = x;
    
    rptrLeft++;
    
    if (wptrLeft - delayBufferLeft_ >= delayBufferLength_) { wptrLeft -= delayBufferLength_; }
    if (rptrLeft - delayBufferLeft_ >= delayBufferLength_) { rptrLeft -= delayBufferLength_; }

    
    
    return y;
    
}