#ifndef PID_H
#define PID_H

#include <Arduino.h>

class PID {
  public:
    PID(float Kp, float Ki, float Kd, float saturation);

    // Update function now takes the setpoint as a parameter
    float update(float setpoint, float input);

  private:
    float Kp;
    float Ki;
    float Kd;

    float deltaTime;
    float error;
    float errorIntegral;
    float errorDerivative;
    float errorLastCycle;

    float saturation;
    float output;

    unsigned long currentTime;
    unsigned long previousTime;
};

#endif
