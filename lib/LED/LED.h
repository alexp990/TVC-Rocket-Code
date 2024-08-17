/*
    STATE           | COLOR
  ----------------|--------
  LAUNCH_PAD_IDLE | red
  ASCENT          | green
  DESCENT         | blue
  LANDED          | yellow

*/
#include <Arduino.h>
//PINS
#define R_LED 41 
#define G_LED 40 
#define B_LED 39 

class LED {
  public:
    LED();
    void red();
    void green();
    void blue();
    void yellow();
    void off();     
};
