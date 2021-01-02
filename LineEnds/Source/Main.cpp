/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>

using namespace juce;

//==============================================================================
int main (int argc, char* argv[])
{
    
    StringArray paths;
    paths.add ("/Users/martinrobinson/development/MySoundHack/SoundHack/Math");
    paths.add ("/Users/martinrobinson/development/MySoundHack/SoundHack/Processing");
    paths.add ("/Users/martinrobinson/development/MySoundHack/SoundHack/SoundFile");
    paths.add ("/Users/martinrobinson/development/MySoundHack/SoundHack/ToolBox");

//    for (auto path : paths)
//    {
//        DirectoryIterator iter (File (path), true);
//
//        while (iter.next())
//        {
//            auto file = iter.getFile();
//
//            auto text = file.loadFileAsString();
//
//            if (text.contains ("\r\n"))
//            {
//                Logger::writeToLog (file.getFullPathName() + ": has rn endings");
//                continue;
//            }
//
//            if (text.contains ("\n\r"))
//            {
//                Logger::writeToLog (file.getFullPathName() + ": has nr endings");
//                continue;
//            }
//
//            text = text.replace("\r", "\n");
//
//            if (! file.replaceWithText (text))
//                Logger::writeToLog (file.getFullPathName() + ": failed");
//        }
//    }

    for (auto path : paths)
    {
        DirectoryIterator iter (File (path), true);
        
        while (iter.next())
        {
            auto file = iter.getFile();
            
            auto text = file.loadFileAsString();
            
            if (! text.contains("\r\n"))
                continue;
            
            text = text.replace("\r\n", "\n");
            
            if (! file.replaceWithText (text))
                Logger::writeToLog (file.getFullPathName() + ": failed");
            else
                Logger::writeToLog (file.getFullPathName() + ": done");
        }
    }

    
    // ..your code goes here!


    return 0;
}
