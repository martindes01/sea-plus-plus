#include <IRremote.h>

constexpr uint8_t irReceiverPin{ 3 };

constexpr unsigned long baudRate{ 9600UL };
constexpr unsigned long loopDelay{ 50UL };

void setup()
{
  Serial.begin(baudRate);

  IrReceiver.begin(irReceiverPin, ENABLE_LED_FEEDBACK);
}

void loop()
{
  if (IrReceiver.decode())
  {
    IrReceiver.printIRResultShort(&Serial);

    IrReceiver.resume();
  }

  delay(loopDelay);
}
