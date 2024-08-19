#include "MPU.h"

//half the stuff doesent work :)

// Initialize I2C communication and set the clock speed
MPU::MPU() {
    Wire.begin();
    Wire.setClock(400000);
}

// Reading data from MPU6050
void MPU::readMPUData() {
    Wire.beginTransmission(0x68);
    Wire.write(0x3B); 
    Wire.endTransmission(false);
    Wire.requestFrom(0x68, 14, true);

    accelX = (Wire.read() << 8 | Wire.read());
    accelY = (Wire.read() << 8 | Wire.read());
    accelZ = (Wire.read() << 8 | Wire.read());
    Wire.read(); // Skip Temperature data
    Wire.read();
    gyroX = (Wire.read() << 8 | Wire.read());
    gyroY = (Wire.read() << 8 | Wire.read());
    gyroZ = (Wire.read() << 8 | Wire.read());
}

// Get the filtered gyro data using Kalman filters
Vector3 MPU::getGyros() {
    readMPUData();
    
    double dt = (double)(micros() - timer) / 1000000; 
    timer = micros();

    double gyroXrate = gyroX / gyroScale;
    double gyroYrate = gyroY / gyroScale;
    double gyroZrate = gyroZ / gyroScale;

    // Kalman filter integration for GyroX and GyroY
    kalAngleX = kalmanX.getAngle(kalAngleX, gyroXrate, dt); 
    kalAngleY = kalmanY.getAngle(kalAngleY, gyroYrate, dt);
    kalAngleZ = kalmanZ.getAngle(kalAngleZ, gyroZrate, dt);

    Vector3 gyro(
        kalAngleX,
        kalAngleY,
        kalAngleZ
    );
    return gyro;
}

// Get the filtered acceleration data using Kalman filters
Vector3 MPU::getAcceleration() {
    readMPUData();

    // Using the Kalman filter for acceleration data
    double accelXFiltered = kalmanX.getAngle(accelX / accelScale, 0, 0);
    double accelYFiltered = kalmanY.getAngle(accelY / accelScale, 0, 0);
    double accelZFiltered = kalmanZ.getAngle(accelZ / accelScale, 0, 0);

    Vector3 accel(
        accelXFiltered,
        accelYFiltered,
        accelZFiltered
    );
    return accel;
}

// Get roll, pitch, and yaw angles
double MPU::getRoll() {
    Vector3 accel = getAcceleration();
    return atan2(accelY, accelZ) * RAD_TO_DEG;
}

double MPU::getPitch() {
    Vector3 accel = getAcceleration();
#ifdef RESTRICT_PITCH
    return atan(-accelX / sqrt(accelY * accelY + accelZ * accelZ)) * RAD_TO_DEG;
#else
    return atan2(-accelX, sqrt(accelY * accelY + accelZ * accelZ)) * RAD_TO_DEG;
#endif
}

double MPU::getYaw() {
    Vector3 gyro = getGyros();
    return gyro.z; 
}

Quaternion MPU::getQuaternion() {
    readMPUData();

    /*Vector3 accel = getAcceleration();
    Vector3 gyro = getGyros();

    double ax = accel.x;
    double ay = accel.y;
    double az = accel.z;

    double gx = gyro.x;
    double gy = gyro.y;
    double gz = gyro.z;*/
    
    double ax = accelX / accelScale;
    double ay = accelY / accelScale;
    double az = accelZ / accelScale;

    double gx = gyroX / gyroScale * DEG_TO_RAD;
    double gy = gyroY / gyroScale * DEG_TO_RAD;
    double gz = gyroZ / gyroScale * DEG_TO_RAD;
    

    // Normalize accelerometer data
    double norm = sqrt(ax * ax + ay * ay + az * az);
    ax /= norm;
    ay /= norm;
    az /= norm;

    double dt = (double)(micros() - timer) / 1000000;
    timer = micros();

    // Complementary filter coefficients
    double alpha = 0.98;

    // Update quaternion using gyroscope data
    q.w += 0.5 * (-q.x * gx - q.y * gy - q.z * gz) * dt;
    q.x += 0.5 * (q.w * gx + q.y * gz - q.z * gy) * dt;
    q.y += 0.5 * (q.w * gy - q.x * gz + q.z * gx) * dt;
    q.z += 0.5 * (q.w * gz + q.x * gy - q.y * gx) * dt;

    // Normalize quaternion
    norm = sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
    q.w /= norm;
    q.x /= norm;
    q.y /= norm;
    q.z /= norm;

    // Correction using accelerometer data (Complementary Filter)
    double roll = atan2(ay, az);
    double pitch = atan(-ax / sqrt(ay * ay + az * az));

    Quaternion correction(
        cos(roll / 2) * cos(pitch / 2),
        sin(roll / 2) * cos(pitch / 2),
        cos(roll / 2) * sin(pitch / 2),
        sin(roll / 2) * sin(pitch / 2)
    );

    // Apply the correction
    q = Quaternion::slerp(q, correction, 1.0 - alpha);

    return q;
}