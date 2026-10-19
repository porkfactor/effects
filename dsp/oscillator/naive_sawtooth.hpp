#ifndef DSP_OSCILLATORS_SAWTOOTH_HPP_
#define DSP_OSCILLATORS_SAWTOOTH_HPP_

#include "basic_oscillator.hpp"

namespace dsp
{
    template<typename _Type>
    class naive_sawtooth :
        public basic_oscillator<_Type>
    {
    public:
        using super = basic_oscillator<_Type>;
        using value_type = super::value_type;

        naive_sawtooth(value_type f0, value_type fs) :
            super(f0, fs)
        {
            angle_ = f0 / fs;
        }

        value_type sample(double phase) const noexcept
        {
            return angle_ * phase;
        }

    private:
        value_type angle_;
    };
}

#endif
