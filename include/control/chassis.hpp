#pragma once

#include "pros/imu.hpp"
#include "pros/motor_group.hpp"


#include "control/pid.hpp"
#include "control/pidSettled.hpp"

#include <memory>

enum SwingType { LeftSwing, RightSwing };

class Chassis {
public:
  Chassis(std::shared_ptr<pros::MotorGroup> leftMotor,
          std::shared_ptr<pros::MotorGroup> rightMotor, const pros::IMU &imu,
          float wheelDiameter, float gearRatio, std::shared_ptr<PID> lateralPID,
          std::shared_ptr<PIDSettled> lateralSettled,
          std::shared_ptr<PID> angularPID,
          std::shared_ptr<PIDSettled> angularSettled,
          std::shared_ptr<PID> swingPID,
          std::shared_ptr<PIDSettled> swingSettled,
          float slew);
  
  void tankControl(float left, float right);

  void arcadeControl(float throttle, float turn);

  void brakeMotors();

  void initialize();

  void setHeading(float heading);

  void turn(float targetHeading, float maxSpeed = 127);

  void swing(float targetHeading, SwingType swingType, float maxSpeed = 127);

  void move(float targetDistance, float maxSpeed = 127);

private:
  std::shared_ptr<pros::MotorGroup> m_leftMotors;
  std::shared_ptr<pros::MotorGroup> m_rightMotors;

  pros::IMU m_imu;

  float m_wheelDiameter;
  float m_gearRatio;

  std::shared_ptr<PID> m_lateralPID;
  std::shared_ptr<PIDSettled> m_lateralSettled;

  std::shared_ptr<PID> m_angularPID;
  std::shared_ptr<PIDSettled> m_angularSettled;

  std::shared_ptr<PID> m_swingPID;
  std::shared_ptr<PIDSettled> m_swingSettled;

  float m_slew;
};