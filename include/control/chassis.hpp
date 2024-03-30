#pragma once

#include "pros/abstract_motor.hpp"
#include "pros/imu.hpp"

#include "control/pid.hpp"
#include "control/pidSettled.hpp"
#include "pros/motors.h"

#include <memory>

enum SwingType {
    LeftSwing,
    RightSwing
};

class Chassis {
    public:
        Chassis(
            std::shared_ptr<pros::AbstractMotor> leftMotor, 
            std::shared_ptr<pros::AbstractMotor> rightMotor,
            const pros::IMU& imu,
            float wheelDiameter,
            float gearRatio,
            std::shared_ptr<PID> lateralPID,
            const PIDSettled& lateralSettled,
            std::shared_ptr<PID> angularPID,
            const PIDSettled& angularSettled,
            std::shared_ptr<PID> swingPID,
            const PIDSettled& swingSettled
        );

        void tankControl(float left, float right);

        void arcadeControl(float throttle, float turn);

        void brakeMotors();

        void setHeading(float heading);
        
        void turn(float targetHeading, float maxSpeed = 127);

        void swing(float targetHeading, SwingType swingType, float maxSpeed = 127);

        void move(float targetDistance, float maxSpeed = 127);
    private:
        std::shared_ptr<pros::AbstractMotor> m_leftMotor;
        std::shared_ptr<pros::AbstractMotor> m_rightMotor;

        pros::IMU m_imu;

        float m_wheelDiameter;
        float m_gearRatio;

        std::shared_ptr<PID> m_lateralPID;
        PIDSettled m_lateralSettled;

        std::shared_ptr<PID> m_angularPID;
        PIDSettled m_angularSettled;

        std::shared_ptr<PID> m_swingPID;
        PIDSettled m_swingSettled;
};