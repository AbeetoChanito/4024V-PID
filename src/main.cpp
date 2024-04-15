#include "main.h"

#include "control/pid.hpp"
#include "control/pidSettled.hpp"
#include "control/chassis.hpp"
#include "control/timer.hpp"

#include "robotControls.hpp"
#include "robotSubsystems.hpp"
#include "optical.hpp"
#include "autonSelector.hpp"
#include "chassisConfig.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	chassis.initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	showAuto();
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	// callSelectedAuton();
	angularPID->enableLogging();
	chassis.turn(90);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
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

		float left = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		float right = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

		chassis.tankControl(left, right);

		if ((hueIsInTolerance(0) && saturationIsInTolerance(100) || // red
			(hueIsInTolerance(240) && saturationIsInTolerance(100)))  // blue
			&& hangedUp) {
			doHangDown();
		}

 		pros::delay(10);
	}
}