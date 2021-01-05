#include "sonicslash_Convolve.h"

namespace sonicslash {
    
using namespace legacy;

Convolve::Convolve() {}
    
bool Convolve::openInputFile (const File& file)
{
    
}

bool Convolve::openFilterFile (const File& file)
{
    
}

bool Convolve::openOutputFile (const File& file)
{
    
}

bool Convolve::setWindowType (long windowType)
{
    
}

bool Convolve::setFilterLength (long length)
{
    
}

bool Convolve::setAmplitudeScale (float scale)
{
    
}

bool Convolve::setNormalise (bool flag)
{
    
}

bool Convolve::setBrighten (bool flag)
{
    
}

bool Convolve::setRingModulate (bool flag)
{
    
}

bool Convolve::setMoving (bool flag)
{
    
}
    
void Convolve::initBuffers()
{
    initBuffer (impulseLeft);
    initBuffer (inputLeft);
    initBuffer (outputLeft);
    initBuffer (overlapLeft);
    initBuffer (impulseRight);
    initBuffer (inputRight);
    initBuffer (outputRight);
    initBuffer (overlapRight);
    initBuffer (window);
}

bool Convolve::allocateBuffers()
{
    initBuffers();

    if (filtSIPtr == nullptr)
        return false;
    
    if (ringMod && sizeConvolution <= 0)
        return false;
    
    if (! ringMod && sizeImpulse <= 0)
        return false;

    if (windowImpulse)
        allocateBuffer (window, ringMod ? sizeConvolution : sizeImpulse);

    allocateBuffer (displaySpectrum, halfSizeFFT + 1);
    allocateBuffer (impulseLeft, sizeFFT);
    
    allocateBuffer (inputLeft, sizeFFT);
    setBufferToReferTo (outputLeft, inputLeft);
    
    allocateBuffer (outputLeft, sizeFFT);
    allocateBuffer (overlapLeft, sizeFFT + 2);
    
    if (filtSIPtr->nChans == STEREO)
        allocateBuffer (impulseRight, sizeFFT);
    else
        setBufferToReferTo (impulseRight, impulseLeft);
    
    if (numChans == STEREO)
    {
        allocateBuffer (inputRight, sizeFFT);
        setBufferToReferTo (outputRight, inputRight);
        allocateBuffer (overlapRight, sizeFFT + 2);
    }
    else
    {
        setBufferToReferTo (outputRight, inputLeft);
        setBufferToReferTo (inputRight, inputLeft);
        setBufferToReferTo (overlapRight, overlapLeft);
    }

    return true;
}

bool Convolve::initFIRProcess()
{
    numBlocks = 0;
    
    {
        if (inSIPtr == nullptr)
            return false;
        
        if (inSIPtr->numBytes <= 0)
            return false;
        
        if (inSIPtr->nChans <= 0)
            return false;
        
        if (inSIPtr->frameSize <= 0)
            return false;
    }
    
    {
        if (filtSIPtr == nullptr)
            return false;
        
        if (filtSIPtr->numBytes <= 0)
            return false;
        
        if (filtSIPtr->nChans <= 0)
            return false;
        
        if (filtSIPtr->frameSize <= 0)
            return false;
    }
    
    if (outSIPtr == nullptr) // changed logic to assume the output is already created too
        return false;

    if (sizeImpulse <= 0)
        return false;
    
    const float inLength = (float) inSIPtr->numBytes / (inSIPtr->nChans * inSIPtr->frameSize);
    const float filtLength = (float) filtSIPtr->numBytes / (filtSIPtr->nChans * filtSIPtr->frameSize);
    incWin = (filtLength / inLength) * sizeImpulse;

    if (windowImpulse)
        Windows::GetWindow (getBufferWrite (window), sizeImpulse, windowType);
    
    overlapLeft.clear();
    overlapRight.clear();
    
//    SetOutputScale(outSIPtr->packMode); ??
    
    return true;
}

bool Convolve::convolveBlock()
{
    
}

void Convolve::brightenFFT (float cartSpectrum[], long halfSizeFFT)
{
    const float twoOverHalfFFT = 64.0f / halfSizeFFT;

    for (long bandNumber = 0; bandNumber <= halfSizeFFT; ++bandNumber)
    {
        const long realIndex = bandNumber << 1;
        const long imagIndex = realIndex + 1;
        
        if (bandNumber == 0)
        {
            cartSpectrum[realIndex] = cartSpectrum[realIndex] * (float) bandNumber * twoOverHalfFFT;
        }
        else if (bandNumber == halfSizeFFT)
        {
            cartSpectrum[1] = cartSpectrum[1] * (float) bandNumber * twoOverHalfFFT;
        }
        else
        {
            cartSpectrum[realIndex] = cartSpectrum[realIndex] * (float) bandNumber * twoOverHalfFFT;
            cartSpectrum[imagIndex] = cartSpectrum[imagIndex] * (float) bandNumber * twoOverHalfFFT;
        }
    }
}

    
} // namespace sonicslash


