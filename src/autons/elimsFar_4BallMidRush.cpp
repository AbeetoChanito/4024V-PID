#include "autos.hpp"
#include "chassisConfig.hpp"
#include "robotSubsystems.hpp"

void elimsFar_4BallMidRush() {
    chassis.setHeading(-14);
    intake.move(-127);
    pros::delay(200);
    intake.move(127);
    chassis.move(40);
    pros::delay(300);
    intake.move(0);
    chassis.move(-44);
    chassis.turn(70);
    intake.move(-127);
    pros::delay(300);
    intake.move(0);
    chassis.turn(-95);
    intake.move(127);
    chassis.move(26);
    pros::delay(300);
    intake.move(0);
    chassis.move(-34);
    chassis.turn(60);
    wingFrontLeft.extend();
    chassis.move(6);
    wingBackLeft.extend();
    pros::delay(250);
    chassis.swing(-20, SwingType::RightSwing);
    wingBackLeft.retract();
    chassis.swing(30, SwingType::RightSwing);
    intake.move(-127);
    pros::delay(300);
    chassis.arcadeControl(127, 0);
    pros::delay(500);
    chassis.arcadeControl(0, 0);
    chassis.move(-7);
    chassis.arcadeControl(127, 0);
    pros::delay(500);
    chassis.arcadeControl(0, 0);
    wingFrontLeft.retract();
    chassis.move(-14);
    chassis.turn(-90);
}