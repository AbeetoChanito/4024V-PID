#include "autos.hpp"
#include "chassisConfig.hpp"
#include "robotSubsystems.hpp"

void qualClose_safeWP() {
    chassis.setHeading(135);
    intake.move(127);
    wingBackLeft.extend();
}