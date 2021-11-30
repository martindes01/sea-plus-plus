#include "src/commands.h"
#include "src/pins.h"

#include <IRremote.h>
#include <Servo.h>

constexpr unsigned long loopDelay{ 50UL };
constexpr int rudderCentre{ 90 };
constexpr int rudderStep{ 5 };
constexpr int throttleStep{ 64 };

static Servo s_rudder{};

void setup()
{
  IrReceiver.begin(pins::irReceiver, ENABLE_LED_FEEDBACK);

  pinMode(pins::motorForward, OUTPUT);
  pinMode(pins::motorReverse, OUTPUT);
  pinMode(pins::motorThrottle, OUTPUT);

  digitalWrite(pins::motorForward, HIGH);
  digitalWrite(pins::motorReverse, LOW);
  digitalWrite(pins::motorThrottle, HIGH);

  s_rudder.attach(pins::servo);
  s_rudder.write(rudderCentre);
}

void loop()
{
  if (IrReceiver.decode())
  {
    switch (IrReceiver.decodedIRData.decodedRawData)
    {
    case commands::rudderCentre:
      s_rudder.write(rudderCentre);
      break;

    case commands::rudderPort:
      s_rudder.write(s_rudder.read() + rudderStep);
      break;

    case commands::rudderStarboard:
      s_rudder.write(s_rudder.read() - rudderStep);
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
