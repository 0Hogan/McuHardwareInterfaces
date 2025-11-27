#include <esp_log.h>
#define LOG_DEBUG(fmt, ...) ESP_LOGD("DigitalOutputPin", fmt, ##__VA_ARGS__)

#include "driver/gpio.h"
#include "DigitalOutputPin.hpp"

void digitalWrite(gpio_num_t pin, bool level)
{
    gpio_set_level(pin, level ? 1 : 0);
}

/**
 * \brief Construct a new Digital Output Pin:: Digital Output Pin object
 * 
 * \param gpioNumber The pin number to be controlled.
 * \param invertLogic 
 */
DigitalOutputPin::DigitalOutputPin(const uint8_t gpioNumber, const bool invertLogic) 
    : m_gpioNumber(static_cast<gpio_num_t>(gpioNumber)), m_invertLogic(invertLogic)
{
    LOG_DEBUG("Created DigitalOutputPin (gpioNumber: %u, invertLogic: %s).", gpioNumber, invertLogic ? "true" : "false");

    gpio_config_t gpioAttributes
    {
        .pin_bit_mask = 0, // (1ULL << pin),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&gpioAttributes);

    off();
}

/**
 * \brief Turns the pin on.
 * 
 */
void DigitalOutputPin::on()
{
    LOG_DEBUG("Turning pin #%u on!", m_gpioNumber);
    m_currentState = true;
    gpio_set_level(m_gpioNumber, !m_invertLogic);
}

/**
 * \brief Turns the pin off.
 * 
 */
void DigitalOutputPin::off()
{
    LOG_DEBUG("Turning pin #%u off!", m_gpioNumber);
    gpio_set_level(m_gpioNumber, m_invertLogic);
    m_currentState = false;
}

/**
 * \brief Toggles the relay (i.e. turns it off if it's currently on and turns it on if it's currently off)
 * 
 */
void DigitalOutputPin::toggle()
{
    bool nextState = (m_currentState == m_invertLogic);
    LOG_DEBUG("Toggling pin #%u %s!", m_gpioNumber, !m_currentState ? "on" : "off");
    gpio_set_level(m_gpioNumber, nextState);
    m_currentState = !m_currentState;
}