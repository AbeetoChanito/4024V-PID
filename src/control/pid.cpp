#include "control/pid.hpp"

#include <cmath>
#include <iostream>

#include "pros/misc.hpp"
#include "pros/rtos.hpp"

#include "control/timer.hpp"

PID::PID(float kp, float ki, float kd, float iMax)
    : m_kp(kp), m_ki(ki), m_kd(kd), m_iMax(iMax)  {
    
}

void PID::reset() {
    m_integral = 0;
    m_lastError = 0;
    m_timer.stop();
}

float PID::update(float error) {
    float dt = m_timer.getElapsedTime();

    bool signFlip = (std::signbit(error) != std::signbit(m_lastError));

    if (signFlip) m_isSettling = true;

    m_integral += error * dt;
    if (error > m_iMax || signFlip) { m_integral = 0; }

    float deltaError = (error - m_lastError) / dt;
    m_lastError = error;

    m_timer.start();

    return error * m_kp + m_integral * m_ki + deltaError * m_kd;
}

float PID::getError() { return m_lastError; }

bool PID::isSettling() { return m_isSettling; }

void PID::enableLogging(float maxTime) {
    pros::Task task([this, maxTime](){
        Timer timer;

        std::cout << "START" << std::endl;	
        pros::delay(10);

        timer.start();

        while (pros::competition::is_autonomous() && timer.getElapsedTime() < maxTime) {
            std::cout << timer.getElapsedTime() << " " << m_lastError << std::endl;

            pros::delay(50);
        }

        std::cout << "STOP" << std::endl;
    });

    pros::delay(10); // give time for timer to initialize
}