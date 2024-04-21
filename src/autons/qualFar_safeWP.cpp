#include "autos.hpp"
#include "chassisConfig.hpp"
#include "robotSubsystems.hpp"

void qualFar_safeWP() {
    chassis.setHeading(270);
    intake.move(-127);
    pros::delay(150);
    intake.move(127);
    chassis.move(7);
    pros::delay(300);
    intake.move(0);
    chassis.move(-28);
    chassis.swing(225, SwingType::LeftSwing);
    chassis.move(-6);
    chassis.turn(60);
    chassis.move(9);
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
    chassis.move(-13.5);
    chassis.turn(-135);
    chassis.move(26);
    chassis.swing(-90, SwingType::LeftSwing);
    chassis.move(28);
}