#pragma once

#include "sonicslash_common.h"

namespace sonicslash {

struct SoundInfo
{
//    FSSpec    sfSpec;            // name, parID and vRefNum
//    double    sRate;            /* sample rate*/
//    TimeScale timeScale;    /* if QT, its media timeScale */
//    TimeValue timeValue;    /* if QT, the position */
//    long    dataStart;        /* offset in data fork from begining of file (in bytes)*/
//    long    dataEnd;        /* byte position of the last sample*/
//    long    numBytes;        /* number of bytes of sound data */
//    long    packMode;        /* numeric format*/
//    Str255    compName;        /* string description of compressed numeric formats */
    long    nChans;            /* number of channels */
//    double    frameSize;        /* size of sample in bytes */
//    long    sfType;            /* type of soundfile header */
//    short    rFileNum;        /* resource file number */
//    short    dFileNum;        /* data file number */
//    long     spectFrameSize;            /* PVA files: size of FFT frames (2^n) */
//    long     spectFrameIncr;            /* PVA files: # new samples each fram (overlap) */
//    unsigned long playPosition;        // Where we are in the playback window.
//    CompStruct    comp;            // if an applecompressed file...
//    int        infoUpdate;        //    should we update the info window?
//    float    infoSamps[256];        // a little snippet for the infoWindow
//    float    peak;
//    float    peakFL;
//    float    peakFR;
//    float    peakRL;
//    float    peakRR;
//    SoundDisp    view;    /* window to display soundfile in */
//    SoundDisp    sigDisp;    /* window to display signal in */
//    SoundDisp    spectDisp;    /* window to display spectrum in */
//    SoundDisp    sonoDisp;        /* window to display sonogram in */
//    WindowPtr    infoWindow;        /* the window that describes the soundfile */
//    CGrafPtr    infoPort;
//    GDHandle    infoDevice;
//    GWorldPtr    infoOffScreen;
//    Ptr            nextSIPtr;    /* the next soundfile in the linked list (must be typdefed)*/
};
    
namespace SoundFile {
    
void AllocateSoundIOMemory(short channels, long frames);
void SetSecondsPosition(SoundInfo *mySI, double seconds);
void SetOutputScale(long packMode);
long ReadQuadBlock(SoundInfo *mySI, long numSamples, float blockL[], float blockR[], float block3[], float block4[]);
long ReadStereoBlock(SoundInfo *mySI, long numSamples, float blockL[], float blockR[]);
long ReadMonoBlock(SoundInfo *mySI, long numSamples, float block[]);
long WriteStereoBlock(SoundInfo *mySI, long numSamples, float blockL[], float blockR[]);
long WriteMonoBlock(SoundInfo *mySI, long numSamples, float block[]);
    
} // namespace SoundFile
} // namespace sonicslash
