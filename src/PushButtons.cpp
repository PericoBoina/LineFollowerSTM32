#include <Arduino.h>
#include "PushButtons.h"

buttons::buttons(uint8_t pin1, uint8_t pin2)
    : _pin1(pin1), _pin2(pin2), _lastState1(false), _lastState2(false) {}

void buttons::begin()
{
    pinMode(_pin1, INPUT_PULLDOWN);
    pinMode(_pin2, INPUT_PULLDOWN);
}

bool buttons::isPressed1()
{
    bool currentState = !digitalRead(_pin1);
    bool pressed = currentState && !_lastState1;
    _lastState1 = currentState;
    return pressed;
}

bool buttons::isPressed2()
{
    bool currentState = !digitalRead(_pin2);
    bool pressed = currentState && !_lastState2;
    _lastState2 = currentState;
    return pressed;
}
