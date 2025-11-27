#ifndef MCU_HARDWARE_INTERFACES_H
#define MCU_HARDWARE_INTERFACES_H

#if defined(ESP_PLATFORM)
#include "../src/EspIdf/DigitalOutputPin.hpp"
#else // ESP_PLATFORM
#include "../src/Arduino/DigitalOutputPin.hpp"
#endif // ESP_PLATFORM
#endif // MCU_HARDWARE_INTERFACES_H
