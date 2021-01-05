#pragma once

#include "sonicslash_common.h"
#include "sonicslash_SoundFile.h"
#include "../Processing/PhaseVocoder.h"

namespace sonicslash {
namespace legacy {
namespace PhaseVocoderRoutines {

using namespace PhaseVocoder;
    
short ScaleWindows(float analysisWindow[], float synthesisWindow[], PvocInfo myPI);
long ShiftIn(SoundInfoLegacy *mySI, float leftBlock[], float rightBlock[], long windowSize, long decimation, long *validSamples, long numberBlocks);
void WindowFold(float input[], float window[], float output[], long currentTime, long points, long windowSize);
void CartToPolar(float spectrum[], float polarSpectrum[], long halfLengthFFT);
void PolarToCart(float polarSpectrum[], float spectrum[], long halfLengthFFT);
void AddSynth(float polarSpectrum[], float output[], float lastAmp[], float lastFreq[], float lastPhase[], float sineIndex[], float sineTable[], PvocInfo myPI);
void OverlapAdd(float input[], float synthesisWindow[], float output[], long currentTime, long points, long windowSize);
long ShiftOut(SoundInfoLegacy *mySI, float leftBlock[], float rightBlock[], long currentTime, long interpolation, long windowSize);

} // namespace PhaseVocoderRoutines
} // namespace legacy
} // namespace sonicslash
