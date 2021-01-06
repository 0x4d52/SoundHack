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
    
    WavAudioFormat wavFormat;
    wavFormat.cr
    
//    reader.reset (manager.createReaderFor (fileToOpen));
//    
//    if (reader == nullptr)
//        return false;
//    
//    file = fileToOpen;
    
    return true;
}
    
} // namespace sonicslash
