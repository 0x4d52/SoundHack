#pragma once

#include <JuceHeader.h>
#include <array>

namespace sonicslash
{
    using BufferValueType = float;
    using Buffer = juce::AudioBuffer<BufferValueType>;

    template<typename SizeType>
    inline void allocateBuffer (Buffer& b, SizeType size)
    {
        b.setSize (1, static_cast<int> (size));
        
        if (size > 0)
            b.clear();
    }
    
    inline void initBuffer (Buffer& b) { allocateBuffer (b, 0); }
    
    inline void setBufferToReferTo (Buffer& b1, Buffer& b2)
    {
        jassert (b2.getNumChannels() == 1);
        b1.setDataToReferTo (b2.getArrayOfWritePointers(), 1, b2.getNumSamples());
    }
    
    template<typename IndexType, typename BufferValueType>
    inline void setBufferSample (Buffer& b, IndexType index, BufferValueType value)
    {
        b.setSample (0, static_cast<int> (index), value);
    }
    
    inline BufferValueType* getBufferWrite (Buffer& b)
    {
        return b.getWritePointer (0);
    }
    
    inline const BufferValueType* getBufferRead (Buffer& b)
    {
        return b.getReadPointer (0);
    }

    using VariableFunction = std::array<float, 400>;
    
namespace legacy
{
    static constexpr float Pi = juce::MathConstants<float>::pi;
    static constexpr float twoPi = juce::MathConstants<float>::twoPi;

    // FFT
    static constexpr long TIME2FREQ = 1;
    static constexpr long FREQ2TIME = 0;
    
    // Windows, windowing
    static constexpr long HAMMING = 1;
    static constexpr long KAISER = 2;
    static constexpr long RAMP = 3;
    static constexpr long RECTANGLE = 4;
    static constexpr long SINC = 5;
    static constexpr long TRIANGLE = 6;
    static constexpr long VONHANN = 7;
    
    static constexpr long WINDOWTYPE_MIN = 1;
    static constexpr long WINDOWTYPE_MAX = 7;

    
    // Analysis
    static constexpr long NO_ANALYSIS = 0;
    static constexpr long CSOUND_ANALYSIS = 1;
    static constexpr long SOUNDHACK_ANALYSIS = 2;
    static constexpr long SDIF_ANALYSIS = 3;
    static constexpr long PICT_ANALYSIS = 4;
    
    // SoundFile
    static constexpr long QUAD = 4;
    static constexpr long STEREO = 2;
    static constexpr long MONO = 1;
    
    static constexpr long RIGHT = 1;
    static constexpr long LEFT = 0;
    
    // Convolve
    static constexpr long F_FILTLENGTH_FIELD = 4;
    static constexpr long F_MEMORY_FIELD = 7;
    static constexpr long F_LOW_RADIO = 9;
    static constexpr long F_MED_RADIO = 11;
    static constexpr long F_HIGH_RADIO = 12;
    static constexpr long F_WINDOW_MENU = 15;
    static constexpr long F_RING_BOX = 14;
    static constexpr long F_BRIGHTEN_BOX = 16;
    static constexpr long F_MOVING_BOX = 13;
    static constexpr long F_NORM_BOX = 8;
    static constexpr long F_CANCEL_BUTTON = 2;
    static constexpr long F_FILTOPEN_BUTTON = 5;
    static constexpr long F_PROCESS_BUTTON = 1;

    // PLACEHOLDERS to get necessary code to compile..
    
} // namesapce legacy
} // namesapce sonicslash

