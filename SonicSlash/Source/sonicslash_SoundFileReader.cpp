#include "sonicslash_SoundFileReader.h"

namespace sonicslash {

bool SoundInfoReader::open (const File& fileToOpen)
{
    file = juce::File();
    reader.reset();
    
    juce::AudioFormatManager manager;
    manager.registerBasicFormats();
    
    reader.reset (manager.createReaderFor (fileToOpen));
    
    if (reader == nullptr)
        return false;
    
    file = fileToOpen;
    
    preferredFormat.sampleRateToUse  = reader->sampleRate;
    preferredFormat.numberOfChannels = reader->numChannels;
    preferredFormat.bitsPerSample    = reader->bitsPerSample;

    return true;
}
    
long SoundInfoReader::readStereo (long numSamples, float blockL[], float blockR[])
{
    if (reader == nullptr)
        return -1;
    
    float* ptrs[] = { blockL, blockR };
    
    if (reader->read (ptrs, 2, 0, static_cast<int> (numSamples)))
        return numSamples;
    
    return -1;
}
    
long SoundInfoReader::readMono (long numSamples, float block[])
{
    if (reader == nullptr)
        return -1;

    float* ptrs[] = { block };
    
    if (reader->read (ptrs, 1, 0, static_cast<int> (numSamples)))
        return numSamples;
    
    return -1;
}

} // namespace sonicslash
