#include "MPU6050.h"

MPU6050::MPU6050() {
    Wire.begin();
    Wire.setClock(400000);
}

void MPU6050::initialize() {
    Wire.beginTransmission(0x68); // Address of MPU6050
    Wire.write(0x6B);  // Power management register
    Wire.write(0x00);  // Wake up MPU6050
    Wire.endTransmission(true);
}

void MPU6050::readMPU6050Data() {
    Wire.beginTransmission(0x68);
    Wire.write(0x3B);  // Starting register for Accel Readings
    Wire.endTransmission(false);
    Wire.requestFrom(0x68, 14, true);

    accelX = (Wire.read() << 8 | Wire.read());
    accelY = (Wire.read() << 8 | Wire.read());
    accelZ = (Wire.read() << 8 | Wire.read());
    Wire.read(); // Temperature data
    Wire.read();
    gyroX = (Wire.read() << 8 | Wire.read());
    gyroY = (Wire.read() << 8 | Wire.read());
    gyroZ = (Wire.read() << 8 | Wire.read());
}

Vector3 MPU6050::getGyros() {
    readMPU6050Data();
    Vector3 gyro(
        KALMAN(gyroX / gyroScale),
        KALMAN(gyroY / gyroScale),
        KALMAN(gyroZ / gyroScale)
    );
    return gyro;
}

Vector3 MPU6050::getAcceleration() {
    readMPU6050Data();
    Vector3 accel(
        KALMAN(accelX / accelScale),
        KALMAN(accelY / accelScale),
        KALMAN(accelZ / accelScale)
    );
    return accel;
}

Quaternion MPU6050::getOrientation() {
    // Perform sensor fusion with quaternions using accel and gyro data
    Vector3 gyro = getGyros();
    Quaternion orientation = Quaternion::fromEuler(gyro.x, gyro.y, gyro.z);
    return orientation;
}
