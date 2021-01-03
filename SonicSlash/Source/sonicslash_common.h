#pragma once

#include <JuceHeader.h>

namespace sonicslash
{
    using Buffer = juce::AudioBuffer<float>;

    inline void allocateBuffer (Buffer& b, int size) { b.setSize (1, size); }
    inline void initBuffer (Buffer& b) { allocateBuffer (b, 0); }
    
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
    
    // Convolve
    static constexpr int F_FILTLENGTH_FIELD = 4;
    static constexpr int F_MEMORY_FIELD = 7;
    static constexpr int F_LOW_RADIO = 9;
    static constexpr int F_MED_RADIO = 11;
    static constexpr int F_HIGH_RADIO = 12;
    static constexpr int F_WINDOW_MENU = 15;
    static constexpr int F_RING_BOX = 14;
    static constexpr int F_BRIGHTEN_BOX = 16;
    static constexpr int F_MOVING_BOX = 13;
    static constexpr int F_NORM_BOX = 8;
    static constexpr int F_CANCEL_BUTTON = 2;
    static constexpr int F_FILTOPEN_BUTTON = 5;
    static constexpr int F_PROCESS_BUTTON = 1;

    // PLACEHOLDERS to get necessary code to compile..
    
} // namesapce legacy
} // namesapce sonicslash

