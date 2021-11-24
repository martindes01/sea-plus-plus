#include <IRremote.h>
#include <Servo.h>

constexpr uint8_t irReceiverPin{ 3 };
constexpr uint8_t servoPin{ 9 };

constexpr uint32_t rudderCentreCommand{ 0x00FF02FDU };
constexpr uint32_t rudderPortCommand{ 0x00FF22DDU };
constexpr uint32_t rudderStarboardCommand{ 0x00FFC23DU };
constexpr uint32_t throttleDecreaseCommand{ 0x00FFA857U };
constexpr uint32_t throttleIncreaseCommand{ 0x00FF629DU };

constexpr unsigned long loopDelay{ 50UL };
constexpr int rudderCentre{ 90 };
constexpr int rudderStep{ 5 };

static Servo s_rudder{};

void setup()
{
  IrReceiver.begin(irReceiverPin, ENABLE_LED_FEEDBACK);

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
      break;

    case throttleIncreaseCommand:
      break;
    }

    IrReceiver.resume();
  }

  delay(loopDelay);
}
