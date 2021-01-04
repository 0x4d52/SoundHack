#pragma once

#include "sonicslash_SoundFile.h"
#include <memory>

namespace sonicslash {
    
class Convolve
{
public:
    Convolve();
    
private:
    void initBuffers();
    bool allocateBuffers();
    bool initFIRProcess();
    bool convolveBlock();
    void brightenFFT (float cartSpectrum[], long halfSizeFFT);

    //==========================================================================
    long numChans = { 2 };
    
    long sizeImpulse;
    long sizeConvolution; // seems to be already multiplied by sizeof(float)
    long sizeFFT = { 4096 };
    long halfSizeFFT = { 2048 };
    long incWin;
    long windowType;
    long binPosition;
    long binHeight;
    short moving;
    bool ringMod = { false };
    bool windowImpulse = { false };
    short binaural;
    short brighten;

    Buffer impulseLeft;
    Buffer inputLeft;
    Buffer outputLeft;
    Buffer overlapLeft;
    Buffer impulseRight;
    Buffer inputRight;
    Buffer outputRight;
    Buffer overlapRight;
    Buffer window;
    Buffer displaySpectrum;

    std::shared_ptr<SoundInfo> filtSIPtr;
};

} // namespace sonicslash
