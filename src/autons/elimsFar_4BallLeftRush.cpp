#include "autos.hpp"
#include "chassisConfig.hpp"
#include "robotSubsystems.hpp"

void elimsFar_4BallLeftRush() {
    chassis.setHeading(-34);
    intake.move(-127);
    pros::delay(200);
    intake.move(127);
    chassis.move(58);
    pros::delay(275);
    intake.move(0);
    chassis.move(-11);
    chassis.turn(90);
    intake.move(-127);
    pros::delay(400);
    intake.move(0);
    chassis.turn(220);
    intake.move(127);
    chassis.move(10);
    pros::delay(300);
    intake.move(0);
    chassis.turn(85);
    intake.move(-127);
    chassis.arcadeControl(127, 0);
    pros::delay(600);
    chassis.arcadeControl(0, 0);
    intake.move(0);
    chassis.move(-12);
    chassis.turn(0);
    chassis.move(-47);
    // chassis.turn(-100);
    // intake.move(127);
    // chassis.move(25);
    // pros::delay(300);
    // intake.move(0);
    // chassis.move(-35);

    chassis.turn(70);
    intake.move(-127);
    chassis.move(17);
    chassis.turn(45);
    intake.move(0);
    wingBackLeft.extend();
    pros::delay(150);
    chassis.swing(-5, SwingType::RightSwing);
    wingBackLeft.retract();
    chassis.swing(20, SwingType::RightSwing);

    // pros::Task task([](){
    //     chassis.swing(30, SwingType::RightSwing);
    // });
    // while (imu.get_heading() < 5) {
    //     pros::delay(10);
    // }
    
    chassis.arcadeControl(127, 0);
    pros::delay(400);
    intake.move(0);
    chassis.arcadeControl(0, 0);
    chassis.move(-6);
    chassis.arcadeControl(127, 0);
    pros::delay(400);
    chassis.move(-6);
}