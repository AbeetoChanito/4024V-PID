#include "autos.hpp"
#include "chassisConfig.hpp"
#include "robotSubsystems.hpp"

void elimsFar_6BallSafe() {
    chassis.setHeading(270);
    intake.move(-127);
    pros::delay(150);
    intake.move(127);
    chassis.move(6);
    pros::delay(300);
    intake.move(0);
    chassis.move(-25);
    chassis.swing(225, SwingType::LeftSwing);
    chassis.move(-5);
    chassis.turn(60);
    chassis.move(8);
    wingBackLeft.extend();
    chassis.swing(-20, SwingType::RightSwing);
    wingBackLeft.retract();
    chassis.swing(15, SwingType::RightSwing);
    intake.move(-127);
    pros::delay(400);
    chassis.arcadeControl(127, 0);
    pros::delay(500);
    chassis.arcadeControl(0, 0);
    intake.move(0);
    chassis.move(-14);
    chassis.turn(-75);
    intake.move(127);
    chassis.move(45);
    pros::delay(300);
    chassis.turn(70);
    intake.move(-100);
    chassis.move(10);
    pros::delay(500);
    intake.move(0);
    chassis.turn(-50);
    intake.move(127);
    chassis.move(17);
    pros::delay(300);
    intake.move(0);
    chassis.turn(90);
    intake.move(-127);
    wingFrontLeft.extend();
    chassis.arcadeControl(127, 0);
    pros::delay(750);
    chassis.arcadeControl(0, 0);
    intake.move(0);
}