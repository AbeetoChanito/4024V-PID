#include "autos.hpp"
#include "chassisConfig.hpp"
#include "robotSubsystems.hpp"

void qualClose_rushWedge() {
    chassis.setHeading(9);
    intake.move(-127);
    pros::delay(200);
    intake.move(127);
    chassis.move(40);
    pros::delay(250);
    chassis.move(-17);
    intake.move(0);
    chassis.swing(90, SwingType::LeftSwing);
    wingFrontLeft.extend();
    chassis.move(16);
    wingFrontLeft.retract();
    chassis.swing(35, SwingType::LeftSwing);
    chassis.move(-37);
    chassis.swing(135, SwingType::RightSwing);
    wingBackLeft.extend();
    pros::delay(300);
    chassis.move(7);
    chassis.swing(60, SwingType::RightSwing);
    wingBackLeft.retract();
    chassis.swing(100, SwingType::RightSwing);
    intake.move(-127);
    pros::delay(2000);
    chassis.move(26);
    pros::delay(500);
    intake.move(0);
}