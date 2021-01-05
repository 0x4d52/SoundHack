#include "sonicslash_SoundFile.h"

namespace sonicslash {

namespace legacy {

namespace SoundFile {

void AllocateSoundIOMemory(short channels, long frames) {}
void SetSecondsPosition(SoundInfoLegacy *mySI, double seconds) {}
void SetOutputScale(long packMode) {}
long ReadQuadBlock(SoundInfoLegacy *mySI, long numSamples, float blockL[], float blockR[], float block3[], float block4[]) { return 0; }
long ReadStereoBlock(SoundInfoLegacy *mySI, long numSamples, float blockL[], float blockR[]) { return 0; }
long ReadMonoBlock(SoundInfoLegacy *mySI, long numSamples, float block[]) { return 0; }
long WriteStereoBlock(SoundInfoLegacy *mySI, long numSamples, float blockL[], float blockR[]) { return 0; }
long WriteMonoBlock(SoundInfoLegacy *mySI, long numSamples, float block[]) { return 0; }
    
} // namespace SoundFile
} // namespace legacy
} // namespace sonicslash
