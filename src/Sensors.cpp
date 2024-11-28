#include "Sensors.h"
#include <Arduino.h>

Sensors::Sensors() : lastReadTime(0), readInterval(1) {
    // Constructor
}

void Sensors::begin() {
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinC, OUTPUT);
    pinMode(pinZ, INPUT);
}

void Sensors::update()
{
    unsigned long currentMillis = millis();
    if (currentMillis - lastReadTime >= readInterval)
    {
        lastReadTime = currentMillis;
        for (int i = 0; i < numSensors; i++)
        {
            selectChannel(i);
            sensorValues[i] = analogRead(pinZ);
        }
    }
}

int Sensors::getSensorValue(int sensorIndex)
{
    if (sensorIndex >= 0 && sensorIndex < numSensors)
    {
        return sensorValues[sensorIndex];
    }
    return -1;
}

void Sensors::selectChannel(int channel)
{
    digitalWrite(pinA, channel & 0x01);
    digitalWrite(pinB, (channel >> 1) & 0x01);
    digitalWrite(pinC, (channel >> 2) & 0x01);
}

void Sensors::calibracion(int numLecturas)
{
    int sumaLecturasBlanco[8] = {0};
    int promedioBlanco[8];
    int sumaLecturasNegro[8] = {0};
    int promedioNegro[8];
    Serial1.println("Poner en blanco");
    delay(5000);
    Serial1.println("Iniciando calibración para blanco...");
    // Tomar 'numLecturas' lecturas para el blanco
    for (int x = 0; x < numLecturas; x++)
    {
        update();
        Serial1.print("Lectura ");
        Serial1.print(x + 1);
        Serial1.print(" para blanco: ");
        for (int i = 0; i < numSensors; i++)
        {
            int valor = getSensorValue(i);
            sumaLecturasBlanco[i] += valor;
            Serial1.print(valor);
            Serial1.print("\t");
        }
        Serial1.println();
    }
    // Calcular el promedio de las lecturas de blanco
    for (int i = 0; i < numSensors; i++)
    {
        promedioBlanco[i] = sumaLecturasBlanco[i] / numLecturas;
    }
    Serial1.println("Poner en negro...");
    delay(5000);
    Serial1.println("Iniciando calibración para negro...");
    // Tomar 'numLecturas' lecturas para el negro
    for (int x = 0; x < numLecturas; x++)
    {
        update();
        Serial1.print("Lectura ");
        Serial1.print(x + 1);
        Serial1.print(" para negro: ");
        for (int i = 0; i < numSensors; i++)
        {
            int valor = getSensorValue(i);
            sumaLecturasNegro[i] += valor;
            Serial1.print(valor);
            Serial1.print("\t");
        }
        Serial1.println();
    }
    // Calcular el promedio de las lecturas de negro
    for (int i = 0; i < numSensors; i++)
    {
        promedioNegro[i] = sumaLecturasNegro[i] / numLecturas;
        umbral[i] = (promedioBlanco[i] + promedioNegro[i]) / 2; // Umbral calculado
    }
    // Imprimir datos de calibración
    Serial1.println("Sensor\tPromedio Blanco\tPromedio Negro\tUmbral");
    for (int i = 0; i < numSensors; i++)
    {
        Serial1.printf("%-8d%-18d%-16d%-8d\n", i + 1, promedioBlanco[i], promedioNegro[i], umbral[i]);
    }
    Serial1.println("¡Calibración Terminada!");
}

void Sensors::LineType(bool colorLine) {
    this->colorLine = colorLine;  
}

int Sensors::posicionLinea()
{
    update();
    int sumaTotal = 0;
    int sumapTotal = 0;
    for (int i = 0; i < 8; i++)
    {
        int valorUmbral;
        if (colorLine)
        {
            valorUmbral = (sensorValues[i] < umbral[i]) ? 1 : 0; // Blanco sobre fondo negro
        }
        else
        {
            valorUmbral = (sensorValues[i] > umbral[i]) ? 1 : 0; // Negro sobre fondo blanco
        }
        sumapTotal += valorUmbral * i;
        sumaTotal += valorUmbral;
    }
    if (sumaTotal > 0)
    {
        int posicion = map(sumapTotal, 0, sumaTotal * 7, 100, 800);
        posicion = constrain(posicion, 100, 800);
        return posicion;
    }
    else
    {
        Serial1.println("No se detectó línea");
        return -1;
    }
}
