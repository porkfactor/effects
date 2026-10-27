#include "EnvelopeVisualizer.hpp"

namespace st1
{
    namespace components
    {
        EnvelopeVisualizer::EnvelopeVisualizer(juce::AudioProcessorValueTreeState &s, juce::String const &name)
        {
            segments_.push_back({ 50.0f,  150.0f });
            segments_.push_back({ 150.0f, 50.0f  });
            segments_.push_back({ 250.0f, 250.0f });
            segments_.push_back({ 350.0f, 150.0f });
        }

        void EnvelopeVisualizer::paint(juce::Graphics &g)
        {
            g.fillAll(juce::Colours::darkgrey);

            juce::Path curvePath;
            if (!segments_.empty())
            {
                curvePath.startNewSubPath(segments_[0].start());

                for (size_t i = 1; i < segments_.size(); ++i)
                {
                    curvePath.lineTo(segments_[i].start());
                }
            }

            g.setColour(juce::Colours::cyan);
            g.strokePath(curvePath, juce::PathStrokeType(3.0f));

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

        void EnvelopeVisualizer::mouseEnter(juce::MouseEvent const &e)
        {

        }

        void EnvelopeVisualizer::mouseExit(juce::MouseEvent const &e)
        {
            if (grabbed_)
            {
                grabbed_ = false;
                repaint();
            }

            selected_ = npos;
        }

        void EnvelopeVisualizer::mouseMove(juce::MouseEvent const &e)
        {
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
            if (selected_ != npos)
            {
                grabbed_ = true;
                repaint();
            }
        }

        void EnvelopeVisualizer::mouseUp(juce::MouseEvent const &e)
        {
            if (selected_ != npos)
            {
                grabbed_ = false;
                repaint();
            }
        }
    }
}
