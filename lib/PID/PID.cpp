#include "PID.h"

PID::PID(float Kp, float Ki, float Kd, float saturation) {
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
  this->saturation = saturation;

  // Initialize other variables
  this->deltaTime = 0.0f;
  this->error = 0.0f;
  this->errorIntegral = 0.0f;
  this->errorDerivative = 0.0f;
  this->errorLastCycle = 0.0f;
  this->output = 0.0f;
  this->currentTime = micros();
  this->previousTime = this->currentTime;
}

float PID::update(float setpoint, float input) {
  // Calculate delta time
  currentTime = micros();
  deltaTime = (currentTime - previousTime) / 1000000.0f; // Convert microseconds to seconds

  // Calculate error
  error = setpoint - input;

  // Integral term
  errorIntegral += error * deltaTime;

  // Derivative term
  errorDerivative = (error - errorLastCycle) / deltaTime;

  // Calculate total output
  output = Kp * error + Ki * errorIntegral + Kd * errorDerivative;

  // Save current error and time for next cycle
  errorLastCycle = error;
  previousTime = currentTime;

  // Check if output is in saturation
  if (output > saturation) {
    output = saturation;
  } else if (output < -saturation) {
    output = -saturation;
  }

  return output;
}
