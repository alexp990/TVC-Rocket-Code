//just testing
#include "Rocket.h"
MPU mpu;
uint32_t timer;
Kalman kalmanX;
Kalman kalmanY;

Rocket::Rocket() {
    //this will initialise all the sensors, data logging etc..
}

void Rocket::updateSensors() {

    Serial.begin(115200);
    
    // Convert gyro data to orientation using quaternions
    Quaternion orientation = mpu.getQuaternion();
    euler = orientation.toEuler();

    double dt = (double)(micros() - timer) / 1000000; 
    timer = micros();
    Vector3 accel = mpu.getAcceleration();
    Vector3 gyro = mpu.getGyros();

    double gyroXrate = gyro.x / 131.0;
    double gyroYrate = gyro.y / 131.0;

    double kalAngleX = kalmanX.getAngle(euler.x, gyroXrate, dt);
    double kalAngleY = kalmanY.getAngle(euler.y, gyroYrate, dt);

    float xPIDoutput = yPID.update(0, kalAngleX);
    float yPIDoutput = zPID.update(0, kalAngleY);

    // Convert the relative orientation in rad to deg
    //xPIDoutput = xPIDoutput * RAD2DEG;
    //yPIDoutput = yPIDoutput * RAD2DEG;




    /*
    Serial.print(orientation.w);
    Serial.print(",");
    Serial.print(orientation.x);
    Serial.print(",");
    Serial.print(orientation.y);
    Serial.print(",");
    Serial.println(orientation.z);
    */

    Serial.print("kalAngleX:"); 
    Serial.print(kalAngleX); 
    Serial.print(","); 

    Serial.print("kalAngleY:"); 
    Serial.print(kalAngleY); 
    Serial.print(","); 

    Serial.print("xPIDoutput:"); 
    Serial.print(xPIDoutput); 
    Serial.print(","); 

    Serial.print("yPIDoutput:"); 
    Serial.println(yPIDoutput);


    // Get sensor data from BMP 
    //temperature = bmp.readTemperature();
    //pressure = bmp.readPressure();
    //altitude = bmp.readAltitude(SEA_LEVEL_PRESSURE);
}

