
#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_

/* Includes ------------------------------------------------------------------*/
#include <Arduino.h>


class Ultrasonic
{
  private:
    byte EchoPin, TrigPin, ServoPin;
    uint8_t ServoBaseDegree;

  public:
    byte determine;
    uint16_t FrontDistance;
    uint16_t RightDistance;
    uint16_t LeftDistance;
    Ultrasonic(byte trig_pin, byte echo_pin, byte servo_pin);
    uint16_t GetUltrasonicFrontDistance();
    uint16_t GetUltrasonicLeftDistance();
    uint16_t GetUltrasonicRightDistance();
    SetServoBaseDegree(uint8_t base);
    SetServoDegree(int degree);
};
#endif
