#pragma once

#include <JuceHeader.h>

namespace sonicslash
{
    
namespace legacy
{
    static constexpr float Pi = juce::MathConstants<float>::pi;
    static constexpr float twoPi = juce::MathConstants<float>::twoPi;

    static constexpr int TIME2FREQ = 1;
    static constexpr int FREQ2TIME = 0;
    
    static constexpr int HAMMING = 1;
    static constexpr int KAISER = 2;
    static constexpr int RAMP = 3;
    static constexpr int RECTANGLE = 4;
    static constexpr int SINC = 5;
    static constexpr int TRIANGLE = 6;
    static constexpr int VONHANN = 7;
        
} // namesapce legacy
} // namesapce sonicslash

