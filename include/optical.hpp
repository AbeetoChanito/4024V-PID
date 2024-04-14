#pragma once

#include "pros/optical.hpp"

extern pros::Optical optical;

bool hueIsInTolerance(float targetHue, float tolerance = 10);

bool saturationIsInTolerance(float targetSaturation, float tolerance = 10);