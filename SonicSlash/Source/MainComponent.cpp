#include "MainComponent.h"

#include "sonicslash_SoundFile.h"
#include "sonicslash_SoundFileReader.h"
#include "sonicslash_SoundFileWriter.h"

namespace sonicslash {

static void testFileRead()
{
    File inputFile ("~/Desktop/sonicslash/beat.wav");
    
    if (! inputFile.existsAsFile())
        return;
    
    SoundInfoReader inputInfo;
    inputInfo.open (inputFile);
}
    
static void testFileWrite()
{
    File outpuFile ("~/Desktop/sonicslash/out.wav");
    
    if (outpuFile.existsAsFile())
    {
        outpuFile.moveToTrash();
        
        while (outpuFile.existsAsFile())
            Thread::sleep (1);
    }
    
    SoundInfoWriter outputInfo;
    outputInfo.open (outpuFile);
}
    
MainComponent::MainComponent()
{
    setSize (600, 400);
    
    testFileRead();
    testFileWrite();
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

} // namespace sonicslash
