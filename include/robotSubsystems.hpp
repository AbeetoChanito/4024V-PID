#pragma once

#include "pros/adi.hpp"
#include "pros/motor_group.hpp"
#include "pros/misc.hpp"

extern pros::Controller controller;

extern pros::adi::Pneumatics wingFrontLeft;
extern pros::adi::Pneumatics wingFrontRight;
extern pros::adi::Pneumatics wingBackLeft;

extern pros::adi::Pneumatics hangUp;
extern pros::adi::Pneumatics hangDown;

extern pros::MotorGroup intake;

extern pros::adi::DigitalIn hangLimitSwitch;

void doHangUp();

void doHangDown();