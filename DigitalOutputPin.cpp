#if __has_include(<McuLogger.h>)
#include <McuLogger.h>
#else
#define LOG_DEBUG(fmt, ...)
#endif

#if __has_include(<Arduino.h>)
#include <Arduino.h>
#elif __has_include(<driver/gpio.h>)
#include "driver/gpio.h"

enum PinMode
{
    INPUT = GPIO_MODE_INPUT,
    OUTPUT = GPIO_MODE_OUTPUT
};

void pinMode(uint8_t pin, PinMode mode)
{
    gpio_config_t gpioAttributes;
    // gpioAttributes.pin_bit_mask = (1ULL << pin);
    gpioAttributes.mode = mode == INPUT ? GPIO_MODE_INPUT : GPIO_MODE_OUTPUT;
    gpioAttributes.pull_up_en = GPIO_PULLUP_DISABLE;
    gpioAttributes.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpioAttributes.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpioAttributes);
}

void digitalWrite(uint8_t pin, bool level)
{
    gpio_set_level(static_cast<gpio_num_t>(pin), level ? 1 : 0);
}
#endif

#include "DigitalOutputPin.h"

/**
 * @brief Construct a new Digital Output Pin:: Digital Output Pin object
 * 
 * @param pinNumber The pin number to be controlled.
 * @param invertLogic 
 */
DigitalOutputPin::DigitalOutputPin(const uint8_t pinNumber, const bool invertLogic) 
    : m_pinNumber(pinNumber), m_invertLogic(invertLogic)
{
    LOG_DEBUG("Created DigitalOutputPin (pinNumber: %u, invertLogic: %s).", pinNumber, invertLogic ? "true" : "false");
    pinMode(m_pinNumber, OUTPUT);
    off();
}

/**
 * @brief Turns the pin on.
 * 
 */
void DigitalOutputPin::on()
{
    LOG_DEBUG("Turning pin #%u on!", m_pinNumber);
    m_currentState = true;
    digitalWrite(m_pinNumber, !m_invertLogic);
}

/**
 * @brief Turns the pin off.
 * 
 */
void DigitalOutputPin::off()
{
    LOG_DEBUG("Turning pin #%u off!", m_pinNumber);
    digitalWrite(m_pinNumber, m_invertLogic);
    m_currentState = false;
}

/**
 * @brief Toggles the relay (i.e. turns it off if it's currently on and turns it on if it's currently off)
 * 
 */
void DigitalOutputPin::toggle()
{
    bool nextState = (m_currentState == m_invertLogic);
    LOG_DEBUG("Toggling pin #%u %s!", m_pinNumber, !m_currentState ? "on" : "off");
    digitalWrite(m_pinNumber, nextState);
    m_currentState = !m_currentState;
}