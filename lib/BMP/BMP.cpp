#include "BMP.h"

#define SEALEVELPRESSURE_HPA (1013.25)

BMP::BMP() {
    // Constructor
}

bool BMP::begin() {
    if (!bmp.begin_I2C()) { 
        Serial.println("ERROR: Stupid BMP388 initialization failed!");
        return false;
    }

    // Set up oversampling and filter
    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X); 
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X); 
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3); 
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);
    
    return true;
}

float BMP::readTemperature() {
    return bmp.readTemperature();
}

float BMP::readPressure() {
    return bmp.readPressure();
}

float BMP::readAltitude(float seaLevelhPa) {
    return bmp.readAltitude(seaLevelhPa);
}