#pragma once

#include "sonicslash_common.h"
#include "sonicslash_SoundFile.h"

namespace sonicslash {
    
class SoundInfoReader : public SoundInfo
{
public:
    SoundInfoReader() = default;
    
    bool open (const File& file) override;
    bool isWriter() const override { return false; }
    
    long readStereo (long numSamples, float blockL[], float blockR[]) override;
    long readMono (long numSamples, float block[]) override;
    
private:
    
    //==========================================================================
    
    std::unique_ptr<juce::AudioFormatReader> reader;
};


} // namespace sonicslash
