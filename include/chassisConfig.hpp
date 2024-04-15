#pragma once

#include <memory>

#include "pros/motor_group.hpp"
#include "pros/imu.hpp"

#include "control/chassis.hpp"
#include "control/pid.hpp"

extern std::shared_ptr<pros::MotorGroup> leftMotors;
extern std::shared_ptr<pros::MotorGroup> rightMotors;

extern pros::IMU imu;

extern std::shared_ptr<PID> lateralPID;
extern std::shared_ptr<PIDSettled> lateralSettled;

extern std::shared_ptr<PID> angularPID;
extern std::shared_ptr<PIDSettled> angularSettled;

extern std::shared_ptr<PID> angularPID;
extern std::shared_ptr<PIDSettled> angularSettled;

extern std::shared_ptr<PID> swingPID;
extern std::shared_ptr<PIDSettled> swingSettled;

extern Chassis chassis;