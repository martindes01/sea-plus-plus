#include <IRremote.h>
#include <Servo.h>

constexpr uint8_t irReceiverPin{ 3 };
constexpr uint8_t motorForwardPin{ 6 };
constexpr uint8_t motorReversePin{ 7 };
constexpr uint8_t motorThrottlePin{ 5 };
constexpr uint8_t servoPin{ 9 };

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
  IrReceiver.begin(irReceiverPin, ENABLE_LED_FEEDBACK);

  pinMode(motorForwardPin, OUTPUT);
  pinMode(motorReversePin, OUTPUT);
  pinMode(motorThrottlePin, OUTPUT);

  digitalWrite(motorForwardPin, HIGH);
  digitalWrite(motorReversePin, LOW);
  digitalWrite(motorThrottlePin, HIGH);

  s_rudder.attach(servoPin);
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
      analogWrite(motorThrottlePin, analogRead(motorThrottlePin) - throttleStep);
      break;

    case throttleIncreaseCommand:
      analogWrite(motorThrottlePin, analogRead(motorThrottlePin) + throttleStep);
      break;
    }

    IrReceiver.resume();
  }

  delay(loopDelay);
}
