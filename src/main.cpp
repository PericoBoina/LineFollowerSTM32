#include <Arduino.h>
#include "Mux4051.h"

Mux4051 mux(PA0, PA1, PA2, PA3);

void setup()
{
  pinMode(PA0, OUTPUT);
  pinMode(PA1, OUTPUT);
  pinMode(PA2, OUTPUT);
  pinMode(PA3, INPUT);
  pinMode(PC13, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  Serial.println("Hola Currito");
  digitalWrite(PC13, 1);
  delay(250);
  digitalWrite(PC13, 0);
  delay(250);
};
