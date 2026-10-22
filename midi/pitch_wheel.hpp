#ifndef MIDI_PITCH_WHEEL_HPP_
#define MIDI_PITCH_WHEEL_HPP_

#include <cstdint>
#include <cmath>

namespace midi
{
    static uint16_t constexpr pitch_wheel_maximum = UINT16_C(0x3fff);
    static uint16_t constexpr pitch_wheel_minimum = UINT16_C(0x0000);
    static uint16_t constexpr pitch_wheel_center = UINT16_C(0x2000);
    static uint16_t constexpr pitch_wheel_semitone = (pitch_wheel_maximum + UINT16_C(1)) / UINT16_C(4);

    static double constexpr pitch_wheel_to_semitones(uint16_t wheel_value)
    {
        if (wheel_value == pitch_wheel_center)
            return 0.0;

        return static_cast<double>(static_cast<int16_t>(wheel_value) - static_cast<int16_t>(pitch_wheel_center)) / static_cast<double>(pitch_wheel_semitone);
    }

    static double constexpr pitch_wheel_to_cents(uint16_t wheel_value)
    {
        static double constexpr pitch_wheel_cent = static_cast<double>(pitch_wheel_semitone) / 12.0;

        if (wheel_value == pitch_wheel_center)
            return 0.0;

        return static_cast<double>(static_cast<int16_t>(wheel_value) - static_cast<int16_t>(pitch_wheel_center)) / pitch_wheel_cent;
    }

    static double constexpr pitch_wheel_to_frequency_delta(uint16_t wheel_value)
    {
        if (wheel_value == pitch_wheel_center)
            return 1.0;

        return std::exp2(pitch_wheel_to_semitones(wheel_value) / 12.0);
    }
}

#endif
