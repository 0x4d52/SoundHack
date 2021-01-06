#include "sonicslash_SoundFile.h"

namespace sonicslash {

//==============================================================================

bool SoundInfo::setPreferredFormat (SoundFormat format)
{
    if (format.sampleRateToUse < 1000.0)
        return false;
    
    if (format.numberOfChannels < 1 || format.numberOfChannels > 2)
        return false;
    
    switch (format.bitsPerSample)
    {
        case 16: break;
        case 24: break;
        default: return false;
    }
    
    preferredFormat = format;
    return true;
}

//==============================================================================

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
