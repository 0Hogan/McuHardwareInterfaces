
#ifndef DIGITAL_OUTPUT_PIN_H
#define DIGITAL_OUTPUT_PIN_H

#include <cstdint>
#include <driver/gpio.h>

class DigitalOutputPin
{
  public:
    DigitalOutputPin(const uint8_t gpioNumber, const bool invertLogic=false);

    void on();
    void off();
    void toggle();
    
    /**
     * @brief Get the current state of the relay.
     * 
     * @returns True if the relay is on, false otherwise.
     */
    bool getState() const { return m_currentState; };

    /**
     * @brief Get the GPIO number.
     * 
     * @returns uint8_t The GPIO number.
     */
    uint8_t getGpioNumber() const { return static_cast<uint8_t>(m_gpioNumber); }

  private:
    gpio_num_t m_gpioNumber; ///< The number of the pin used to control the relay.
    bool m_invertLogic; ///< Whether the pin is "on" when the pin is set to "high"
    bool m_currentState; ///< Whether the pin is currently "on".
};

#endif // DIGITAL_OUTPUT_PIN_H