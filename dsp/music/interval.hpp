#ifndef DSP_MUSIC_INTERVAL_HPP_
#define DSP_MUSIC_INTERVAL_HPP_

#include <chrono>
#include <ratio>

namespace dsp
{
    namespace music
    {
        template<typename _Rep, typename _Period = std::ratio<1>>
        struct interval
        {
        
        };

        using cent = interval<double, std::ratio<1, 100>>;
        using semitone = interval<double, std::ratio<12, 100>>;
        using tone = interval<double, std::ratio<24, 100>>;
    }
}

#endif
