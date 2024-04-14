#pragma once

#include "pros/adi.hpp"

extern pros::adi::Potentiometer autonPot;

uint8_t getAutonNumber();

void callSelectedAuton();

void showAuto();