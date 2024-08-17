#ifndef MPU6050_H
#define MPU6050_H

#include <Wire.h>
#include <Arduino.h>
#include "KalmanFilter.h"
#include "Quaternion.h"
#include <Adafruit_Sensor.h>
#include "Vector3.h" // Including the pre-made Vector3 class

class MPU6050 {
public:
    MPU6050();
    void initialize();
    Vector3 getGyros();
    Vector3 getAcceleration();
    Quaternion getOrientation();

private:
    void readMPU6050Data();
    int16_t accelX, accelY, accelZ;
    int16_t gyroX, gyroY, gyroZ;
    double accelScale = 16384.0;
    double gyroScale = 131.0;
};

#endif
