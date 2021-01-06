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
    
private:
    
    //==========================================================================
    
    std::unique_ptr<juce::AudioFormatWriter> writer;
};
    
} // namespace sonicslash
