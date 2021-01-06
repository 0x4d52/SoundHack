#pragma once

#include "sonicslash_common.h"
#include "sonicslash_SoundFile.h"

namespace sonicslash {
    
class SoundInfoWriter : public SoundInfo
{
public:
    SoundInfoWriter() = default;
    
    bool open (const File& file) override;
    bool isWriter() const override { return true; }
    
    bool isValid() const override;

    long writeStereo (long numSamples, float blockL[], float blockR[]) override;
    long writeMono (long numSamples, float block[]) override;
    
private:
    
    //==========================================================================
    
    std::unique_ptr<juce::AudioFormatWriter> writer;
};
    
} // namespace sonicslash
