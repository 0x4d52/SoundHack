#include "sonicslash_SoundFile.h"

namespace sonicslash {

// SoundInfo code?

namespace SoundFile {

void AllocateSoundIOMemory(short channels, long frames) {}
void SetSecondsPosition(SoundInfo *mySI, double seconds) {}
void SetOutputScale(long packMode) {}
long ReadQuadBlock(SoundInfo *mySI, long numSamples, float blockL[], float blockR[], float block3[], float block4[]) { return 0; }
long ReadStereoBlock(SoundInfo *mySI, long numSamples, float blockL[], float blockR[]) { return 0; }
long ReadMonoBlock(SoundInfo *mySI, long numSamples, float block[]) { return 0; }
long WriteStereoBlock(SoundInfo *mySI, long numSamples, float blockL[], float blockR[]) { return 0; }
long WriteMonoBlock(SoundInfo *mySI, long numSamples, float block[]) { return 0; }
    
} // namespace SoundFile
} // namespace sonicslash
