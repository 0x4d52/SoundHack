#pragma once

#include "../../Math/Windows.h"
#include "sonicslash_SoundFile.h"
#include <memory>

namespace sonicslash {
    
class Convolve
{
public:
    Convolve();
    
    bool setNumPoints (long points);
    bool setWindowType (long windowType);
    bool setOverlap (float overlap);
    bool setAnalysisRate (long samplesPerFFT);
    bool setSynthesisRate (long samplesPerFFT);
    bool setScaleValue (bool isRelative, bool isTime, float value);
    bool setScaleFunction (bool isRelative, bool isTime, VariableFunction function);
    bool setGating (bool enable, float minAmplitude, float thresholdUnderMax);
    
private:
    void setBestRatio();
    void initBuffers();
    bool allocateBuffers();
    bool isStateValid();
    void initSineTable();
    void phaseInterpolate (float polarSpectrum[], float lastPhaseIn[], float lastPhaseOut[]);
    void simpleSpectralGate (float polarSpectrum[]);

    //==========================================================================
    
    float overlap = { 1.0f };
    float frequency = { 44100.0f / 4096 };
    bool relative = { false };
    float relativeScale = { 1.0f };
    
    long points = { 4096 };
    long halfPoints = { 2048 };
    long windowSize;
    long decimation;
    long interpolation;
    long windowType = { legacy::HAMMING };
    bool phaseLocking = { false }; // seems to be always false in legacy code?
    double scaleFactor;
    double maskRatio;
    double minAmplitude = { 0.0 };
    short analysisType;
    bool time = { true };
    bool useFunction; // function is a 400 element float,.. for UI??
    
    Buffer analysisWindow;
    Buffer synthesisWindow;
    Buffer inputL;
    Buffer inputR;
    Buffer spectrum;
    Buffer polarSpectrum;
    Buffer displaySpectrum;
    Buffer outputL;
    Buffer outputR;
    Buffer lastPhaseInL;
    Buffer lastPhaseInR;
    Buffer lastPhaseOutL;
    Buffer lastPhaseOutR;
    Buffer lastAmpL;
    Buffer lastAmpR;
    Buffer lastFreqL;
    Buffer lastFreqR;
    Buffer indexL;
    Buffer indexR;
    Buffer sineTable;
    
    std::shared_ptr<SoundInfo> inSIPtr;
};
    
} // namespace sonicslash

