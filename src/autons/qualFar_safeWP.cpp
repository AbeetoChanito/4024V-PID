#include "autos.hpp"
#include "chassisConfig.hpp"
#include "robotSubsystems.hpp"

void qualFar_safeWP() {
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
    chassis.swing(-25, SwingType::RightSwing);
    wingBackLeft.retract();
    chassis.swing(15, SwingType::RightSwing);
    intake.move(-127);
    pros::delay(400);
    chassis.arcadeControl(127, 0);
    pros::delay(500);
    chassis.arcadeControl(0, 0);
    intake.move(0);
    chassis.move(-12);
    chassis.turn(-135);
    chassis.move(23);
    chassis.swing(-90, SwingType::LeftSwing);
    chassis.move(25);
}