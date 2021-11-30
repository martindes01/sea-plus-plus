#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdint.h>

namespace commands
{
  inline constexpr uint32_t rudderCentre{ 0x00FF02FDU };
  inline constexpr uint32_t rudderPort{ 0x00FF22DDU };
  inline constexpr uint32_t rudderStarboard{ 0x00FFC23DU };
  inline constexpr uint32_t throttleDecrease{ 0x00FFA857U };
  inline constexpr uint32_t throttleIncrease{ 0x00FF629DU };
}

#endif
