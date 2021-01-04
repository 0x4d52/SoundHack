#pragma once

#include "../../Math/Windows.h"
#include "sonicslash_SoundFile.h"
#include <memory>

namespace sonicslash {
    
class PhaseVocoder
{
public:
    PhaseVocoder();
    
    bool setNumPoints (long points);
    bool setWindowType (long windowType);
    bool setOverlap (float overlap);
    bool setAnalysisRate (long samplesPerFFT);
    bool setSynthesisRate (long samplesPerFFT);
    bool setScaleValue (bool isRelative, bool isTime, float value);
    bool setScaleFunction (bool isRelative, bool isTime, VariableFunction function);
    bool setGating (bool enable, float minAmplitudeLinear = 0.0f, float thresholdUnderMaxLinear = 0.0f);
    
private:
    void setBestRatio();
    void initBuffers();
    bool allocateBuffers();
    bool isStateValid();
    void initSineTable();
    void phaseInterpolate (float polarSpectrum[], float lastPhaseIn[], float lastPhaseOut[]);
    void simpleSpectralGate (float polarSpectrum[]);
    bool updateRelativeScale();

    //==========================================================================
    
    float overlap = { 1.0f };
    float frequency = { 44100.0f / 4096 };
    bool relative = { false };
    float relativeScale = { 1.0f };
    bool gatingEnabled = { false };
    bool normalise = { false };
    
    long points = { 4096 };
    long halfPoints = { 2048 };
    long windowSize = { 2048 };
    long decimation = { 128 };
    long interpolation = { 128 };
    long windowType = { legacy::HAMMING };
    bool phaseLocking = { false }; // seems to be always false in legacy code?
    double scaleFactor = { 1.0 };
    double maskRatio = { 0.0 };
    double minAmplitude = { 0.0 };
    short analysisType;
    bool time = { true };
    bool useFunction = { false };
    
    VariableFunction scaleFunction;
    
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

