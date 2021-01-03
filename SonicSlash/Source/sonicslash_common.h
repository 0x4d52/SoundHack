#pragma once

#include <JuceHeader.h>

namespace sonicslash
{
    
namespace legacy
{
    static constexpr float Pi = juce::MathConstants<float>::pi;
    static constexpr float twoPi = juce::MathConstants<float>::twoPi;

    // FFT
    static constexpr int TIME2FREQ = 1;
    static constexpr int FREQ2TIME = 0;
    
    // Windows, windowing
    static constexpr int HAMMING = 1;
    static constexpr int KAISER = 2;
    static constexpr int RAMP = 3;
    static constexpr int RECTANGLE = 4;
    static constexpr int SINC = 5;
    static constexpr int TRIANGLE = 6;
    static constexpr int VONHANN = 7;
    
    // Analysis
    static constexpr int NO_ANALYSIS = 0;
    static constexpr int CSOUND_ANALYSIS = 1;
    static constexpr int SOUNDHACK_ANALYSIS = 2;
    static constexpr int SDIF_ANALYSIS = 3;
    static constexpr int PICT_ANALYSIS = 4;
    
    // SoundFile
    static constexpr int QUAD = 4;
    static constexpr int STEREO = 2;
    static constexpr int MONO = 1;
    
    static constexpr int RIGHT = 1;
    static constexpr int LEFT = 0;


    // PLACEHOLDERS to get necessary code to compile..
    
} // namesapce legacy
} // namesapce sonicslash

