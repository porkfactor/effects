#ifndef DSP_MUSIC_PITCH_HPP_
#define DSP_MUSIC_PITCH_HPP_

#include "interval.hpp"

namespace dsp
{
    namespace music
    {
        struct pitch
        {
            constexpr pitch(double v) :
                hertz_(v)
            {}

            template<typename _Rep, typename _Period>
            inline pitch &operator+=(interval<_Rep, _Period> const &r)
            {
                return *this;
            }

            template<typename _Rep, typename _Period>
            inline pitch &operator-=(interval<_Rep, _Period> const &r)
            {
                return *this;
            }

            double hertz() const noexcept;

            friend inline bool operator==(pitch const &l, pitch const &r)
            {
                return l.hertz_ == r.hertz_;
            }

            friend inline bool operator!=(pitch const &l, pitch const &r)
            {

            }

        private:
            std::ratio<1> hertz_;
        };

        template<typename _Rep, typename _Period>
        inline pitch operator+(pitch const &l, interval<_Rep, _Period> const &r)
        {
            pitch result(l);
            return l += r;
        }

        template<typename _Rep, typename _Period>
        inline pitch operator-(pitch const &l, interval<_Rep, _Period> const &r)
        {
            pitch result(l);
            return l -= r;
        }

        template<typename _Rep, typename _Period>
        inline interval<_Rep, _Period> operator-(pitch const &l, pitch const &r)
        {
            return l.hertz() / r.hertz();
        }

        static inline constexpr pitch a0(27.5);
        static inline constexpr pitch a1(55.0);
        static inline constexpr pitch a2(110.0);
        static inline constexpr pitch a3(220.0);
        static inline constexpr pitch a4(440.0);
        static inline constexpr pitch a5(880.0);
        static inline constexpr pitch a6(1760.0);
        static inline constexpr pitch a7(3520.0);
        static inline constexpr pitch a8(7040.0);
    }
}

#endif
