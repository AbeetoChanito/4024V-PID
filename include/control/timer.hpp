#pragma once

#include <cstdint>

class Timer {
public:
  Timer() = default;

  void stop();

  void start();

  bool isStopped();

  float getElapsedTime();

private:
  std::uint32_t m_time = 0;
};