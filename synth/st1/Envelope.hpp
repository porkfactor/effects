#ifndef ST1_ENVELOPE_HPP_
#define ST1_ENVELOPE_HPP_

#include <chrono>

/**
 * so: 
 *  we have a number of archetypes - we could just create a separate generator class per
 * archetype, or have a generic generator class:
 * 
 *  generic:
 *      list of segments - each having core properties (duration, delta), and
 *          invariant properties
 * 
 *      thought: if I modify the end-level of stage C by dragging downwards, we expect the
 *          end-level of stage D to be unaffacted. is this a series of levels split by a 
 *          time-delta, or a series of vectors?
 * 
 *          we're representing as an x-y plot, but what are we storing as is a question. 
 *          it feels like treating each stage as its own concept makes more sense - there
 *          are functional attachments. 
 * 
 *      pro: not dealing with subclasses. but ... do we want to be anyway?
 *      pro: easier to interface to editor, but does that matter?
 *      con: gets a bit messy trying to maintain invariants
 */

namespace st1
{
    class EnvelopeSegment
    {
    public:

        inline std::chrono::microseconds duration() const noexcept
        {
            return duration_;
        }

    private:
        std::chrono::microseconds duration_{};
    };

    class EnvelopeAttack :
        public EnvelopeSegment
    {
    public:

    private:
    };

    class EnvelopeDelay :
        public EnvelopeSegment
    {
    public:

    private:
    };

    class EnvelopeSustain :
        public EnvelopeSegment
    {
    public:

    private:
    };

    class EnvelopeRelease :
        public EnvelopeSegment
    {
    public:

    private:
    };

    class EnvelopeGenerator
    {
    public:

    private:

        
    };
}

#endif
