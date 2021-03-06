#include "AnimationStyle.h"

#include <cmath>

namespace carto {

    AnimationStyle::AnimationStyle(float relativeSpeed, float phaseInDuration, float phaseOutDuration, AnimationType::AnimationType fadeAnimationType, AnimationType::AnimationType sizeAnimationType) :
        _relativeSpeed(relativeSpeed),
        _phaseInDuration(phaseInDuration),
        _phaseOutDuration(phaseOutDuration),
        _fadeAnimationType(fadeAnimationType),
        _sizeAnimationType(sizeAnimationType)
    {
    }
    
    AnimationStyle::~AnimationStyle() {
    }
    
    float AnimationStyle::getRelativeSpeed() const {
        return _relativeSpeed;
    }

    float AnimationStyle::getPhaseInDuration() const {
        return _phaseInDuration;
    }

    float AnimationStyle::getPhaseOutDuration() const {
        return _phaseOutDuration;
    }

    AnimationType::AnimationType AnimationStyle::getFadeAnimationType() const {
        return _fadeAnimationType;
    }
    
    AnimationType::AnimationType AnimationStyle::getSizeAnimationType() const {
        return _sizeAnimationType;
    }

    float AnimationStyle::CalculateTransition(AnimationType::AnimationType animationType, float t) {
        switch (animationType) {
        case AnimationType::ANIMATION_TYPE_STEP:
            return t >= 0.5f ? 1.0f : 0.0f;
        case AnimationType::ANIMATION_TYPE_LINEAR:
            return t;
        case AnimationType::ANIMATION_TYPE_SMOOTHSTEP:
            return t * t * (3 - 2 * t);
        case AnimationType::ANIMATION_TYPE_SPRING:
            return -0.5f * std::exp(-6 * t) * (-2.0f * std::exp(6 * t) + std::sin(12 * t) + 2 * cos(12 * t));
        default:
            return 1.0f;
        }
    }

}
