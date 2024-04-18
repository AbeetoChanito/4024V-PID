#include "main.h"

#include "autonSelector.hpp"
#include "chassisConfig.hpp"
#include "control/chassis.hpp"
#include "robotControls.hpp"
#include "robotSubsystems.hpp"

void initialize() {
  pros::lcd::initialize();
  chassis.initialize();
}

void disabled() { showAuto(); }

void competition_initialize() {}

void autonomous() {
  intake.move(127);
  chassis.move(43);
}

void driveCurve(float curve) {}

float expoDriveCurve(float input) {
  const float g = std::abs(input);
  const float i = pow(DRIVE_CURVE_SCALE, g - 127) * g * std::copysign(1, input);
  return (127.0 - DRIVE_MIN_OUTPUT) / 127.0f * i +
         DRIVE_MIN_OUTPUT * std::copysign(1, input);
}

void opcontrol() {
  bool hangedUp = false;

  while (true) {
    if (controller.get_digital(INTAKE_BUTTON)) {
      intake.move(127);
    } else if (controller.get_digital(OUTTAKE_BUTTON)) {
      intake.move(-127);
    } else {
      intake.move(0);
    }

    if (controller.get_digital(FRONT_LEFT_WING_BUTTON)) {
      wingFrontLeft.extend();
    } else {
      wingFrontLeft.retract();
    }

    if (controller.get_digital(FRONT_RIGHT_WING_BUTTON)) {
      wingFrontRight.extend();
    } else {
      wingFrontRight.retract();
    }

    if (controller.get_digital(BACK_LEFT_WING_BUTTON)) {
      wingBackLeft.extend();
    } else {
      wingBackLeft.retract();
    }

    if (controller.get_digital_new_press(HANG_BUTTON)) {
      if (hangedUp) {
        doHangDown();
      } else {
        doHangUp();
      }

      hangedUp = true;
    }

    float left =
        expoDriveCurve(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
    float right = expoDriveCurve(
        controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));

    controller.print(0, 0, "%f %f", left, right);

    chassis.tankControl(left, right);

    pros::delay(10);
  }
}