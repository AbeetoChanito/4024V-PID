#include "chassisConfig.hpp"
std::shared_ptr<PID> lateralPID = std::make_shared<PID>(30.55, 0, 3.30);
std::shared_ptr<PIDSettled> lateralSettled = std::make_shared<PIDSettled>(
    lateralPID, std::initializer_list<Bound>{{0.5, 0}}, 0);

std::shared_ptr<PID> angularPID = std::make_shared<PID>(5, 0, 0.395);
std::shared_ptr<PIDSettled> angularSettled = std::make_shared<PIDSettled>(
    angularPID, std::initializer_list<Bound>{{5, 0.25}}, 0);

std::shared_ptr<PID> swingPID = std::make_shared<PID>(10.80, 0, 1);
std::shared_ptr<PIDSettled> swingSettled = std::make_shared<PIDSettled>(
    swingPID, std::initializer_list<Bound>{{5, 0.25}}, 0);

std::shared_ptr<pros::MotorGroup> leftMotors =
    std::make_shared<pros::MotorGroup>(
        std::initializer_list<std::int8_t>{-8, 9, -10},
        pros::v5::MotorGears::blue);
std::shared_ptr<pros::MotorGroup> rightMotors =
    std::make_shared<pros::MotorGroup>(
        std::initializer_list<std::int8_t>{1, -6, 3},
        pros::v5::MotorGears::blue);

pros::IMU imu(15);

Chassis chassis(leftMotors, rightMotors, imu, 2.75, 1, lateralPID,
                lateralSettled, angularPID, angularSettled, swingPID,
                swingSettled);