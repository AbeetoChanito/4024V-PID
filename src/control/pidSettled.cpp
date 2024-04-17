#include "control/pidSettled.hpp"
#include "control/pid.hpp"

#include <cmath>
#include <limits>

Bound::Bound(float errorRange, float errorTime)
    : m_errorRange(errorRange), m_errorTime(errorTime) {}

bool Bound::isSettled(float error) {
  if (std::abs(error) < m_errorRange) {
    if (m_timer.isStopped()) {
      m_timer.start();
    }

    if (m_timer.getElapsedTime() > m_errorTime) {
      return true;
    }
  } else {
    m_timer.stop();
  }

  return false;
}

void Bound::reset() { m_timer.stop(); }

PIDSettled::PIDSettled(std::shared_ptr<PID> pid,
                       std::initializer_list<Bound> bounds, float maxTime)
    : m_pid(pid), m_bounds(bounds) {
  if (maxTime != 0) {
    m_bounds.push_back(Bound(std::numeric_limits<float>::infinity(), maxTime));
  }
}

void PIDSettled::reset() {
  for (auto &bound : m_bounds) {
    bound.reset();
  }
}

bool PIDSettled::isSettled() {
  for (auto &bound : m_bounds) {
    if (bound.isSettled(m_pid->getError())) {
      return true;
    }
  }

  return false;
}