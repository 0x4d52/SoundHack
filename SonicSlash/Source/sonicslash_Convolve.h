#pragma once

#include "../../Math/Windows.h"

namespace sonicslash {
    
class Convolve
{
public:
    Convolve ();
    
private:
    void setBestRatio();
    void initBuffers();
    void allocateBuffers();

    //==========================================================================
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
    bool time; // bool?
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
};
    
} // namespace sonicslash

