
#include <Wire.h>
#include <Arduino.h>

class PID {
  public:
    PID(float Kp, float Ki, float Kd, float saturation);
    float update(float input);

  private:
    float Kp = 0.0f;
    float Ki = 0.0f;
    float Kd = 0.0f;

    // Loop interval time
    float deltaTime = 0.0f;
    float error = 0.0f;
    float setpoint = 0.0f;
    float errorIntegral = 0.0f;
    float errorDerivative = 0.0f;
    float errorLastCycle = 0.0f;

    // Maximum value of manipulated variable (absolute value)
    float saturation = 0.0f;
    float output = 0.0f;

    unsigned long currentTime = 0.0;
    unsigned long previousTime = 0.0;
};