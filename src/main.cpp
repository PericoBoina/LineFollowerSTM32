#include <Arduino.h>
#include "Sensors.h"

HardwareSerial Serial1(PA10, PA9);
Sensors sensors;

int pos_Line = 0;

void setup()
{
  pinMode(PC13, OUTPUT);
  Serial1.begin(115200);
  sensors.begin();
  sensors.calibracion(5);
  sensors.setLineType(1);
}

void loop()
{
  pos_Line = sensors.posicionLinea();
  Serial1.println(pos_Line);
  if (pos_Line < 400 || pos_Line > 500)
  {
    digitalWrite(13, HIGH);
  }
  else
  {
    digitalWrite(13, LOW);
  }
}
