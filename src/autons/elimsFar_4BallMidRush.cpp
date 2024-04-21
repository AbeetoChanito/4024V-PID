#include "autos.hpp"
#include "chassisConfig.hpp"
#include "robotSubsystems.hpp"

void elimsFar_4BallMidRush() {
    chassis.setHeading(-14);
    intake.move(-127);
    pros::delay(200);
    intake.move(127);
    chassis.move(45);
    pros::delay(300);
    intake.move(0);
    chassis.move(-50);
    chassis.turn(70);
    intake.move(-127);
    pros::delay(300);
    intake.move(0);
    chassis.turn(-95);
    intake.move(127);
    chassis.move(29);
    pros::delay(300);
    intake.move(0);
    chassis.move(-38);
    chassis.turn(60);
    wingFrontLeft.extend();
    chassis.move(7);
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
    chassis.move(-8);
    chassis.arcadeControl(127, 0);
    pros::delay(500);
    chassis.arcadeControl(0, 0);
    wingFrontLeft.retract();
    chassis.move(-16);
    chassis.turn(-90);
}