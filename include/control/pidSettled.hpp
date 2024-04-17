#pragma once

#include <memory>
#include <vector>

#include "pid.hpp"

class Bound {
public:
  Bound(float errorRange, float time);

  bool isSettled(float error);

  void reset();

private:
  float m_errorRange;
  float m_errorTime;

  Timer m_timer;
};

class PIDSettled {
public:
  PIDSettled(std::shared_ptr<PID> pid, std::initializer_list<Bound> bounds,
             float maxTime = 0);

  void reset();

  bool isSettled();

private:
  std::shared_ptr<PID> m_pid;
  std::vector<Bound> m_bounds;
};