#include "robotSubsystems.hpp"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::adi::Pneumatics wingFrontLeft('b', false);
pros::adi::Pneumatics wingFrontRight('c', false);
pros::adi::Pneumatics wingBackLeft('g', false);

pros::adi::Pneumatics hangUp('e', false);
pros::adi::Pneumatics hangDown('f', false);

pros::MotorGroup intake(std::initializer_list<int8_t> {-11, 20});

auto lateralPID = std::make_shared<PID>(10, 0, 0);
auto lateralSettled = std::make_shared<PIDSettled>(lateralPID, std::initializer_list<Bound> {{0, 0}, {0, 0}}, 0);

auto angularPID = std::make_shared<PID>(3, 0, 0);
auto angularSettled = std::make_shared<PIDSettled>(angularPID, std::initializer_list<Bound> {{0, 0}, {0, 0}}, 0);

auto swingPID = std::make_shared<PID>(2, 0, 0);
auto swingSettled = std::make_shared<PIDSettled>(swingPID, std::initializer_list<Bound> {{0, 0}, {0, 0}}, 0);

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

void doHangUp() {
	hangUp.extend();
}

void doHangDown() {
	hangUp.retract();
	hangDown.extend();
}