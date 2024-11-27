#include "Mux4051.h"
#include <Arduino.h>

Mux4051::Mux4051(uint8_t s0Pin, uint8_t s1Pin, uint8_t s2Pin, uint8_t analogPin)
    : _s0Pin(s0Pin), _s1Pin(s1Pin), _s2Pin(s2Pin), _analogPin(analogPin) {
    pinMode(_s0Pin, OUTPUT);
    pinMode(_s1Pin, OUTPUT);
    pinMode(_s2Pin, OUTPUT);
    digitalWrite(_s0Pin, LOW);
    digitalWrite(_s1Pin, LOW);
    digitalWrite(_s2Pin, LOW);
}

void Mux4051::setChannel(uint8_t channel)
{
    digitalWrite(_s0Pin, channel & 0x01);
    digitalWrite(_s1Pin, (channel >> 1) & 0x01);
    digitalWrite(_s2Pin, (channel >> 2) & 0x01);
}

void Mux4051::readAllChannels(int* resultsArray) {
    for (uint8_t channel = 0; channel < 8; channel++) {
        setChannel(channel);                  
        resultsArray[channel] = analogRead(_analogPin); 
    }
}

