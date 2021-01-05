#pragma once

#include "../../Math/Windows.h"
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
    long numBlocks = { 0 };
    
    long sizeImpulse = { 0 }; // in samples
    long sizeConvolution = { 0 }; // in samples
    long sizeFFT = { 4096 };
    long halfSizeFFT = { 2048 };
    long incWin;
    long windowType = { legacy::HAMMING };
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

    std::shared_ptr<SoundInfo> inSIPtr;
    std::shared_ptr<SoundInfo> filtSIPtr;
    std::shared_ptr<SoundInfo> outSIPtr;
};

} // namespace sonicslash
