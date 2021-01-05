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
    
    return true;
}

} // namespace sonicslash