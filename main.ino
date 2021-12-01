#include "src/commands.h"
#include "src/pins.h"
#include "src/rudder.h"

#include <IRremote.h>

constexpr unsigned long loopDelay{ 50UL };
constexpr int throttleStep{ 64 };

static control::Rudder s_rudder{ pins::servo };

void setup()
{
  IrReceiver.begin(pins::irReceiver, ENABLE_LED_FEEDBACK);

  pinMode(pins::motorForward, OUTPUT);
  pinMode(pins::motorReverse, OUTPUT);
  pinMode(pins::motorThrottle, OUTPUT);

  digitalWrite(pins::motorForward, HIGH);
  digitalWrite(pins::motorReverse, LOW);
  digitalWrite(pins::motorThrottle, HIGH);

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
      analogWrite(pins::motorThrottle, analogRead(pins::motorThrottle) - throttleStep);
      break;

    case commands::throttleIncrease:
      analogWrite(pins::motorThrottle, analogRead(pins::motorThrottle) + throttleStep);
      break;
    }

    IrReceiver.resume();
  }

  delay(loopDelay);
}
