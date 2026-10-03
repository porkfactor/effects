#ifndef DSP_FILTER_BIQUAD_HPP_
#define DSP_FILTER_BIQUAD_HPP_

#include <cmath>
#include <algorithm>

struct lowpass_t{};
struct highpass_t{};
struct lowshelf_t{};
struct highshelf_t{};
struct notch_t{};
struct bandpass_t{};
struct allpass_t{};

struct biquad
{
public:
    static lowpass_t constexpr lowpass = lowpass_t{};
    static highpass_t constexpr highpass = highpass_t{};
    static lowshelf_t constexpr lowshelf = lowshelf_t{};
    static highshelf_t constexpr highshelf = highshelf_t{};
    static bandpass_t constexpr bandpass = bandpass_t{};
    static allpass_t constexpr allpass = allpass_t{};

    biquad(lowpass_t, double Fs, double f0, double Q, double gain)
    {
        double const w0 = (2.0 * M_PI) * (f0 / Fs);
        double const cosw0 = std::cos(w0);
        double const alpha = std::sin(w0) / (2.0 * Q);

        b0_ = (1.0 - cosw0) / 2.0;
        b1_ = (1.0 - cosw0);
        b2_ = b0_;
        a0_ = 1.0 + alpha;
        a1_ = -2.0 * cosw0;
        a2_ = 1.0 - alpha;
    }

    biquad(highpass_t, double Fs, double f0, double Q, double gain)
    {
        double const w0 = (2.0 * M_PI) * (f0 / Fs);
        double const cosw0 = std::cos(w0);
        double const alpha = std::sin(w0) / (2.0 * Q);

        b0_ = (1.0 + cosw0) / 2.0;
        b1_ = -(1.0 + cosw0);
        b2_ = b0_;
        a0_ = 1.0 + alpha;
        a1_ = -2.0 * cosw0;
        a2_ = 1.0 - alpha;
    }

    biquad(lowshelf_t, double Fs, double f0, double Q, double gain)
    {
        double const w0 = (2.0 * M_PI) * (f0 / Fs);
        double const cosw0 = std::cos(w0);
        double const sinw0 = std::sin(w0);
        double const S = std::clamp(Q / 2.0, 0.1, 4.0);
        double const A = std::pow(10, gain / 40.0);
        double const alpha = sinw0/2.0 * std::sqrt((A + 1.0/A) * (1.0/S - 1.0) + 2.0);

        b0_ = A * ((A + 1.0) - ((A - 1.0) * cosw0) + (2.0 * std::sqrt(A) * alpha));
        b1_ = 2 * A * ((A - 1.0) - ((A + 1.0) * cosw0));
        b2_ = A * ((A + 1.0) - ((A - 1.0) * cosw0) - (2.0 * std::sqrt(A) * alpha));
        a0_ = (A + 1.0) + ((A - 1.0) * cosw0) + (2.0 * std::sqrt(A) * alpha);
        a1_ = -2.0 * ((A - 1.0) + ((A + 1.0) * cosw0));
        a2_ = (A + 1.0) + ((A - 1.0) * cosw0) - (2.0 * std::sqrt(A) * alpha);
    }

    biquad(highshelf_t, double Fs, double f0, double Q, double gain)
    {
        double const w0 = (2.0 * M_PI) * (f0 / Fs);
        double const cosw0 = std::cos(w0);
        double const sinw0 = std::sin(w0);
        double const S = std::clamp(Q / 2.0, 0.1, 4.0);
        double const A = std::pow(10, gain / 40.0);
        double const alpha = sinw0/2.0 * std::sqrt((A + 1.0/A) * (1.0/S - 1.0) + 2.0);

        b0_ = A * ((A + 1.0) + ((A - 1.0) * cosw0) + (2.0 * std::sqrt(A) * alpha));
        b1_ = 2 * A * ((A - 1.0) + ((A + 1.0) * cosw0));
        b2_ = A * ((A + 1.0) + ((A - 1.0) * cosw0) - (2.0 * std::sqrt(A) * alpha));
        a0_ = (A + 1.0) - ((A - 1.0) * cosw0) + (2.0 * std::sqrt(A) * alpha);
        a1_ = -2.0 * ((A - 1.0) - ((A + 1.0) * cosw0));
        a2_ = (A + 1.0) - ((A - 1.0) * cosw0) - (2.0 * std::sqrt(A) * alpha);
    }

    biquad(allpass_t, double Fs, double f0, double Q, double gain)
    {
        double const w0 = (2.0 * M_PI) * (f0 / Fs);
        double const cosw0 = std::cos(w0);
        double const alpha = std::sin(w0) / (2.0 * Q);

        b0_ = 1.0 - alpha;
        b1_ = -2.0 * cosw0;
        b2_ = 1.0 + alpha;
        a0_ = 1.0 + alpha;
        a1_ = -2.0 * cosw0;
        a2_ = 1.0 - alpha;
    }

    biquad(bandpass_t, double Fs, double f0, double Q, double gain)
    {
        double const w0 = (2.0 * M_PI) * (f0 / Fs);
        double const cosw0 = std::cos(w0);
        double const sinw0 = std::sin(w0);
        double const alpha = std::sin(w0) / (2.0 * Q);

        if (gain == 0.0)
        {
            b0_ = alpha;
            b1_ = 0.0;
            b2_ = -alpha;
            a0_ = 1.0 + alpha;
            a1_ = -2.0 * cosw0;
            a2_ = 1.0 - alpha;
        }
        else
        {
            b0_ = sinw0 / 2.0;
            b1_ = 0.0;
            b2_ = -sinw0 / 2.0;
            a0_ = 1.0 + alpha;
            a1_ = -2.0 * cosw0;
            a1_ = 1.0 - alpha;
        }
    }

    biquad(notch_t, double Fs, double f0, double Q, double gain)
    {
        double const w0 = (2.0 * M_PI) * (f0 / Fs);
        double const cosw0 = std::cos(w0);
        double const alpha = std::sin(w0) / (2.0 * Q);

        b0_ = 1.0;
        b1_ = -2.0 * cosw0;
        b2_ = 1.0;
        a0_ = 1.0 + alpha;
        a1_ = -2.0 * cosw0;
        a2_ = 1.0 - alpha;
    }

    inline float input(float x)
    {

    }

private:
    double b0_;
    double b1_;
    double b2_;
    double a0_;
    double a1_;
    double a2_;
};

#endif
