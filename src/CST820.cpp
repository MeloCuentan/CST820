#include "L_CST820.h"

// Constructor
CST820::CST820(uint8_t sda, uint8_t scl, uint32_t frecuencia)
{
    _sda = sda;
    _scl = scl;
    _frecuencia = frecuencia;
    _x = 0;
    _y = 0;
    _rotacion = 0;
}

// Inicializa el puerto I2C
void CST820::begin(uint16_t ancho, uint16_t alto)
{
    Wire.begin(_sda, _scl, _frecuencia);
    _ancho = ancho;
    _alto = alto;
}

// Establecer orientacion de la pantalla
void CST820::setRotation(uint8_t rotacion) {
  if (rotacion > 3) return;
  _rotacion = rotacion;
}

// Método para leer el estado táctil
bool CST820::isPressed()
{
    static const uint8_t bytes = 7;
    Wire.beginTransmission(_ADDR_TOUCH);
    Wire.write(0x00);

    if (Wire.endTransmission(false) != 0)
        return false;

    Wire.requestFrom((int)_ADDR_TOUCH, (int)bytes);
    if (Wire.available() != bytes)
        return false;

    uint8_t data[bytes];
    for (uint8_t i = 0; i < bytes; i++)
    {
        data[i] = Wire.read(); // Guardamos valores leídos
    }

    if (data[2] == 0x01)
    {                                  // Si se ha detectado una pulsación
        _x = (data[5] << 8) | data[6];
        _y = 240 - data[4];
        return true;
    }
    return false;
}

// Método para obtener las coordenadas X e Y
void CST820::getCoordinates(uint16_t &outX, uint16_t &outY)
{
    switch (_rotacion)
    {
    case 0:
        outX = _alto - _y;
        outY = _x;
        break;
    case 1:
        outX = _x;
        outY = _y;
        break;
    case 2:
        outX = _y;
        outY = _ancho - _x;
        break;
    case 3:
        outX = _ancho - _x;
        outY = _alto - _y;
        break;
    }
}
