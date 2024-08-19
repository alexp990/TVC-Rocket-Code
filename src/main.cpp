// just testing

#include <Arduino.h>
#include "Rocket.h"

/*MPU mpu;
Kalman kalmanX; 
Kalman kalmanY;
uint32_t timer;

void setup() {
    Serial.begin(9600);

    Serial.println("MPU6050 Initialized!");

    delay(100);

    timer = micros();
}

void loop() {

    double dt = (double)(micros() - timer) / 1000000; 
    timer = micros();
    Vector3 accel = mpu.getAcceleration();
    Vector3 gyro = mpu.getGyros();

    double gyroXrate = gyro.x / 131.0;
    double gyroYrate = gyro.y / 131.0;s

    float roll = mpu.getRoll();
    float pitch = mpu.getPitch();
    float yaw = mpu.getYaw();

    double kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt);
    double kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt);

    Serial.print(gyro.x); 
    Serial.print(",");
    Serial.print(gyro.y); 
    Serial.print(",");
    Serial.println(gyro.z); 

    delay(0); 
}
*/


void setup() {
    Serial.begin(9600);
    Serial.print("initialised");
}

Rocket rocket;  

void loop() {

    rocket.updateSensors();
    

    /*Serial.print("Temperature: ");
    Serial.print(rocket.temperature);
    Serial.print(" C, Pressure: ");
    Serial.print(rocket.pressure);
    Serial.print(" hPa, Altitude: ");
    Serial.print(rocket.altitude);
    Serial.println(" m");
    */

    delay(10); 
}
