#ifndef PUSHBUTTONS_H
#define PUSHBUTTONS_h

#include <Arduino.h>

class buttons
{
public:
    buttons(uint8_t pin1, uint8_t pin2); // Constructor para inicializar los pines
    void begin();                          // Configuración inicial
    bool isPressed1();                     // Devuelve true si el botón 1 es presionado
    bool isPressed2();                     // Devuelve true si el botón 2 es presionado

private:
    uint8_t _pin1, _pin2;
    bool _lastState1, _lastState2;         // Almacena el estado anterior para detectar el cambio
};

#endif
