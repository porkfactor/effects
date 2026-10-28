#include "EnvelopeVisualizer.hpp"

#include <parameters/EnvelopeAttackParameter.hpp>
#include <parameters/EnvelopeDecayParameter.hpp>
#include <parameters/EnvelopeReleaseParameter.hpp>
#include <parameters/EnvelopeSustainParameter.hpp>

namespace st1
{
    namespace components
    {
        EnvelopeVisualizer::EnvelopeVisualizer(juce::AudioProcessorValueTreeState &s, juce::String const &name) :
            juce::Component(name),
            state_(s),
            attackParameter_(s.getParameter(EnvelopeAttackParameter::identifier())),
            decayParamter_(s.getParameter(EnvelopeDecayParameter::identifier())),
            sustainParameter_(s.getParameter(EnvelopeSustainParameter::identifier())),
            releaseParameter_(s.getParameter(EnvelopeReleaseParameter::identifier()))
        {
            state_.addParameterListener(attackParameter_->paramID, this);
            state_.addParameterListener(decayParamter_->paramID, this);
            state_.addParameterListener(sustainParameter_->paramID, this);
            state_.addParameterListener(releaseParameter_->paramID, this);

            calculatePaths();
        }

        EnvelopeVisualizer::~EnvelopeVisualizer()
        {
            state_.removeParameterListener(attackParameter_->paramID, this);
            state_.removeParameterListener(decayParamter_->paramID, this);
            state_.removeParameterListener(sustainParameter_->paramID, this);
            state_.removeParameterListener(releaseParameter_->paramID, this);
        }

        void EnvelopeVisualizer::parameterChanged(juce::String const &parameterID, float newValue)
        {
            juce::ignoreUnused(parameterID);
            juce::ignoreUnused(newValue);

            /* doesn't matter which parameter has changed, we just need to trigger a redraw */
            triggerAsyncUpdate();
        }

        void EnvelopeVisualizer::handleAsyncUpdate(void)
        {
            calculatePaths();
            Component::repaint();
        }

        void EnvelopeVisualizer::paint(juce::Graphics &g)
        {
            auto bounds = Component::getLocalBounds();
            float scaled_width = static_cast<float>(bounds.getWidth());
            float scaled_height = static_cast<float>(bounds.getHeight());

            {
                static float const dashes[] = { 4.0f, 4.0f };
                static float const vertical_ticks[] = { 0.25f, 0.5f, 0.75f };
                static float const horizontal_ticks[] = { 0.25f, 0.5f, 0.75f };

                /* background */
                g.fillAll(juce::Colours::darkgrey);

                /* horizontal tick lines */
                g.setColour(juce::Colours::lightblue);
                for (int i = 0; i < juce::numElementsInArray(vertical_ticks); ++i)
                {
                    float y = scaled_height * vertical_ticks[i];

                    g.drawDashedLine(juce::Line<float>({0.0f, y}, {scaled_width, y}), dashes, juce::numElementsInArray(dashes), 1.0f);
                }

                /* verfical tick lines */
                g.setColour(juce::Colours::lightblue);
                for (int i = 0; i < juce::numElementsInArray(horizontal_ticks); ++i)
                {
                    float x = scaled_width * horizontal_ticks[i];

                    g.drawDashedLine(juce::Line<float>({x, 0.0}, {x, scaled_height}), dashes, juce::numElementsInArray(dashes), 1.0f);
                }
            }

            {
                /* grid lines */
                static float const dashes[] = { 4.0f, 4.0f };
                float scaled_sustain = (1.0f - sustainParameter_->getValue()) * static_cast<float>(bounds.getHeight());
                float scaled_attack = attackParameter_->getValue() * (scaled_width / 5.0f);
                
                g.setColour(juce::Colours::darkblue);
                g.drawDashedLine(juce::Line<float>{{0.0f, scaled_sustain}, {scaled_width, scaled_sustain}}, dashes, 2, 1.0f);
                g.drawDashedLine(juce::Line<float>{{scaled_attack, 0.0f}, {scaled_attack, scaled_height}}, dashes, 2, 1.0f);
            }

            {
                juce::Path curvePath;
                if (!segments_.empty())
                {
                    juce::Point<float> scale{scaled_width / 5, scaled_height};

                    curvePath.startNewSubPath({0.0f, scaled_height});
    
                    for (auto const &segment : segments_)
                    {
                    #if 1
                        switch (segment.style())
                        {
                        case EnvelopeSegment<float>::linear:
                            curvePath.lineTo(segment.end() * scale);
                            break;
                        case EnvelopeSegment<float>::quadratic:
                            curvePath.quadraticTo(segment.control1() * scale, segment.end() * scale);
                            break;
                        case EnvelopeSegment<float>::cubic:
                            curvePath.cubicTo(segment.control1() * scale, segment.control2() * scale, segment.end() * scale);
                            break;
                        }
                    #else
                        curvePath.lineTo(segment.end() * scale);
                    #endif
                    }
                }
    
                g.setColour(juce::Colours::cyan);
                g.strokePath(curvePath, juce::PathStrokeType(3.0f));
            }

            if (selected_ != npos)
            {
                g.setColour(grabbed_ ? juce::Colours::yellow : juce::Colours::white);
                
                g.fillEllipse(
                    segments_[selected_].start().x - anchorRadius,
                    segments_[selected_].start().y - anchorRadius,
                    anchorRadius * 2.0f, 
                    anchorRadius * 2.0f
                );
            }
        }

        static juce::Point<float> attack_point(juce::Point<float> const &start, juce::Point<float> const &end, float x)
        {
            float absoluteX = start.getX() + ((end.getX() - start.getX()) * x);
            float absoluteY = start.getY() + (1.0f - std::exp(-1.5f * x));

            return juce::Point<float>(absoluteX, absoluteY);
        }

        static juce::Point<float> decay_point(juce::Point<float> const &start, juce::Point<float> const &end, float x)
        {
            float absoluteX = start.getX() + ((end.getX() - start.getX()) * x);
            float absoluteY = end.getY() + std::exp(-4.95f * x);

            return juce::Point<float>(absoluteX, absoluteY);
        }

        void EnvelopeVisualizer::calculatePaths()
        {
            segments_.clear();

            auto attack = attackParameter_->getValue();
            auto decay = decayParamter_->getValue();
            auto sustain = sustainParameter_->getValue();
            auto release = releaseParameter_->getValue();

            juce::Point<float> start{0.0f, 0.0f};
            juce::Point<float> end{};

            /* attack */
            {
                end = juce::Point<float>(start.getX() + attack, 1.0f);
                segments_.push_back(EnvelopeSegment<float>(start, attack_point(start, end, 0.25f), attack_point(start, end, 0.5f), end));
                start = end;
            }

            /* decay */
            {
                end = juce::Point<float>(start.getX() + decay, sustain);
                segments_.push_back(EnvelopeSegment<float>(start, decay_point(start, end, 0.25f), decay_point(start, end, 0.5f), end));
                start = end;
            }

            /* sustain */
            {
                end = juce::Point<float>(start.getX() + 1.0f, sustain);
                segments_.push_back(EnvelopeSegment<float>(start, end));
                start = end;
            }

            /* release */
            {
                end = juce::Point<float>(start.getX() + release, 0.0f);
                segments_.push_back(EnvelopeSegment<float>(start, end));
                start = end;
            }
        }

        void EnvelopeVisualizer::mouseEnter(juce::MouseEvent const &e)
        {
            juce::ignoreUnused(e);
        }

        void EnvelopeVisualizer::mouseExit(juce::MouseEvent const &e)
        {
            juce::ignoreUnused(e);

            if (grabbed_)
            {
                grabbed_ = false;
                repaint();
            }

            selected_ = npos;
        }

        void EnvelopeVisualizer::mouseMove(juce::MouseEvent const &e)
        {
            juce::ignoreUnused(e);

            std::size_t selected = npos;

            for (size_t i = 0; i < segments_.size(); ++i)
            {
                if (e.position.getDistanceFrom(segments_[i].start()) <= grabTolerance)
                {
                    selected = i;
                    break;
                }
            }

            if (selected != selected_)
            {
                selected_ = selected;
                repaint();
            }
        }

        void EnvelopeVisualizer::mouseDrag(juce::MouseEvent const &e)
        {
            if (grabbed_ && (selected_ != npos))
            {
                // Update position and constrain to component bounds
                auto newPos = e.position;
                newPos.x = juce::jlimit(0.0f, (float)getWidth(), newPos.x);
                newPos.y = juce::jlimit(0.0f, (float)getHeight(), newPos.y);
                
                // segments_[selected_] = newPos;
                repaint();
            }
        }

        void EnvelopeVisualizer::mouseDown(juce::MouseEvent const &e)
        {
            juce::ignoreUnused(e);

            if (selected_ != npos)
            {
                grabbed_ = true;
                repaint();
            }
        }

        void EnvelopeVisualizer::mouseUp(juce::MouseEvent const &e)
        {
            juce::ignoreUnused(e);

            if (selected_ != npos)
            {
                grabbed_ = false;
                repaint();
            }
        }
    }
}
