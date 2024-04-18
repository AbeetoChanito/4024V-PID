#include "autonSelector.hpp"

#include "pros/llemu.hpp"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"


#include <array>
#include <cmath>
#include <functional>
#include <utility>


#include "autos.hpp"

std::array<std::function<void(void)>, 9> autos{qualClose_safeWP, qualClose_soloWP, qualFar_safeWP,
                                               qualFar_6BallWP, elimsClose_rushRetreat, elimsClose_rushWedge,
                                               elimsFar_6BallSafe, elimsFar_6BallRush, elimsFar_5BallRush};

pros::adi::Potentiometer autonPot('A');

uint8_t getAutonNumber() {
  return std::floor(autonPot.get_value() / 4096.0 *
                    static_cast<float>(autos.size()));
}

void callSelectedAuton() { autos[getAutonNumber()](); }

void showAuto() {
  pros::Task task([]() {
    while (pros::competition::is_disabled()) {
      pros::lcd::print(0, "current selected auto: %i", getAutonNumber());

      pros::delay(10);
    }

    pros::lcd::clear_line(0);
  });
}