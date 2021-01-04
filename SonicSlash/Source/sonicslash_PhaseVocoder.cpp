#include "sonicslash_PhaseVocoder.h"

namespace sonicslash {

using namespace legacy;
    
static float roundOverlapToValidValue (float overlap)
{
    if (overlap < 0.75f) return 0.5f;
    if (overlap < 1.5f)  return 1.0f;
    if (overlap < 3.0f)  return 2.0f;

    return 4.0f;
}
    
PhaseVocoder::PhaseVocoder()
{
    scaleFunction.fill (1.0f);
}
    
bool PhaseVocoder::setNumPoints (long points)
{
    if (inSIPtr == nullptr)
        return false;
    
    if (inSIPtr->sRate < 1000.0)
        return false;
    
    points = static_cast<long> (juce::jlimit (8, 4096, juce::nextPowerOfTwo (static_cast<int> (points))));
    
    frequency = inSIPtr->sRate / points;
    
    if (! setOverlap (overlap))
        return false;
    
    return true;
}

bool PhaseVocoder::setWindowType (long type)
{
    windowType = juce::jlimit (WINDOWTYPE_MIN, WINDOWTYPE_MAX, type);
    return true;
}
    
bool PhaseVocoder::updateRelativeScale()
{
    if (! relative)
    {
        relativeScale = scaleFactor;
        return true;
    }

    if (time)
    {
        if (inSIPtr->sRate < 1000.0)
            return false;
        
        if (inSIPtr->frameSize <= 0.0)
            return false;
        
        if (inSIPtr->nChans <= 0)
            return false;
        
        if (inSIPtr->numBytes <= 0)
            return false;
        
        const double inLength = inSIPtr->numBytes / (inSIPtr->sRate * inSIPtr->nChans * inSIPtr->frameSize);

        relativeScale = scaleFactor * inLength;
        return true;
    }
    
    // pitch
    relativeScale = std::exp2 (scaleFactor / 12.0f);
    return true;
}
    
bool PhaseVocoder::setOverlap (float value)
{
    overlap = roundOverlapToValidValue (value);
    windowSize = (long) (points * overlap);
    setBestRatio();

    return updateRelativeScale();
}

bool PhaseVocoder::setAnalysisRate (long samplesPerFFT)
{
    jassert (windowSize > 0);
    decimation = juce::jmax (1L, samplesPerFFT);
    
    if (decimation > (windowSize >> 3))
        decimation = windowSize >> 3;
    
    if (time)
        scaleFactor = (float) interpolation / decimation;
    else
        interpolation = decimation;
    
    return updateRelativeScale();
}

bool PhaseVocoder::setSynthesisRate (long samplesPerFFT)
{
    jassert (windowSize > 0);
    jassert (decimation > 0);

    interpolation = juce::jmax (1L, samplesPerFFT);

    if (interpolation > (windowSize >> 3))
        interpolation = windowSize >> 3;
    
    if (time)
        scaleFactor = (float) interpolation / decimation;
    else
        decimation = interpolation;
    
    return updateRelativeScale();
}

bool PhaseVocoder::setScaleValue (bool isRelative, bool isTime, float value)
{
    relative = isRelative;
    time = isTime;
    relativeScale = scaleFactor = value;
    
    if (time)
        setBestRatio(); // NB!! in the legacy code the equivalent call exceptionally doesn't re-assign the scaleFactor (ours always does)

    return updateRelativeScale();
}

bool PhaseVocoder::setScaleFunction (bool isRelative, bool isTime, VariableFunction function)
{
    if (! setScaleValue (isRelative, isTime, isTime ? 1.0f : 0.0f))
        return false;
    
    scaleFunction = function;
    return true;
}

bool PhaseVocoder::setGating (bool enable, float minAmplitudeLinear, float thresholdUnderMaxLinear)
{
    // thresholdUnderMax appears to be the legacy P_RATIO_FIELD ?
    // legacy UI values were in dB, internal values are linear
    
    if (! enable)
    {
        gatingEnabled = false;
        minAmplitude = 0.0f;
        maskRatio = 0.0f;
        return true;
    }
    
    gatingEnabled = true;
    minAmplitude = juce::jmax (0.0f, minAmplitudeLinear);
    maskRatio = juce::jmax (0.0f, thresholdUnderMaxLinear);

    return true;
}
    
void PhaseVocoder::setBestRatio()
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

void PhaseVocoder::initBuffers()
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
    
bool PhaseVocoder::isStateValid()
{
    if (inSIPtr == nullptr)
        return false;
    
    return true;
}
    
bool PhaseVocoder::allocateBuffers()
{
    initBuffers();
    
    if (! isStateValid())
    {
        jassertfalse;
        return false;
    }
    
    allocateBuffer (analysisWindow, windowSize);
    allocateBuffer (synthesisWindow, windowSize);
    allocateBuffer (inputL, windowSize);
    allocateBuffer (spectrum, points);
    allocateBuffer (polarSpectrum, points * 2);
    allocateBuffer (displaySpectrum, halfPoints + 1);
    allocateBuffer (outputL, windowSize);
    allocateBuffer (lastPhaseInL, halfPoints + 1);
    allocateBuffer (lastPhaseOutL, halfPoints + 1);

    if (! time)
    {
        allocateBuffer (lastAmpL, halfPoints + 1);
        allocateBuffer (lastFreqL, halfPoints + 1);
        allocateBuffer (indexL, halfPoints + 1);
        allocateBuffer (sineTable, 8192);
    }

    if (inSIPtr->nChans == STEREO)
    {
        allocateBuffer (inputR, windowSize);
        allocateBuffer (outputR, windowSize);
        allocateBuffer (lastPhaseInR, halfPoints + 1);
        allocateBuffer (lastPhaseOutR, halfPoints + 1);

        if (! time)
        {
            allocateBuffer (lastAmpR, halfPoints + 1);
            allocateBuffer (lastFreqR, halfPoints + 1);
            allocateBuffer (indexR, halfPoints + 1);
        }
    }
    
    initSineTable();
    
    return true;
}

void PhaseVocoder::initSineTable()
{
    const int numSamples = sineTable.getNumSamples();

    if (numSamples == 0)
        return;
    
    for (int n = 0; n < numSamples; ++n)
        setBufferSample (sineTable, n, 0.5f * std::cos (n * twoPi / numSamples));
}
    
void PhaseVocoder::phaseInterpolate (float polarSpectrum[], float lastPhaseIn[], float lastPhaseOut[])
{
    float amplitude, phase; // seem unused!?
    
    const float phasePerBand = ((float) decimation * twoPi) / (float) points;
    
    for (long bandNumber = 0; bandNumber <= halfPoints; ++bandNumber)
    {
        const long ampIndex = bandNumber << 1;
        const long phaseIndex = ampIndex + 1;
        
        float phaseDifference = 0.0f;
        
        // take difference between the current phase value and previous value for each channel
        
        if (polarSpectrum[ampIndex] == 0.0f)
        {
            polarSpectrum[phaseIndex] = lastPhaseOut[bandNumber];
        }
        else
        {
            if (phaseLocking) // NB it seems from the legacy code phaseLocking is always false!?
            {
                float maxAmplitude = 0.0f;
                
                // set low band info
                
                if (bandNumber > 1)
                {
                    maxAmplitude = polarSpectrum[ampIndex - 2];
                    phaseDifference = (polarSpectrum[phaseIndex - 2] - lastPhaseIn[bandNumber - 1]) - phasePerBand;
                }
                
                if (polarSpectrum[ampIndex] > maxAmplitude)
                {
                    maxAmplitude = polarSpectrum[ampIndex];
                    phaseDifference = polarSpectrum[phaseIndex] - lastPhaseIn[bandNumber];
                }
                
                if (bandNumber != halfPoints)
                    if (polarSpectrum[ampIndex + 2] > maxAmplitude)
                        phaseDifference = (polarSpectrum[phaseIndex + 2] - lastPhaseIn[bandNumber + 1]) + phasePerBand;
            }
            else
            {
                phaseDifference = polarSpectrum[phaseIndex] - lastPhaseIn[bandNumber];
            }
            
            lastPhaseIn[bandNumber] = polarSpectrum[phaseIndex];
            
            // unwrap phase differences

            phaseDifference *= scaleFactor;
        
            // create new phase from interpolate/decimate ratio

            polarSpectrum[phaseIndex] = lastPhaseOut[bandNumber] + phaseDifference;
        
            while (polarSpectrum[phaseIndex] > Pi)
                polarSpectrum[phaseIndex] -= twoPi;
        
            while (polarSpectrum[phaseIndex] < -Pi)
                polarSpectrum[phaseIndex] += twoPi;
        
            phase = lastPhaseOut[bandNumber] = polarSpectrum[phaseIndex];
            amplitude = polarSpectrum[ampIndex];
        }
    }
}

void PhaseVocoder::simpleSpectralGate (float polarSpectrum[])
{
    float maxAmplitude = 0.0;
    
    /* Find maximum amplitude */
    
    for (long bandNumber = 0; bandNumber <= halfPoints; ++bandNumber)
    {
        const long ampIndex = bandNumber << 1;
        
        if (polarSpectrum[ampIndex] > maxAmplitude)
            maxAmplitude = polarSpectrum[ampIndex];
    }
    
    const float maskAmplitude = maskRatio * maxAmplitude;
    
    for (long bandNumber = 0; bandNumber <= halfPoints; ++bandNumber)
    {
        const long ampIndex = bandNumber << 1;
       
        /* Set for Ducking */
        
        if (polarSpectrum[ampIndex] < maskAmplitude)
            polarSpectrum[ampIndex] = 0.0f;
        else if (polarSpectrum[ampIndex] < minAmplitude)
            polarSpectrum[ampIndex] = 0.0f;
    }
}

    
} // namespace sonicslash
