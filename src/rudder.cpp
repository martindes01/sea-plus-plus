#include "rudder.h"

#include <Servo.h>

namespace control
{
  constexpr int centreAngle{ 90 };
  constexpr int stepAngle{ 5 };

  void Rudder::setup()
  {
    m_servo.attach(m_pin);
  }

  void Rudder::reset()
  {
    m_servo.detach();
  }

  void Rudder::centre()
  {
    m_servo.write(centreAngle);
  }

  void Rudder::turnToPort()
  {
    m_servo.write(m_servo.read() + stepAngle);
  }

  void Rudder::turnToStarboard()
  {
    m_servo.write(m_servo.read() - stepAngle);
  }
}
