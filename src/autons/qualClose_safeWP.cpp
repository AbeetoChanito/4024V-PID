#include "autos.hpp"
#include "chassisConfig.hpp"
#include "robotSubsystems.hpp"

void qualClose_safeWP() {
    chassis.setHeading(135);
    chassis.move(-5);
    intake.move(-127);
    wingBackLeft.extend();
    pros::delay(300);
    intake.move(0);
    chassis.swing(60, SwingType::RightSwing);
    wingBackLeft.retract();
    chassis.swing(100, SwingType::RightSwing);
    intake.move(-127);
    chassis.move(32);
    pros::delay(1000);
    intake.move(0);
}