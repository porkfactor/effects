#include "OscillatorVoice.hpp"

#include <parameters/OscillatorTypeParameter.hpp>
#include <parameters/OscillatorAmplitudeParameter.hpp>
#include <parameters/OscillatorPitchShiftParameter.hpp>
#include <parameters/OscillatorPulseWidthParameter.hpp>

namespace st1
{
    namespace voices
    {
        static juce::String const sawtooth("Sawtooth");
        static juce::String const sinusoid("Sinusoid");
        static juce::String const square("Square");
        static juce::String const triangle("Triangle");


        std::unique_ptr<juce::AudioProcessorParameterGroup> OscillatorVoice::parameters(juce::String const &name)
        {
            return std::make_unique<juce::AudioProcessorParameterGroup>(
                juce::String("OVPG"),
                name,
                juce::String("|"),
                OscillatorTypeParameter::create("oscillator_type"),
                OscillatorPitchShiftParameter::create("pitch_shift"),
                OscillatorPulseWidthParameter::create("pulse_width"),
                OscillatorAmplitudeParameter::create("amplitude")
            );
        }

        OscillatorVoice::OscillatorVoice(juce::AudioProcessorValueTreeState &s) :
            juce::AudioProcessorValueTreeState::Listener(),
            state_(s),
            envelope_(s)
        {
        #if 1
            oscillators_.emplace_back(1.0, 0.50);
            oscillators_.emplace_back(1.5, 0.05);
            oscillators_.emplace_back(3.0, 0.10);
            oscillators_.emplace_back(5.0, 0.05);
            oscillators_.emplace_back(6.0, 0.125);
        #else
            oscillators_.emplace_back(1.0, 0.50);
            oscillators_.emplace_back(3.0, 0.10);
            oscillators_.emplace_back(5.0, 0.05);
            oscillators_.emplace_back(6.0, 0.125);
            oscillators_.emplace_back(7.0, 0.09);
            oscillators_.emplace_back(9.0, 0.005);
            oscillators_.emplace_back(13.0, 0.002);
            oscillators_.emplace_back(15.0, 0.001);
        #endif

            state_.addParameterListener(OscillatorTypeParameter::identifier(), this);
            state_.addParameterListener(OscillatorPitchShiftParameter::identifier(), this);
            state_.addParameterListener(OscillatorPulseWidthParameter::identifier(), this);
            state_.addParameterListener(OscillatorAmplitudeParameter::identifier(), this);

            if (auto parameter = state_.getParameter(OscillatorAmplitudeParameter::identifier()))
            {
                parameterAmplitudeCallback(parameter->getValue());
            }

            if (auto parameter = state_.getParameter(OscillatorPitchShiftParameter::identifier()))
            {
                parameterPitchShiftCallback(parameter->convertFrom0to1(parameter->getValue()));
            }

            if (auto parameter = state_.getParameter(OscillatorTypeParameter::identifier()))
            {
                parameterWaveTypeCallback(parameter->convertFrom0to1(parameter->getValue()));
            }
        }

        OscillatorVoice::~OscillatorVoice()
        {
            state_.removeParameterListener(OscillatorTypeParameter::identifier(), this);
            state_.removeParameterListener(OscillatorPitchShiftParameter::identifier(), this);
            state_.removeParameterListener(OscillatorPulseWidthParameter::identifier(), this);
            state_.removeParameterListener(OscillatorAmplitudeParameter::identifier(), this);
        }

        void OscillatorVoice::parameterChanged(juce::String const &parameterID, float newValue)
        {
            static std::map<juce::String, void(OscillatorVoice::*)(float)> const functors =
            {
                { OscillatorTypeParameter::identifier(), &OscillatorVoice::parameterWaveTypeCallback },
                { OscillatorAmplitudeParameter::identifier(), &OscillatorVoice::parameterAmplitudeCallback },
                { OscillatorPitchShiftParameter::identifier(), &OscillatorVoice::parameterPitchShiftCallback },
                { OscillatorPulseWidthParameter::identifier(), &OscillatorVoice::parameterPulseWidthCallback },
            };

            auto it = functors.find(parameterID);

            if (it != functors.end())
            {
                std::invoke(it->second, this, newValue);
            }
        }

        bool OscillatorVoice::canPlaySound(juce::SynthesiserSound *sound)
        {
            juce::ignoreUnused(sound);

            return true;
        }

        void OscillatorVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
        {
            juce::ignoreUnused(sound);
            juce::ignoreUnused(velocity);

            for (auto &oscillator : oscillators_)
            {
                oscillator.startNote(SynthesiserVoice::getSampleRate(), juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber), wave_type_);
            }
            envelope_.startNote(SynthesiserVoice::getSampleRate());
            velocity_ = static_cast<double>(velocity);

            pitchWheelMoved(currentPitchWheelPosition);
        }

        void OscillatorVoice::stopNote(float velocity, bool allowTailOff)
        {
            juce::ignoreUnused(velocity);
            juce::ignoreUnused(allowTailOff);

            if (allowTailOff)
            {
                envelope_.stopNote();
            }
            else
            {
                SynthesiserVoice::clearCurrentNote();
                reset();
            }
        }

        void OscillatorVoice::pitchWheelMoved(int newPitchWheelValue)
        {
            if (newPitchWheelValue == 0x2000)
            {
                pitchAdjust_ = 1.0;
            }
            else
            {
                double semitones = static_cast<double>(newPitchWheelValue - INT32_C(0x2000)) / 4096.0;
                double frequency_adjust = std::exp2(static_cast<double>(semitones) / 12.0);

                pitchAdjust_ = frequency_adjust;
            }

            for (auto &oscillator : oscillators_)
            {
                oscillator.pitchShift(pitchShift_ * pitchAdjust_);
            }
        }

        void OscillatorVoice::controllerMoved(int controllerNumber, int newControllerValue)
        {
            juce::ignoreUnused(controllerNumber);
            juce::ignoreUnused(newControllerValue);
        }

        void OscillatorVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
        {
            if (velocity_ != 0.0)
            {
                int const numChannels = outputBuffer.getNumChannels();
                int sampleIdx{};
                float currentSample = 0.0f;

                do
                {
                    int channelIdx{};
                    double sample{};

                    for (auto &oscillator : oscillators_)
                    {
                        sample += oscillator.generate();
                    }

                    currentSample = static_cast<float>(envelope_.process() * sample * velocity_);

                    do
                    {
                        outputBuffer.addSample(channelIdx, startSample + sampleIdx, currentSample);
                        ++channelIdx;
                    } while(channelIdx < numChannels);
    
                    ++sampleIdx;
                } while (sampleIdx < numSamples);
            }

            if (!envelope_.active())
                clearCurrentNote();
        }

        void OscillatorVoice::parameterWaveTypeCallback(float newValue)
        {
            switch (static_cast<OscillatorTypeParameter::OscillatorType>(newValue))
            {
            case OscillatorTypeParameter::OscillatorType::SAWTOOTH:
                setWaveType(Oscillator::wave_type::sawtooth);
                break;
            case OscillatorTypeParameter::OscillatorType::SINUSOID:
                setWaveType(Oscillator::wave_type::sinusoid);
                break;
            case OscillatorTypeParameter::OscillatorType::SQUARE:
                setWaveType(Oscillator::wave_type::square);
                break;
            case OscillatorTypeParameter::OscillatorType::TRIANGLE:
                setWaveType(Oscillator::wave_type::triangle);
                break;
            }
        }

        void OscillatorVoice::parameterAmplitudeCallback(float newValue)
        {
            amplitude_ = static_cast<double>(newValue);
        }

        void OscillatorVoice::parameterPitchShiftCallback(float newValue)
        {
            setPitchShift(static_cast<double>(newValue));
        }

        void OscillatorVoice::parameterPulseWidthCallback(float newValue)
        {
            juce::ignoreUnused(newValue);
        }

        void OscillatorVoice::setWaveType(enum Oscillator::wave_type type)
        {
            wave_type_ = type;
        }

        void OscillatorVoice::setPitchShift(double semitones)
        {
            pitchShift_ = std::exp2(static_cast<double>(semitones) / 12.0);

            for (auto &oscillator : oscillators_)
            {
                oscillator.pitchShift(pitchShift_ * pitchAdjust_);
            }
        }

        void OscillatorVoice::reset(void)
        {
            velocity_ = 0.0;
            pitchAdjust_ = 1.0;
            envelope_.reset();

            for (auto &oscillator : oscillators_)
            {
                oscillator.reset();
            }
        }
    }
}