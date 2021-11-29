#include "src/pins.h"

#include <IRremote.h>
#include <Servo.h>

constexpr uint32_t rudderCentreCommand{ 0x00FF02FDU };
constexpr uint32_t rudderPortCommand{ 0x00FF22DDU };
constexpr uint32_t rudderStarboardCommand{ 0x00FFC23DU };
constexpr uint32_t throttleDecreaseCommand{ 0x00FFA857U };
constexpr uint32_t throttleIncreaseCommand{ 0x00FF629DU };

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
    case rudderCentreCommand:
      s_rudder.write(rudderCentre);
      break;

    case rudderPortCommand:
      s_rudder.write(s_rudder.read() + rudderStep);
      break;

    case rudderStarboardCommand:
      s_rudder.write(s_rudder.read() - rudderStep);
      break;

    case throttleDecreaseCommand:
      analogWrite(pins::motorThrottle, analogRead(pins::motorThrottle) - throttleStep);
      break;

    case throttleIncreaseCommand:
      analogWrite(pins::motorThrottle, analogRead(pins::motorThrottle) + throttleStep);
      break;
    }

    IrReceiver.resume();
  }

  delay(loopDelay);
}
