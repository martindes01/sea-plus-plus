#include <IRremote.h>

constexpr uint8_t irReceiverPin{ 3 };

constexpr uint32_t rudderCentreCommand{ 0x00FF02FDU };
constexpr uint32_t rudderPortCommand{ 0x00FF22DDU };
constexpr uint32_t rudderStarboardCommand{ 0x00FFC23DU };
constexpr uint32_t throttleDecreaseCommand{ 0x00FFA857U };
constexpr uint32_t throttleIncreaseCommand{ 0x00FF629DU };

constexpr unsigned long loopDelay{ 50UL };

void setup()
{
  IrReceiver.begin(irReceiverPin, ENABLE_LED_FEEDBACK);
}

void loop()
{
  if (IrReceiver.decode())
  {
    switch (IrReceiver.decodedIRData.decodedRawData)
    {
    case rudderCentreCommand:
      break;

    case rudderPortCommand:
      break;

    case rudderStarboardCommand:
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
