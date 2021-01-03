#include "sonicslash_Convolve.h"

namespace sonicslash {

Convolve::Convolve()
{
    
}
    
void Convolve::setBestRatio()
{
    long maxInterpolate = windowSize / 8;
    
    if (! time)
    {
        decimation = interpolation = maxInterpolate;
        return; // don't change scale
    }

    float testScale;
    float percentError = 2.0f;
    float newScaleFactor;
    long maxDecimate = maxInterpolate;
    
    if (scaleFactor > 1.0f)
    {
        for (interpolation = maxInterpolate; percentError > 1.01f; --interpolation)
        {
            decimation = (long) ((float) interpolation / scaleFactor);
            testScale = (float) interpolation / decimation;
            
            if (testScale > scaleFactor)
                percentError = testScale / scaleFactor;
            else
                percentError = scaleFactor / testScale;
            
            if (percentError < 1.004f)
                break;
            
            if (interpolation == 1)
            {
                interpolation = maxInterpolate;
                decimation = (long) ((float) interpolation / scaleFactor);
                newScaleFactor = (float) interpolation / decimation;
                percentError = 1.0f;
            }
        }
    }
    else
    {
        for (decimation = maxDecimate; percentError > 1.01f; --decimation)
        {
            interpolation = (long) (decimation * scaleFactor);
            testScale = (float) interpolation / decimation;
            
            if (testScale > scaleFactor)
                percentError = testScale / scaleFactor;
            else
                percentError = scaleFactor / testScale;
            
            if (percentError < 1.004f)
                break;
            
            if (decimation == 1)
            {
                decimation = maxDecimate;
                interpolation = (long) (decimation * scaleFactor);
                newScaleFactor = (float) interpolation / decimation;
                percentError = 1.0f;
            }
        }
    }
    
    scaleFactor = (float) interpolation / decimation;
}

void Convolve::initBuffers()
{
    initBuffer (analysisWindow);
    initBuffer (synthesisWindow);
    initBuffer (inputL);
    initBuffer (inputR);
    initBuffer (spectrum);
    initBuffer (polarSpectrum);
    initBuffer (displaySpectrum);
    initBuffer (outputL);
    initBuffer (outputR);
    initBuffer (lastPhaseInL);
    initBuffer (lastPhaseInR);
    initBuffer (lastPhaseOutL);
    initBuffer (lastPhaseOutR);
    initBuffer (lastAmpL);
    initBuffer (lastAmpR);
    initBuffer (lastFreqL);
    initBuffer (lastFreqR);
    initBuffer (indexL);
    initBuffer (indexR);
    initBuffer (sineTable);
}
    
void Convolve::allocateBuffers()
{
    
}



    
} // namespace sonicslash
