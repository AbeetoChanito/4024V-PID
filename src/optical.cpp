#include "optical.hpp"

pros::Optical optical(4);

bool hueIsInTolerance(float targetHue, float tolerance) {
	return std::abs(targetHue - optical.get_hue()) <= tolerance;
}

bool saturationIsInTolerance(float targetSaturation, float tolerance) {
	return std::abs(targetSaturation - optical.get_saturation() * 100) <= tolerance;
}