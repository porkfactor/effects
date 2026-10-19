#ifndef DSP_BASIC_OSCILLATOR_HPP_
#define DSP_BASIC_OSCILLATOR_HPP_

namespace dsp
{
    template<typename _Type>
    class basic_oscillator
    {
    public:
        using value_type = _Type;

        basic_oscillator(value_type fo, value_type fs);

        inline value_type oscillator_frequency() const noexcept
        {
            return oscillator_frequency_;
        }

        inline value_type sampling_frequency() const noexcept
        {
            return sampling_frequency_;
        }

    private:
        value_type oscillator_frequency_;
        value_type sampling_frequency_;
    };
}

#endif
