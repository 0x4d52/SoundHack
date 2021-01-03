#pragma once

#include "sonicslash_common.h"

namespace sonicslash {
namespace legacy {
namespace Convolve {
            
//void HandleFIRDialog(void);
//void HandleFIRDialogEvent(short itemHit);
short InitFIRProcess(void);
short ConvolveBlock(void);
short AllocConvMem(void);
void DeAllocConvMem(void);
void BrightenFFT(float cartSpectrum[], long halfSizeFFT);

struct ConvolveInfo
{
    long sizeImpulse;
    long sizeConvolution;
    long sizeFFT;
    long halfSizeFFT;
    long incWin;
    long windowType;
    long binPosition;
    long binHeight;
    short moving;
    short ringMod;
    short windowImpulse;
    short binaural;
    short brighten;
};

} // namespace Convolve
} // namespace legacy
} // namespace sonicslash
