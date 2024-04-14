#include "control/chassis.hpp"

#include <cmath>

void Chassis::brakeMotors() {
    m_leftMotor->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    m_rightMotor->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    m_leftMotor->brake();
    m_rightMotor->brake();
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

void Chassis::turn(float targetHeading, float maxSpeed, AngularDirection direction) {
    m_angularPID->reset();
    m_angularSettled->reset();

    while (!m_angularSettled->isSettled()) {
        float error = getPath(targetHeading, m_imu.get_rotation(), direction);

        float output = capSpeed(m_angularPID->update(error), maxSpeed);

        arcadeControl(0, output);

        pros::delay(10);
    }
    
    brakeMotors();
}

void Chassis::swing(float targetHeading, SwingType swingType, float maxSpeed, AngularDirection direction) {
    m_swingPID->reset();
    m_swingSettled->reset();

    if (swingType == SwingType::LeftSwing) {
        m_rightMotor->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        m_rightMotor->brake();
    } else {
        m_leftMotor->set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        m_leftMotor->brake();
    }

    while (!m_angularSettled->isSettled()) {
        float error = getPath(targetHeading, m_imu.get_rotation(), direction);

        float output = capSpeed(m_swingPID->update(error), maxSpeed);

        if (swingType == SwingType::LeftSwing) {
            tankControl(output, 0);
        } else {
            tankControl(0, -output);
        }

        pros::delay(10);
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
    m_lateralSettled->reset();

    m_leftMotor->tare_position_all();
    m_rightMotor->tare_position_all();

    m_leftMotor->set_encoder_units(pros::MotorUnits::rotations);
    m_rightMotor->set_encoder_units(pros::MotorUnits::rotations);

    while (true) {
        float error = targetDistance - (m_leftMotor->get_position(0) + m_rightMotor->get_position(0)) / 2 * m_gearRatio * m_wheelDiameter * M_PI;

        float output = capSpeed(m_lateralPID->update(error), maxSpeed);
        
        arcadeControl(output, 0);

        pros::delay(10);
    }

    brakeMotors();
}