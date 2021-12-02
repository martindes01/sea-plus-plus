#include "src/commands.h"
#include "src/motor.h"
#include "src/pins.h"
#include "src/rudder.h"

#include <IRremote.h>

constexpr unsigned long loopDelay{ 50UL };

static control::Motor s_motor{ pins::motorForward, pins::motorReverse, pins::motorThrottle };

static control::Rudder s_rudder{ pins::servo };

void setup()
{
  IrReceiver.begin(pins::irReceiver, ENABLE_LED_FEEDBACK);

  s_motor.setup();

  s_rudder.setup();
}

void loop()
{
  if (IrReceiver.decode())
  {
    switch (IrReceiver.decodedIRData.decodedRawData)
    {
    case commands::rudderCentre:
      s_rudder.centre();
      break;

    case commands::rudderPort:
      s_rudder.turnToPort();
      break;

    case commands::rudderStarboard:
      s_rudder.turnToStarboard();
      break;

    case commands::throttleDecrease:
      s_motor.decreaseSpeed();
      break;

    case commands::throttleIncrease:
      s_motor.increaseSpeed();
      break;
    }

    IrReceiver.resume();
  }

  delay(loopDelay);
}
