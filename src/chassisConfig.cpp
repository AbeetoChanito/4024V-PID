#include "chassisConfig.hpp"

std::shared_ptr<PID> lateralPID = std::make_shared<PID>(10, 0, 0);
std::shared_ptr<PIDSettled> lateralSettled = std::make_shared<PIDSettled>(lateralPID, std::initializer_list<Bound> {{0, 0}, {0, 0}}, 0);

std::shared_ptr<PID> angularPID = std::make_shared<PID>(3, 0, 0);
std::shared_ptr<PIDSettled> angularSettled = std::make_shared<PIDSettled>(angularPID, std::initializer_list<Bound> {{0, 0}, {0, 0}}, 0);

std::shared_ptr<PID> swingPID = std::make_shared<PID>(2, 0, 0);
std::shared_ptr<PIDSettled> swingSettled = std::make_shared<PIDSettled>(swingPID, std::initializer_list<Bound> {{0, 0}, {0, 0}}, 0);

std::shared_ptr<pros::MotorGroup> leftMotors = std::make_shared<pros::MotorGroup>(std::initializer_list<std::int8_t>{-8, 9, -10}, pros::v5::MotorGears::blue);
std::shared_ptr<pros::MotorGroup> rightMotors = std::make_shared<pros::MotorGroup>(std::initializer_list<std::int8_t>{1, -2, 3}, pros::v5::MotorGears::blue);

pros::IMU imu(18);

Chassis chassis(
	leftMotors,
	rightMotors,
	imu,
	3.25,
	0.75,
	lateralPID,
	lateralSettled,
	angularPID,
	angularSettled,
	swingPID,
	swingSettled
);