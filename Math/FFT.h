#pragma once

#include "sonicslash_common.h"

namespace sonicslash {
namespace legacy {
namespace FFT {

void InitFFTTable(void);
void FFT(float data[], long numberPoints, short direction);
void bitreverse(float data[], long numberData);
void RealFFT(float data[], long numberPoints, short direction);
    
} // namespace FFT
} // namespace legacy
} // namespace sonicslash

