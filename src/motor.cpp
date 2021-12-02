#include "motor.h"

#include "arduino.h"

namespace control
{
  constexpr int throttleStep{ 64 };

  void Motor::setup() const
  {
    pinMode(m_forwardPin, OUTPUT);
    pinMode(m_reversePin, OUTPUT);
    pinMode(m_throttlePin, OUTPUT);

    digitalWrite(m_forwardPin, HIGH);
    digitalWrite(m_reversePin, LOW);
    stop();
  }

  void Motor::reset() const
  {
    stop();
    digitalWrite(m_reversePin, LOW);
    digitalWrite(m_forwardPin, LOW);

    pinMode(m_throttlePin, INPUT);
    pinMode(m_reversePin, INPUT);
    pinMode(m_forwardPin, INPUT);
  }

  void Motor::decreaseSpeed() const
  {
    analogWrite(m_throttlePin, analogRead(m_throttlePin) - throttleStep);
  }

  void Motor::increaseSpeed() const
  {
    analogWrite(m_throttlePin, analogRead(m_throttlePin) + throttleStep);
  }

  void Motor::fullSpeed() const
  {
    digitalWrite(m_throttlePin, HIGH);
  }

  void Motor::stop() const
  {
    digitalWrite(m_throttlePin, LOW);
  }
}
