#include "robotSubsystems.hpp"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::adi::Pneumatics wingFrontLeft('b', false);
pros::adi::Pneumatics wingFrontRight('c', false);
pros::adi::Pneumatics wingBackLeft('g', false);

pros::adi::Pneumatics hangUp('e', false);
pros::adi::Pneumatics hangDown('f', false);

pros::MotorGroup intake(std::initializer_list<int8_t>{-11, 20});

pros::adi::DigitalIn hangLimitSwitch('h');

void doHangUp() { hangUp.extend(); }

void doHangDown() {
  hangUp.retract();
  hangDown.extend();
}