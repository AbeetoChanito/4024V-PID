#include "main.h"

#include "control/pid.hpp"
#include "control/pidSettled.hpp"
#include "control/chassis.hpp"

pros::Controller controller(pros::E_CONTROLLER_MASTER);

// chassis config
auto leftMotors = std::make_shared<pros::MotorGroup>(std::initializer_list<std::int8_t>{1, -2, 3}, pros::v5::MotorGears::blue);
auto rightMotors = std::make_shared<pros::MotorGroup>(std::initializer_list<std::int8_t>{-8, 9, -10}, pros::v5::MotorGears::blue);
pros::IMU imu(18);

auto lateralPID = std::make_shared<PID>(0, 0, 0);
auto lateralSettled = std::make_shared<PIDSettled>(lateralPID, std::initializer_list<Bound> {{0, 0}, {0, 0}}, 0);

auto angularPID = std::make_shared<PID>(0, 0, 0);
auto angularSettled = std::make_shared<PIDSettled>(angularPID, std::initializer_list<Bound> {{0, 0}, {0, 0}}, 0);

auto swingPID = std::make_shared<PID>(0, 0, 0);
auto swingSettled = std::make_shared<PIDSettled>(swingPID, std::initializer_list<Bound> {{0, 0}, {0, 0}}, 0);

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

// intake
pros::MotorGroup intake(std::initializer_list<int8_t> {11, 20});

// wings
pros::adi::Pneumatics wingFrontLeft('b', false);
pros::adi::Pneumatics wingFrontRight('c', false);
pros::adi::Pneumatics wingBackLeft('d', false);

// hang
pros::adi::Pneumatics hangUp('e', false);
pros::adi::Pneumatics hangDown('f', false);

// controls
constexpr pros::controller_digital_e_t INTAKE_BUTTON = pros::E_CONTROLLER_DIGITAL_L1;
constexpr pros::controller_digital_e_t OUTTAKE_BUTTON = pros::E_CONTROLLER_DIGITAL_L2;
constexpr pros::controller_digital_e_t FRONT_LEFT_WING_BUTTON = pros::E_CONTROLLER_DIGITAL_RIGHT;
constexpr pros::controller_digital_e_t FRONT_RIGHT_WING_BUTTON = pros::E_CONTROLLER_DIGITAL_Y;
constexpr pros::controller_digital_e_t BACK_LEFT_WING_BUTTON = pros::E_CONTROLLER_DIGITAL_R2;
constexpr pros::controller_digital_e_t HANG_BUTTON = pros::E_CONTROLLER_DIGITAL_R1;
constexpr pros::controller_digital_e_t REVERSE_BUTTON = pros::E_CONTROLLER_DIGITAL_X;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

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
void autonomous() {}

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
	pros::Mutex hangMutex;

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

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
			if (hangedUp) {
				pros::Task hangTask([&](){
					hangMutex.take();
					hangUp.extend();
					pros::delay(250);
					hangUp.retract();
					hangMutex.give();
				});
			} else {
				pros::Task hangTask([&](){
					hangMutex.take();
					hangDown.extend();
					hangMutex.give();
				});
			}

			hangedUp = true;
		}

		float left = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		float right = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

		if (controller.get_digital(REVERSE_BUTTON)) {
			chassis.tankControl(-left, -right);
		} else {
			chassis.tankControl(left, right);
		}

 		pros::delay(10);
	}
}