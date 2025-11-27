#include <cstdint>

#ifndef DIGITAL_OUTPUT_PIN_H
#define DIGITAL_OUTPUT_PIN_H

class DigitalOutputPin
{
  public:
    DigitalOutputPin(const uint8_t pinNumber, const bool invertLogic=false);

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
     * @brief Get the pin number.
     * 
     * @returns uint8_t The pin number.
     */
    uint8_t getPinNumber() const { return m_pinNumber; }

  private:
    uint8_t m_pinNumber; ///< The number of the pin used to control the relay.
    bool m_invertLogic; ///< Whether the pin is "on" when the pin is set to "high"
    bool m_currentState; ///< Whether the pin is currently "on".
};

#endif // DIGITAL_OUTPUT_PIN_H