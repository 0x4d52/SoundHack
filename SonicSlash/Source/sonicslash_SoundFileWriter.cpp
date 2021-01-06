#include "sonicslash_SoundFileWriter.h"

namespace sonicslash {
    
bool SoundInfoWriter::open (const File& fileToOpen)
{
    file = juce::File();
    writer.reset();
    
    if (! fileToOpen.hasFileExtension ("wav"))
        return false;
    
    if (fileToOpen.exists())
    {
        if (fileToOpen.isDirectory())
            return false;

        if (! fileToOpen.moveToTrash())
            return false;
        
        while (fileToOpen.existsAsFile())
            Thread::sleep (1);
    }
    
    if (auto *const outputStream = fileToOpen.createOutputStream())
    {
        WavAudioFormat wavFormat;
        
        writer.reset (wavFormat.createWriterFor (outputStream,
                                                 preferredFormat.sampleRateToUse,
                                                 preferredFormat.numberOfChannels,
                                                 preferredFormat.bitsPerSample, {}, 0));
    }

    if (writer == nullptr)
        return false;
    
    file = fileToOpen;
    samplesWritten = 0;
    
    return true;
}
    
bool SoundInfoWriter::isValid() const
{
    if (writer == nullptr)
        return false;
    
    return true;
}
    
int64 SoundInfoWriter::getLengthInSamples() const
{
    if (! isValid())
        return -1;
    
    return samplesWritten;
}
    
double SoundInfoWriter::getSampleRate() const
{
    if (! isValid())
        return -1.0;

    return writer->getSampleRate();
}
    
long SoundInfoWriter::writeStereo (long numSamples, float blockL[], float blockR[])
{
    if (writer == nullptr)
        return -1;
    
    float* ptrs[] = { blockL, blockR };
    
    if (writer->writeFromFloatArrays (ptrs, 2, static_cast<int> (numSamples)))
    {
        samplesWritten += numSamples;
        return numSamples;
    }
    
    return -1;
}
    
long SoundInfoWriter::writeMono (long numSamples, float block[])
{
    if (writer == nullptr)
        return -1;

    float* ptrs[] = { block };
    
    if (writer->writeFromFloatArrays (ptrs, 1, static_cast<int> (numSamples)))
    {
        samplesWritten += numSamples;
        return numSamples;
    }

    return -1;
}
    
} // namespace sonicslash
