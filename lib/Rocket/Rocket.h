#ifndef ROCKET_H
#define ROCKET_H

#include "Vector3.h"
#include <Wire.h>
#include <Arduino.h>
//#include <Servo.h>
#include "MPU.h"
//#include "BMP.h"
#include "PID.h"
//#include "SDCard.h"
#include "Vector3.h"

#define DEG2RAD 0.01745329251f      // Convert degrees to radians
#define RAD2DEG 57.2957795131f      // Convert radians to degrees

#define SEA_LEVEL_PRESSURE 1013.25  // Sea level pressure (hPa)

class Rocket {
public:
    Rocket();

    //SDCard sdCard;

    // Angular velocity (rad/s)
    Vector3 gyros;
    // Acceleration (m/s^2)
    Vector3 acceleration;
    // Absolute orientation (degrees)
    Quaternion orientation;

    Vector3 euler;

    float flightTime = 0.0f;        // Flight time (s)
    float flightStartTime = 0.0f;   // Start time of flight (ms)
    
    float altitude;                 // Altitude (meters)
    float pressure;                 // Pressure (hPa)
    float temperature;              // Temperature (Celsius)

    //just filler functions

    void padIdle();
    void ascent();
    void maxApogee();
    void descent();
    void landed();

    void updateSensors();           // Update sensor data
    void controlServos();           // Control servos based on orientation
    void deployParachute();

private:
    MPU mpu6050;                // MPU6050 instance
    //BMP bmp;                        // BMP sensor instance
    
    unsigned long currentTime = 0.0;
    unsigned long previousTime = 0.0;
    float deltaTime = 0.0f;

    PID yPID = PID(0.6f, 0.05f, 0.125f, 10.0f);
    // PID-Controller for calculation of motor mount orientation on z-axis
    PID zPID = PID(0.6f, 0.05f, 0.125f, 10.0f);

};

#endif
