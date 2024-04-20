#pragma once

#include "pros/misc.hpp"

constexpr pros::controller_digital_e_t INTAKE_BUTTON =
    pros::E_CONTROLLER_DIGITAL_L1;
constexpr pros::controller_digital_e_t OUTTAKE_BUTTON =
    pros::E_CONTROLLER_DIGITAL_L2;
constexpr pros::controller_digital_e_t FRONT_LEFT_WING_BUTTON =
    pros::E_CONTROLLER_DIGITAL_R2;
constexpr pros::controller_digital_e_t FRONT_RIGHT_WING_BUTTON =
    pros::E_CONTROLLER_DIGITAL_RIGHT;
constexpr pros::controller_digital_e_t BACK_LEFT_WING_BUTTON =
    pros::E_CONTROLLER_DIGITAL_Y;
constexpr pros::controller_digital_e_t BACK_LEFT_WING_TOGGLE_BUTTON =
    pros::E_CONTROLLER_DIGITAL_B;
constexpr pros::controller_digital_e_t HANG_BUTTON =
    pros::E_CONTROLLER_DIGITAL_A;

constexpr float DRIVE_MIN_OUTPUT = 0;
constexpr float DRIVE_CURVE_SCALE = 1.05;