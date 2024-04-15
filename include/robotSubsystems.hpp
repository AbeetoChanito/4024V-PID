#pragma once

#include <memory>

#include "pros/adi.hpp"
#include "pros/motor_group.hpp"
#include "pros/misc.hpp"

#include "control/chassis.hpp"

extern pros::Controller controller;

extern pros::adi::Pneumatics wingFrontLeft;
extern pros::adi::Pneumatics wingFrontRight;
extern pros::adi::Pneumatics wingBackLeft;

extern pros::adi::Pneumatics hangUp;
extern pros::adi::Pneumatics hangDown;

extern pros::MotorGroup intake;

void doHangUp();

void doHangDown();