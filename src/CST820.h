// CST820.h
#ifndef CST820_H
#define CST820_H

#include <Wire.h>

class CST820
{
public:
    CST820(uint8_t sda, uint8_t scl, uint32_t frecuencia); // Constructor
    void begin(uint16_t ancho = 320, uint16_t alto = 240); // Inicializa el puerto I2C
    void setRotation(uint8_t rotacion);                    // Rotacion del táctil
    bool isPressed();                                      // Método para leer el estado táctil
    void getCoordinates(uint16_t &outX, uint16_t &outY);   // Método para obtener las coordenadas X e Y

private:
    const uint8_t _ADDR_TOUCH = 0x15; // Dirección I2C del CST820
    uint8_t _sda, _scl;               // Pines del bus I2C
    uint8_t _rotacion;                // Orientacion de la pantalla
    uint16_t _x, _y;                  // Coordenadas de la detección del táctil
    uint16_t _ancho, _alto;           // Resolución de la pantalla en píxeles
    uint32_t _frecuencia;             // Frecuencia del bus I2C
};

#endif
