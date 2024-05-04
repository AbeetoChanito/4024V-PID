#include "autos.hpp"
#include "chassisConfig.hpp"
#include "robotSubsystems.hpp"

void elimsClose_rushRetreat() {
  chassis.setHeading(9);
  intake.move(-127);
  pros::delay(200);
  intake.move(127);
  chassis.move(45);
  pros::delay(250);
  chassis.move(-11);
  intake.move(0);
  chassis.turn(33);
  chassis.move(-30);
  chassis.swing(135, SwingType::RightSwing);
  wingBackLeft.extend();
  pros::delay(300);
  chassis.move(8);
  chassis.swing(60, SwingType::RightSwing);
  wingBackLeft.retract();
  chassis.swing(100, SwingType::RightSwing);
  intake.move(-127);
  chassis.move(37);
  pros::delay(500);
  intake.move(0);
  chassis.move(-37);
}