#include "autonSelector.hpp"

#include "pros/llemu.hpp"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"


#include <array>
#include <cmath>
#include <functional>
#include <utility>


#include "autos.hpp"

std::array<std::function<void(void)>, 9> autos {qualClose_safeWP, qualClose_rushWedge, qualClose_rushRetreat,
                                               qualFar_safeWP, elimsClose_rushRetreat, elimsClose_rushWedge,
                                               elimsFar_6BallSafe, elimsFar_4BallMidRush, elimsFar_4BallLeftRush};

std::array<const char*, 9> autoNames {"Qual Close WP", "Qual Close Rush Wedge", "Qual Close Rush Retreat",
                                    "Qual Far Safe WP", "Elims Close Rush Retreat", "Elims Close Rush Wedge",
                                    "Elims Far 6 Ball Safe", "Elims Far 4 Ball Mid Rush", "Elims Far 4 Ball Left Rush"};

pros::adi::Potentiometer autonPot('A');

uint8_t getAutonNumber() {
  return std::floor(autonPot.get_value() / 4096.0 *
                    static_cast<float>(autos.size()));
}

void callSelectedAuton() {
  autos[getAutonNumber()](); 
}

void showAuto() {
  pros::Task task([]() {
    while (true) {
      pros::lcd::print(1, "current selected auto:");
      pros::lcd::print(2, "%s", autoNames[getAutonNumber()]);

      pros::delay(10);
    }
  });
}