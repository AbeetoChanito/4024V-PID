#include "angleUtil.hpp"

#include <cmath>

static float sanitizeAngle(float angle) {
    return std::fmod(std::fmod(angle, 360) + 360, 360);
}

float getPath(float target, float actual, AngularDirection direction) {
    target = sanitizeAngle(target);
    actual = sanitizeAngle(actual);

    float rawError = target - actual;

    float clockwiseError = (rawError < 0) ? rawError + 360 : rawError;
    float counterClockwiseError = (rawError > 0) ? rawError - 360 : rawError;

    if (std::abs(clockwiseError) > std::abs(counterClockwiseError)) {
        return (direction == AngularDirection::LongestPath) ? clockwiseError : counterClockwiseError;
    } else {
        return (direction == AngularDirection::LongestPath) ? counterClockwiseError : clockwiseError;
    }
}