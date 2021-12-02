#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

namespace control
{
  class Motor
  {
  private:
    uint8_t m_forwardPin{};
    uint8_t m_reversePin{};
    uint8_t m_throttlePin{};

  public:
    Motor(const uint8_t forwardPin, const uint8_t reversePin, const uint8_t throttlePin) : m_forwardPin{ forwardPin }, m_reversePin{ reversePin }, m_throttlePin{ throttlePin } {}

    ~Motor()
    {
      reset();
    }

    void setup() const;

    void reset() const;

    void decreaseSpeed() const;

    void increaseSpeed() const;

    void fullSpeed() const;

    void stop() const;
  };
}

#endif
