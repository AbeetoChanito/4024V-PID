#pragma once

#include "control/timer.hpp"

#include <limits>

class PID {
    public:
        PID(float kp, float ki, float kd, float iMax = std::numeric_limits<float>::infinity());

        void reset();

        float update(float error);

        float getError();

        bool isSettling();

        void enableLogging(float maxTime = 0);
    private:
        float m_kp;
        float m_ki;
        float m_kd;
        float m_iMax;

        float m_integral;
        float m_lastError;

        Timer m_timer;

        bool m_isSettling = false;
};