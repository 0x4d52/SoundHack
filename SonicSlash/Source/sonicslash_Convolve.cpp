#include "sonicslash_Convolve.h"

namespace sonicslash {
    
using namespace legacy;

Convolve::Convolve() {}
    
bool Convolve::updateNumChans()
{
    if (! soundInfoIsValid (filtSIPtr))
        return false;

    if (! soundInfoIsValid (inSIPtr))
        return false;

    if (inSIPtr->nChans == STEREO || filtSIPtr->nChans == STEREO)
        numChans = STEREO;
    else
        numChans = MONO;
    
    return true;
}
    
bool Convolve::openInputFile (const File& file)
{
    // need to implement opening the file and converting to a SoundInfo
    // and store in inSIPtr

    /// then..
    
    return updateNumChans();
}

bool Convolve::openFilterFile (const File& file)
{
    // need to implement opening the file and converting to a SoundInfo
    // and store in filtSIPtr
    
    // then...
    
    if (! soundInfoIsValid (filtSIPtr))
        return false;

    filtLengthMax = filtSIPtr->numBytes / (filtSIPtr->nChans * filtSIPtr->sRate * filtSIPtr->frameSize);

    if (! setFilterLength (filtLengthMax))
        jassertfalse;
    
    return updateNumChans();
}

bool Convolve::openOutputFile (const File& file)
{
    
}

bool Convolve::setWindowType (long type)
{
    windowType = juce::jlimit (WINDOWTYPE_MIN, WINDOWTYPE_MAX, type);
    windowImpulse = windowType != RECTANGLE;
    return true;
}

bool Convolve::setFilterLength (float length)
{
    if (! soundInfoIsValid (filtSIPtr))
        return false;
    
    jassert (filtLengthMax > 0.0f);
    
    if (length <= 0.0f)
        return false;
    
    length = juce::jmin (length, filtLengthMax);
    
    sizeImpulse = (long) (length * filtSIPtr->sRate);
    sizeConvolution = 2 * sizeImpulse - 1;
    
    for (sizeFFT = 1; sizeFFT < sizeConvolution;)
        sizeFFT <<= 1;

    halfSizeFFT = sizeFFT >> 1;
    
    return true;
}

bool Convolve::setAmplitudeScale (float scale)
{
    amplitudeScale = scale;
    return true;
}

bool Convolve::setNormalise (bool flag)
{
    normalise = flag;
    return true;
}

bool Convolve::setBrighten (bool flag)
{
    brighten = flag;
    return true;
}

//bool Convolve::setRingModulate (bool flag)
//{
//    ringMod = flag;
//    return true;
//}

bool Convolve::setMoving (bool flag)
{
    moving = flag;
    return true;
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
    
//    if (ringMod)
//    {
//        if (sizeConvolution <= 0)
//            return false;
//        
//        if (windowImpulse)
//            allocateBuffer (window, sizeConvolution);
//    }
//    else
    {
        if (sizeImpulse <= 0)
            return false;
        
        if (windowImpulse)
            allocateBuffer (window, sizeImpulse);
    }
    
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
    
bool Convolve::soundInfoIsValid (std::shared_ptr<SoundInfo> file)
{
    if (file == nullptr)
        return false;
    
    if (file->numBytes <= 0)
        return false;
    
    if (file->nChans <= 0)
        return false;
    
    if (file->frameSize <= 0)
        return false;
    
    if (file->sRate < 1000.0)
        return false;

    return true;
}

bool Convolve::initFIRProcess()
{
    numBlocks = 0;
    
    if (! soundInfoIsValid (inSIPtr))
        return false;
    
    if (! soundInfoIsValid (filtSIPtr))
        return false;
    
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


