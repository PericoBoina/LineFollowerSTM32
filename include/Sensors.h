#ifndef SENSORS_H
#define SENSORS_H

#define pinA PA0      // Pin A para multiplexor
#define pinB PA1      // Pin B para multiplexor
#define pinC PA2      // Pin C para multiplexor
#define analogPin PA3 // Pin analógico de entrada para los sensores

class Sensors
{
public:
    Sensors();                           // Constructor
    void begin();                        // Configura los pines
    void update();                       // Actualiza las lecturas
    int getSensorValue(int sensorIndex); // Obtiene el valor de un sensor específico
    void calibracion(int numLecturas);   // Función de calibración
    int posicionLinea();                 // Obtiene la posición de la línea
    void LineType(bool colorLine);  // Establece el tipo de línea (blanca o negra)

private:
    int sensorValues[8];                  // Arreglo de 8 sensores
    int umbral[8];                        // Arreglo de umbrales
    unsigned long lastReadTime;           // Última vez que se leyó
    const unsigned long readInterval = 1; // Intervalo de lectura
    const int numSensors = 8;             // Número de sensores
    void selectChannel(int channel);      // Selecciona el canal en el multiplexor
    bool colorLine = false;             // Determina si la línea es blanca (1) o negra (0)
};

#endif
