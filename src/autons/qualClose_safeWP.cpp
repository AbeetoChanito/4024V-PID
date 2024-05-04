#include "autos.hpp"
#include "chassisConfig.hpp"
#include "robotSubsystems.hpp"

void qualClose_safeWP() {
  chassis.setHeading(135);
  chassis.move(-6);
  intake.move(-127);
  wingBackLeft.extend();
  pros::delay(300);
  intake.move(0);
  chassis.swing(60, SwingType::RightSwing);
  wingBackLeft.retract();
  chassis.swing(135, SwingType::RightSwing);
  chassis.move(4);
  chassis.swing(90, SwingType::RightSwing);
  intake.move(-127);
  chassis.move(34);
  pros::delay(1000);
  intake.move(0);
}