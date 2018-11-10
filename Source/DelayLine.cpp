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


double DelayLine::delayLineL(double x, double tempo, bool repeated)
{
    
    double y;
    
    /*double *rpi = (rptrLeft+1);
    if (rpi - delayBufferLeft_ >= delayBufferLength_) { rpi -= delayBufferLength_; }*/
    
    // Hermite polynomial interpolation
    // 4-point, 3rd-order Hermite (x-form)
    static double c0, c1, c2, c3;
    
    double *y_1 = (rptrLeft - 1);
    double *y_2 = (rptrLeft - 2);
    double *y_3 = (rptrLeft - 3);
    
    if (y_1 < delayBufferLeft_) { y_1 += delayBufferLength_; }
    if (y_2 < delayBufferLeft_) { y_2 += delayBufferLength_; }
    if (y_3 < delayBufferLeft_) { y_3 += delayBufferLength_; }
    
    c0 = *y_1;
    c1 = (1.0/2.0)*(*y_2 - *rptrLeft);
    c2 = (*rptrLeft - (5.0/2.0)* *y_1) + (2.0* *y_2 - (1.0/2.0)* *y_3);
    c3 = (1.0/2.0)*(*y_3- *rptrLeft) + (3.0/2.0)*(*y_1 - *y_2);
    y = ((c3*x+c2)*x+c1)*fracDelaySamplesLeft+c0;
    //
    
    //y = sqrt(0.5f * (1.0f + t_L)) * (1 - fracDelaySamplesLeft) * *rptrLeft + fracDelaySamplesLeft * *(rpi) - y_1_L * (1 - fracDelaySamplesLeft);
    
    //y = (1 - fracDelaySamplesLeft) * *rptrLeft + fracDelaySamplesLeft * *(rpi) - y_1_L * (1 - fracDelaySamplesLeft);
    
    //y_1_L = y;
    
    rptrLeft += 1;
    
    if(repeated){
        
        double *nextWptrLeft = wptrLeft + (int)tempo;
        
        if (nextWptrLeft - delayBufferLeft_ >= delayBufferLength_) { nextWptrLeft -= delayBufferLength_; }
        *nextWptrLeft += x;
        
        *wptrLeft += 1;
        //*wptrLeft++ = x;
        
    }else{
        *wptrLeft++ = x;
    }
    
    if (rptrLeft - delayBufferLeft_ >= delayBufferLength_) { rptrLeft -= delayBufferLength_; }
    if (wptrLeft - delayBufferLeft_ >= delayBufferLength_) { wptrLeft -= delayBufferLength_; }
    
    return y;
}

double DelayLine::delayLineR(double x, double tempo, bool repeated)
{
    
    double y;
    
    /*
    double *rpi = (rptrRight+1);
    if (rpi - delayBufferRight_ >= delayBufferLength_) { rpi -= delayBufferLength_; }
    
    y = (1 - fracDelaySamplesRight) * *rptrRight + fracDelaySamplesRight * *(rpi) - y_1_R * (1 - fracDelaySamplesRight);
    y_1_R = y;
    */
    
    // Hermite polynomial interpolation
    // 4-point, 3rd-order Hermite (x-form)
    static double c0, c1, c2, c3;
    
    double *y_1 = (rptrRight - 1);
    double *y_2 = (rptrRight - 2);
    double *y_3 = (rptrRight - 3);
    
    if (y_1 < delayBufferRight_) { y_1 += delayBufferLength_; }
    if (y_2 < delayBufferRight_) { y_2 += delayBufferLength_; }
    if (y_3 < delayBufferRight_) { y_3 += delayBufferLength_; }
    
    c0 = *y_1;
    c1 = (1.0/2.0)*(*y_2 - *rptrRight);
    c2 = (*rptrRight - (5.0/2.0)* *y_1) + (2.0* *y_2 - (1.0/2.0)* *y_3);
    c3 = (1.0/2.0)*(*y_3- *rptrRight) + (3.0/2.0)*(*y_1 - *y_2);
    y = ((c3*x+c2)*x+c1)*fracDelaySamplesRight+c0;
    //
    
    rptrRight += 1;

    if(repeated){
        
        double *nextWptrRight = wptrRight + (int)tempo;
        
        if (nextWptrRight - delayBufferRight_ >= delayBufferLength_) { nextWptrRight -= delayBufferLength_; }
        *nextWptrRight += x;
        
        *wptrRight += 1;
        //*wptrRight++ = x;
        
    }else{
        
        *wptrRight++ = x;
    }
    
    if (rptrRight - delayBufferRight_ >= delayBufferLength_) { rptrRight -= delayBufferLength_; }
    if (wptrRight - delayBufferRight_ >= delayBufferLength_) { wptrRight -= delayBufferLength_; }
    
    return y;
}

double DelayLine::delayLine_Ref_L(double x, double tempo, bool repeated)
{
    
    double y;
    
    /*double *rpi = (rptrLeft_Ref+1);
    if (rpi - delayBufferLeftRef_ >= delayBufferLengthRef_) { rpi -= delayBufferLengthRef_; }
    
    y = (1 - fracDelaySamplesLeft_Ref) * *rptrLeft_Ref + fracDelaySamplesLeft_Ref * *(rpi) - y_1_L_ref * (1 - fracDelaySamplesLeft_Ref);
    
    y_1_L_ref = y;*/
    
    
    // Hermite polynomial interpolation
    // 4-point, 3rd-order Hermite (x-form)
    static double c0, c1, c2, c3;
    
    double *y_1 = (rptrLeft_Ref - 1);
    double *y_2 = (rptrLeft_Ref - 2);
    double *y_3 = (rptrLeft_Ref - 3);
    
    if (y_1 < delayBufferLeftRef_) { y_1 += delayBufferLengthRef_; }
    if (y_2 < delayBufferLeftRef_) { y_2 += delayBufferLengthRef_; }
    if (y_3 < delayBufferLeftRef_) { y_3 += delayBufferLengthRef_; }
    
    c0 = *y_1;
    c1 = (1.0/2.0)*(*y_2 - *rptrLeft_Ref);
    c2 = (*rptrLeft_Ref - (5.0/2.0)* *y_1) + (2.0* *y_2 - (1.0/2.0)* *y_3);
    c3 = (1.0/2.0)*(*y_3- *rptrLeft_Ref) + (3.0/2.0)*(*y_1 - *y_2);
    y = ((c3*x+c2)*x+c1)*fracDelaySamplesLeft_Ref+c0;
    //
    
    if(repeated){
        
        double *nextWptrLeft_Ref = wptrLeft_Ref + (int)tempo;
        
        if (nextWptrLeft_Ref - delayBufferLeftRef_ >= delayBufferLengthRef_) { nextWptrLeft_Ref -= delayBufferLengthRef_; }
        *nextWptrLeft_Ref += x;
        
        *wptrLeft_Ref++ = x;

    }else{
        
        *wptrLeft_Ref++ = x;
    }
    
    rptrLeft_Ref += 1;
    
    if (rptrLeft_Ref - delayBufferLeftRef_ >= delayBufferLengthRef_) { rptrLeft_Ref -= delayBufferLengthRef_; }
    if (wptrLeft_Ref - delayBufferLeftRef_ >= delayBufferLengthRef_) { wptrLeft_Ref -= delayBufferLengthRef_; }
    
    return y;

}

double DelayLine::delayLine_Ref_R(double x, double tempo, bool repeated)
{
    
    double y;
    
    /*double *rpi = (rptrRight_Ref+1);
    if (rpi - delayBufferRightRef_ >= delayBufferLengthRef_) { rpi -= delayBufferLengthRef_; }
    
    y = (1 - fracDelaySamplesRight_Ref) * *rptrRight_Ref + fracDelaySamplesRight_Ref * *(rpi) - y_1_R_ref * (1 - fracDelaySamplesRight_Ref);
    
    y_1_R_ref = y;*/

    
    // Hermite polynomial interpolation
    // 4-point, 3rd-order Hermite (x-form)
    static double c0, c1, c2, c3;
    
    double *y_1 = (rptrRight_Ref - 1);
    double *y_2 = (rptrRight_Ref - 2);
    double *y_3 = (rptrRight_Ref - 3);
    
    if (y_1 < delayBufferRightRef_) { y_1 += delayBufferLengthRef_; }
    if (y_2 < delayBufferRightRef_) { y_2 += delayBufferLengthRef_; }
    if (y_3 < delayBufferRightRef_) { y_3 += delayBufferLengthRef_; }
    
    c0 = *y_1;
    c1 = (1.0/2.0)*(*y_2 - *rptrRight_Ref);
    c2 = (*rptrRight_Ref - (5.0/2.0)* *y_1) + (2.0* *y_2 - (1.0/2.0)* *y_3);
    c3 = (1.0/2.0)*(*y_3- *rptrRight_Ref) + (3.0/2.0)*(*y_1 - *y_2);
    y = ((c3*x+c2)*x+c1)*fracDelaySamplesRight_Ref+c0;
    //
    
    
    rptrRight_Ref += 1;
    
    if(repeated){
        
        double *nextWptrRight_Ref = wptrRight_Ref + (int)tempo;
        
        if (nextWptrRight_Ref - delayBufferRightRef_ >= delayBufferLengthRef_) { nextWptrRight_Ref -= delayBufferLengthRef_; }
        *nextWptrRight_Ref += x;
        
        *wptrRight_Ref++ = x;
        
    }else{
        
        *wptrRight_Ref++ = x;
    }
    
    if (rptrRight_Ref - delayBufferRightRef_ >= delayBufferLengthRef_) { rptrRight_Ref -= delayBufferLengthRef_; }
    if (wptrRight_Ref - delayBufferRightRef_ >= delayBufferLengthRef_) { wptrRight_Ref -= delayBufferLengthRef_; }
    
    return y;
}