#include "control/chassis.hpp"

#include <cmath>
#include <numbers>
#include <iostream>

#include "pros/llemu.hpp"
#include "pros/motors.h"

void Chassis::brakeMotors() {
    m_leftMotors->set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
	m_rightMotors->set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    m_leftMotors->brake();
    m_rightMotors->brake();
}

void Chassis::initialize() {
    m_imu.reset(true);
}

void Chassis::setHeading(float heading) {
    m_imu.set_rotation(heading);
}

static float capSpeed(float speed, float maxSpeed) {
    if (speed > maxSpeed) return maxSpeed;
    if (speed < -maxSpeed) return -maxSpeed;
    return speed;
}

static float slew(float speed, float lastSpeed, float maxChange = 20) {
    float change = speed - lastSpeed;
    if (change > maxChange) change = maxChange;
    else if (change < -maxChange) change = -maxChange;
    return speed + change;
}

static void displayError(const char* motion, float error) {
    pros::lcd::print(3 ,"%s error: %f", motion, error);
}

void Chassis::turn(float targetHeading, float maxSpeed) {
    m_angularPID->reset();
    m_angularSettled->reset();

    while (!m_angularSettled->isSettled()) {
        float error = targetHeading - m_imu.get_rotation();
        float output = capSpeed(m_angularPID->update(targetHeading - m_imu.get_rotation()), maxSpeed);

        displayError("turn", error);

        arcadeControl(0, output);

        pros::delay(10);
    }
    
    brakeMotors();
}

void Chassis::swing(float targetHeading, SwingType swingType, float maxSpeed) {
    m_swingPID->reset();
    m_swingSettled->reset();

    brakeMotors();

    while (!m_swingSettled->isSettled()) {
        float error = targetHeading - m_imu.get_rotation();
        float output = capSpeed(m_swingPID->update(error), maxSpeed);
        
        displayError("swing", error);

        if (swingType == SwingType::LeftSwing) {
            m_leftMotors->move(output);
        } else {
            m_rightMotors->move(-output);
        }

        pros::delay(10);
    }
    
    brakeMotors();
}

void Chassis::move(float targetDistance, float maxSpeed) {
    m_lateralPID->reset();
    m_lateralSettled->reset();

    m_leftMotors->tare_position_all();
    m_rightMotors->tare_position_all();

    m_leftMotors->set_encoder_units(pros::MotorUnits::rotations);
    m_rightMotors->set_encoder_units(pros::MotorUnits::rotations);

    float lastOutput = NAN;

    while (!m_lateralSettled->isSettled()) {
        float error = targetDistance - (m_leftMotors->get_position(0) + m_rightMotors->get_position(0)) / 2
            * m_gearRatio * m_wheelDiameter * std::numbers::pi;

        displayError("distance", error);

        float output = m_lateralPID->update(error);
        if (!std::isnan(lastOutput) && std::abs(error) > 7.5) {
            output = slew(output, lastOutput);
        }
        output = capSpeed(output, maxSpeed);
        lastOutput = output;

        arcadeControl(output, 0);

        pros::delay(10);
    }
    
    brakeMotors();
}