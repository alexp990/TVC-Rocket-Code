#include "Quaternion.h"
#include <math.h>

// Constructor initializes the quaternion to the identity quaternion
Quaternion::Quaternion() : w(1), x(0), y(0), z(0) {}

// Constructor to initialize the quaternion with specific values
Quaternion::Quaternion(double w, double x, double y, double z) : w(w), x(x), y(y), z(z) {}

Quaternion Quaternion::normalized() const {
    double norm = sqrt(w * w + x * x + y * y + z * z);
    if (norm > 0.0) {
        return Quaternion(w / norm, x / norm, y / norm, z / norm);
    }
    return Quaternion();  // Return the identity quaternion if norm is zero
}

// Normalize the quaternion to ensure it represents a valid rotation
void Quaternion::normalize() {
    double norm = sqrt(w * w + x * x + y * y + z * z);
    if (norm > 0.0) {
        w /= norm;
        x /= norm;
        y /= norm;
        z /= norm;
    }
}

// Function to create a quaternion from Euler angles (roll, pitch, yaw)
Quaternion Quaternion::fromEuler(double roll, double pitch, double yaw) {
    double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);
    double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);
    double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);

    Quaternion q;
    q.w = cr * cp * cy + sr * sp * sy;
    q.x = sr * cp * cy - cr * sp * sy;
    q.y = cr * sp * cy + sr * cp * sy;
    q.z = cr * cp * sy - sr * sp * cy;

    q.normalize();  

    return q;
}

// Function to convert quaternion to Euler angles (roll, pitch, yaw)
Vector3 Quaternion::toEuler() const {
    Vector3 euler;
    
    // Roll (x-axis rotation)
    double sinr_cosp = 2.0 * (w * x + y * z);
    double cosr_cosp = 1.0 - 2.0 * (x * x + y * y);
    euler.x = atan2(sinr_cosp, cosr_cosp);

    // Pitch (y-axis rotation)
    double sinp = 2.0 * (w * y - z * x);
    if (fabs(sinp) >= 1.0)
        euler.y = copysign(M_PI / 2.0, sinp); // Use 90 degrees if out of range
    else
        euler.y = asin(sinp);

    // Yaw (z-axis rotation)
    double siny_cosp = 2.0 * (w * z + x * y);
    double cosy_cosp = 1.0 - 2.0 * (y * y + z * z);
    euler.z = atan2(siny_cosp, cosy_cosp);

    euler.x *= RAD_TO_DEG;
    euler.y *= RAD_TO_DEG;
    euler.z *= RAD_TO_DEG;

    return euler;
}

// Quaternion multiplication (Hamilton product)
Quaternion Quaternion::operator*(const Quaternion& q) const {
    return Quaternion(
        w * q.w - x * q.x - y * q.y - z * q.z,
        w * q.x + x * q.w + y * q.z - z * q.y,
        w * q.y - x * q.z + y * q.w + z * q.x,
        w * q.z + x * q.y - y * q.x + z * q.w
    );
}

// Spherical linear interpolation between two quaternions (slerp)
Quaternion Quaternion::slerp(const Quaternion& q1, const Quaternion& q2, double t) {
    // Compute the cosine of the angle between the two quaternions
    double cosTheta = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;

    // If cosTheta is negative, flip one of the quaternions to ensure shortest path
    Quaternion q2Copy = q2;
    if (cosTheta < 0.0) {
        q2Copy = Quaternion(-q2.w, -q2.x, -q2.y, -q2.z);
        cosTheta = -cosTheta;
    }

    // If the quaternions are very close, use linear interpolation to avoid divide by zero
    if (cosTheta > 0.9995) {
        return Quaternion(
            q1.w + t * (q2Copy.w - q1.w),
            q1.x + t * (q2Copy.x - q1.x),
            q1.y + t * (q2Copy.y - q1.y),
            q1.z + t * (q2Copy.z - q1.z)
        ).normalized();  
    }

    // Compute the angle and the sine of the angle
    double theta = acos(cosTheta);
    double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

    // Compute the weights for the interpolation
    double w1 = sin((1.0 - t) * theta) / sinTheta;
    double w2 = sin(t * theta) / sinTheta;

    // Return the interpolated quaternion
    return Quaternion(
        w1 * q1.w + w2 * q2Copy.w,
        w1 * q1.x + w2 * q2Copy.x,
        w1 * q1.y + w2 * q2Copy.y,
        w1 * q1.z + w2 * q2Copy.z
    ).normalized(); 
}