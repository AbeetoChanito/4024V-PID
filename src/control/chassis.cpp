#include "control/chassis.hpp"

Chassis::Chassis(std::shared_ptr<pros::MotorGroup> leftMotor,
                 std::shared_ptr<pros::MotorGroup> rightMotor,
                 const pros::IMU &imu, float wheelDiameter, float gearRatio,
                 std::shared_ptr<PID> lateralPID,
                 std::shared_ptr<PIDSettled> lateralSettled,
                 std::shared_ptr<PID> angularPID,
                 std::shared_ptr<PIDSettled> angularSettled,
                 std::shared_ptr<PID> swingPID,
                 std::shared_ptr<PIDSettled> swingSettled)
    : m_leftMotors(leftMotor), m_rightMotors(rightMotor), m_imu(imu),
      m_wheelDiameter(wheelDiameter), m_gearRatio(gearRatio),
      m_lateralPID(lateralPID), m_lateralSettled(lateralSettled),
      m_angularPID(angularPID), m_angularSettled(angularSettled),
      m_swingPID(swingPID), m_swingSettled(swingSettled) {}

void Chassis::tankControl(float left, float right) {
  m_leftMotors->move(left);
  m_rightMotors->move(right);
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