#include <Arduino.h>
#include "Quaternion.h"

void setup() {
    Serial.begin(9600);
    
    // Test Quaternion Creation
    Serial.println("Testing Quaternion Creation...");

    Quaternion q1;
    Serial.print("Default Quaternion: ");
    Serial.print("w = "); Serial.print(q1.w);
    Serial.print(", x = "); Serial.print(q1.x);
    Serial.print(", y = "); Serial.print(q1.y);
    Serial.print(", z = "); Serial.println(q1.z);

    Quaternion q2(0.7071, 0, 0.7071, 0);
    Serial.print("Custom Quaternion: ");
    Serial.print("w = "); Serial.print(q2.w);
    Serial.print(", x = "); Serial.print(q2.x);
    Serial.print(", y = "); Serial.print(q2.y);
    Serial.print(", z = "); Serial.println(q2.z);

    // Test Euler to Quaternion Conversion
    Serial.println("Testing Euler to Quaternion Conversion...");

    double roll = 30.0 * DEG_TO_RAD;  // 30 degrees to radians
    double pitch = 45.0 * DEG_TO_RAD; // 45 degrees to radians
    double yaw = 60.0 * DEG_TO_RAD;   // 60 degrees to radians

    Quaternion q = Quaternion::fromEuler(roll, pitch, yaw);

    Serial.print("Converted Quaternion from Euler Angles: ");
    Serial.print("w = "); Serial.print(q.w);
    Serial.print(", x = "); Serial.print(q.x);
    Serial.print(", y = "); Serial.print(q.y);
    Serial.print(", z = "); Serial.println(q.z);
}
