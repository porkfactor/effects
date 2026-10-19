#ifndef DSP_MATH_MATH_HPP_
#define DSP_MATH_MATH_HPP_

#include <cmath>

namespace dsp
{
    double sin(double x)
    {
        static double constexpr B = 4.0 / M_PI;
        static double constexpr C = -4.0 / (M_PI * M_PI);
        static double constexpr P = 0.225;
        static double constexpr Q = 0.775;

        double y = (B * x) + (C * x * abs(x));

        y = P * (y * abs(y) - y) + y;
        //y = (Q * y) + (P * y * abs(y));

        return y;
    }

    double cos(double x)
    {
        x += M_PI_2;

        if (x > M_PI)
            x -= (2.0f * M_PI);

        return dsp::sin(x);
    }

    float sin(float x)
    {
        static float constexpr B = 4.0f / M_PI;
        static float constexpr C = -4.0f / (M_PI * M_PI);
        static float constexpr P = 0.225f;
        static float constexpr Q = 0.775f;

        float y = (B * x) + (C * x * fabs(x));

        y = P * (y * fabs(y) - y) + y;
        //y = (Q * y) + (P * y * abs(y));

        return y;
    }

    float cos(float x)
    {
        x += M_PI_2;

        if (x > M_PI)
            x -= (2.0f * M_PI);

        return dsp::sin(x);
    }
}

#endif
