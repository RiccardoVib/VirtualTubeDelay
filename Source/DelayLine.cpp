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
