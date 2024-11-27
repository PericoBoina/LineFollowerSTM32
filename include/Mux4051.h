#ifndef MUX4051_H
#define MUX4051_H

#include <Arduino.h>

class Mux4051 {
public:
    Mux4051(uint8_t s0Pin, uint8_t s1Pin, uint8_t s2Pin, uint8_t analogPin);
    void begin();
    void readAllChannels(int* resultsArray);

private:
    uint8_t _s0Pin;      ///< Pin de selección S0
    uint8_t _s1Pin;      ///< Pin de selección S1
    uint8_t _s2Pin;      ///< Pin de selección S2
    uint8_t _analogPin;  ///< Pin analógico conectado al multiplexor
    void setChannel(uint8_t channel);
};

#endif // MUX4051_H
