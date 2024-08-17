#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>

#ifndef BMP_H
#define BMP_H

class BMP {
public:
    BMP();

    bool begin(); 
    float readTemperature();
    float readPressure();
    float readAltitude(float seaLevelhPa);

private:
    Adafruit_BMP3XX bmp; 
};

#endif 
