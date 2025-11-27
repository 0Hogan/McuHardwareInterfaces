#include <Log.h>
#include <McuHardwareInterfaces.hpp>

DigitalOutputPin pin1(13);

void setup()
{
    Serial.begin(115200);
    Logger::addOutputStream(&Serial);
}

void loop()
{
    pin1.toggle();
    delay(500);
}