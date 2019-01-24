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


double DelayLine::hermiteInterpolation(double* pointer, double* buffer, int bufferLenght, double frac){
    
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

void DelayLine::setDelay(double samples, int channel)
{
    
    rptr[channel] = wptr[channel] - (long)samples;
    while (rptr[channel] < delayBuffer[channel]) { rptr[channel] += delayBufferLength_; }
    
    fracDelaySamples[channel] = samples - (long)samples;
    
}


double DelayLine::delayLine(double x, int channel)
{
    
    double y;
    y = hermiteInterpolation(rptr[channel], delayBuffer[channel], delayBufferLength_, fracDelaySamples[channel]);
    
    rptr[channel] += 1;
    
    *wptr[channel]++ = x;
    
    if (rptr[channel] - delayBuffer[channel] >= delayBufferLength_) { rptr[channel] -= delayBufferLength_; }
    if (wptr[channel] - delayBuffer[channel] >= delayBufferLength_) { wptr[channel] -= delayBufferLength_; }
    
    return y;
}

double DelayLine::delayLineRep(double x, double tempoDelay, double feedback, int channel)
{
    
    rptrMul[channel] = wptrMul[channel] - (long)tempoDelay;
    while (rptrMul[channel] < delayMultitapBuffer[channel]) { rptrMul[channel] += delayBufferLength_; }
    
    double y = 0.0;
    
    y = *rptrMul[channel] + hermiteInterpolation(rptr[channel], delayBuffer[channel], delayBufferLength_, fracDelaySamples[channel]);
    
    //H(z) = 1/(1 - az^-D)
    //y(n) = ay(n - D) + x(n)

    rptrMul[channel] += 1;
    
    *wptrMul[channel]++ = feedback * y;
    
    if (rptrMul[channel] - delayMultitapBuffer[channel] >= delayBufferLength_) { rptrMul[channel] -= delayBufferLength_; }
    if (wptrMul[channel] - delayMultitapBuffer[channel] >= delayBufferLength_) { wptrMul[channel] -= delayBufferLength_; }
    
    rptr[channel] += 1;
    
    *wptr[channel]++ = x;
    
    if (rptr[channel] - delayBuffer[channel] >= delayBufferLength_) { rptr[channel] -= delayBufferLength_; }
    if (wptr[channel] - delayBuffer[channel] >= delayBufferLength_) { wptr[channel] -= delayBufferLength_; }
    
    return y;
}

//TODO: to join with previous method
double DelayLine::delayLineRepSync(double x, double tempoDelay, double feedback, int channel)
{
    
    rptrSyn[channel] = wptrSyn[channel] - (long)tempoDelay;
    while (rptrSyn[channel] < delaySyncBuffer[channel]) { rptrSyn[channel] += delayBufferLength_; }
    
    double y = 0.0;
    
    y = *rptrSyn[channel] + hermiteInterpolation(rptr[channel], delayBuffer[channel], delayBufferLength_, fracDelaySamples[channel]);
    
    //H(z) = 1/(1 - az^-D)
    //y(n) = ay(n - D) + x(n)
    
    rptrSyn[channel] += 1;
    
    *wptrSyn[channel]++ = feedback * y;
    
    if (rptrSyn[channel] - delaySyncBuffer[channel] >= delayBufferLength_) { rptrSyn[channel] -= delayBufferLength_; }
    if (wptrSyn[channel] - delaySyncBuffer[channel] >= delayBufferLength_) { wptrSyn[channel] -= delayBufferLength_; }
    
    rptr[channel] += 1;
    
    *wptr[channel]++ = x;
    
    if (rptr[channel] - delayBuffer[channel] >= delayBufferLength_) { rptr[channel] -= delayBufferLength_; }
    if (wptr[channel] - delayBuffer[channel] >= delayBufferLength_) { wptr[channel] -= delayBufferLength_; }
    
    return y;
}
