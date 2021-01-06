#include "sonicslash_SoundFileWriter.h"

namespace sonicslash {
    
bool SoundInfoWriter::open (const File& fileToOpen)
{
    file = juce::File();
    writer.reset();
    
    if (fileToOpen.hasFileExtension ("wav"))
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
    
    return true;
}
    
} // namespace sonicslash
