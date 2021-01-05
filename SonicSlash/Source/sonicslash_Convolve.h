#pragma once

#include "../../Math/Windows.h"
#include "sonicslash_SoundFile.h"
#include <memory>

namespace sonicslash {
    
class Convolve
{
public:
    Convolve();
    
    bool openInputFile (const File& file);
    bool openFilterFile (const File& file);
    bool openOutputFile (const File& file);
    bool setWindowType (long windowType);
    bool setFilterLength (long length);
    bool setAmplitudeScale (float scale);
    bool setNormalise (bool flag);
    bool setBrighten (bool flag);
    bool setRingModulate (bool flag);
    bool setMoving (bool flag);

private:
    void initBuffers();
    bool allocateBuffers();
    bool initFIRProcess();
    bool convolveBlock();
    void brightenFFT (float cartSpectrum[], long halfSizeFFT);

    //==========================================================================
    long numChans = { 2 };
    long numBlocks = { 0 };
    float amplitudeScale = { 1.0f };
    bool normalise = { false };
    
    long sizeImpulse = { 0 }; // in samples
    long sizeConvolution = { 0 }; // in samples
    long sizeFFT = { 4096 };
    long halfSizeFFT = { 2048 };
    long incWin = { 0 };
    long windowType = { legacy::HAMMING };
    long binPosition = { 0 };
    long binHeight = { 0 };
    bool moving  = { false };
    bool ringMod = { false };
    bool windowImpulse = { false };
    bool binaural = { false };
    bool brighten = { false };

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
