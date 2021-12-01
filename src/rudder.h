#ifndef RUDDER_H
#define RUDDER_H

#include <Servo.h>

#include <stdint.h>

namespace control
{
  class Rudder
  {
  private:
    uint8_t m_pin{};
    Servo m_servo{};

  public:
    Rudder(const uint8_t pin) : m_pin{ pin } {}

    ~Rudder()
    {
      reset();
    }

    void setup();

    void reset();

    void centre();

    void turnToPort();

    void turnToStarboard();
  };
}

#endif
