#ifndef PINS_H
#define PINS_H

#include <stdint.h>

namespace pins
{
  inline constexpr uint8_t irReceiver{ 3 };
  inline constexpr uint8_t motorForward{ 6 };
  inline constexpr uint8_t motorReverse{ 7 };
  inline constexpr uint8_t motorThrottle{ 5 };
  inline constexpr uint8_t servo{ 9 };
}

#endif
