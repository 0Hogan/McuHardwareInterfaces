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