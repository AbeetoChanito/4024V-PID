#include "control/chassis.hpp"
#include "pros/motors.h"

#include <cmath>

Chassis::Chassis(
    std::shared_ptr<pros::AbstractMotor> leftMotor, 
    std::shared_ptr<pros::AbstractMotor> rightMotor,
    const pros::IMU& imu,
    float wheelDiameter,
    float gearRatio,
    std::shared_ptr<PID> lateralPID,
    std::shared_ptr<PIDSettled> lateralSettled,
    std::shared_ptr<PID> angularPID,
    std::shared_ptr<PIDSettled> angularSettled,
    std::shared_ptr<PID> swingPID,
    std::shared_ptr<PIDSettled> swingSettled
):  m_leftMotor(leftMotor),
    m_rightMotor(rightMotor),
    m_imu(imu),
    m_wheelDiameter(wheelDiameter),
    m_gearRatio(gearRatio), 
    m_lateralPID(lateralPID), 
    m_lateralSettled(lateralSettled),
    m_angularPID(angularPID),
    m_angularSettled(angularSettled),
    m_swingPID(swingPID),
    m_swingSettled(swingSettled) {
    m_leftMotor->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    m_rightMotor->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void Chassis::tankControl(float left, float right) {
    m_leftMotor->move(left);
    m_rightMotor->move(right);
}

void Chassis::arcadeControl(float throttle, float turn) {
    float left = throttle + turn;
    float right = throttle - turn;

    float mag = std::max(std::abs(left), std::abs(right)) / 127;

    if (mag > 1) {
        left /= mag;
        right /= mag;
    }

    tankControl(left, right);
}

void Chassis::brakeMotors() {
    m_leftMotor->brake();
    m_rightMotor->brake();
}

void Chassis::setHeading(float heading) {
    m_imu.set_rotation(heading);
}

static float shortenPath(float error) {
    return std::remainder(error, 360);
}

static float capSpeed(float speed, float maxSpeed) {
    return std::signbit(speed) * std::min(std::abs(speed), maxSpeed);
}

void Chassis::turn(float targetHeading, float maxSpeed) {
    m_angularPID->reset();
    m_angularSettled.reset();

    while (!m_angularSettled->isSettled()) {
        float error = shortenPath(targetHeading - m_imu.get_rotation());

        float output = capSpeed(m_angularPID->update(error), maxSpeed);

        arcadeControl(0, output);
    }
    
    brakeMotors();
}

void Chassis::swing(float targetHeading, SwingType swingType, float maxSpeed) {
    m_swingPID->reset();
    m_swingSettled.reset();

    if (swingType == SwingType::LeftSwing) {
        m_rightMotor->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        m_rightMotor->brake();
    } else {
        m_leftMotor->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        m_leftMotor->brake();
    }

    while (!m_angularSettled->isSettled()) {
        float error = shortenPath(targetHeading - m_imu.get_rotation());

        float output = capSpeed(m_swingPID->update(error), maxSpeed);

        if (swingType == SwingType::LeftSwing) {
            tankControl(output, 0);
        } else {
            tankControl(0, output);
        }
    }
    
    if (swingType == SwingType::LeftSwing) {
        m_leftMotor->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        m_leftMotor->brake();
    } else {
        m_rightMotor->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        m_rightMotor->brake();
    }
}

void Chassis::move(float targetDistance, float maxSpeed) {
    m_lateralPID->reset();
    m_lateralSettled.reset();

    m_leftMotor->tare_position_all();
    m_rightMotor->tare_position_all();

    while (!m_lateralSettled->isSettled()) {
        float error = (m_leftMotor->get_position(0) + m_rightMotor->get_position(0)) / 2 * m_gearRatio * m_wheelDiameter * M_PI;

        float output = capSpeed(m_lateralPID->update(error), maxSpeed);
        
        arcadeControl(output, 0);
    }

    brakeMotors();
}