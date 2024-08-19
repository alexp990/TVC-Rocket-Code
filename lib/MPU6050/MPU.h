#ifndef MPU_H
#define MPU_H

#include <Wire.h>
#include <Arduino.h>
#include "KalmanFilter.h"
#include "Quaternion.h"
#include <Adafruit_Sensor.h>
#include "Vector3.h" 


class MPU {
public:
    MPU();
    void initialize();
    void readMPUData();
    Quaternion getQuaternion();
    Quaternion q;
    Vector3 getGyros();
    Vector3 getAcceleration();
    Quaternion getOrientation();
    double getRoll();
    double getPitch();
    double getYaw();

private:
    Kalman kalmanX;
    Kalman kalmanY;
    Kalman kalmanZ;
    double accelX, accelY, accelZ;
    double gyroX, gyroY, gyroZ;
    double gyroScale = 131.0;
    double accelScale = 16384.0;
    uint32_t timer;
    double kalAngleX = 0;
    double kalAngleY = 0;
    double kalAngleZ = 0;
    Quaternion orientation;
};

#endif
