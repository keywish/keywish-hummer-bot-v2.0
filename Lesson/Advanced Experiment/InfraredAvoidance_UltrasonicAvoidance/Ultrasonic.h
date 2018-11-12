
#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_

/* Includes ------------------------------------------------------------------*/
#include <Arduino.h>

#define UL_LIMIT_MIN 12
#define UL_LIMIT_MID 20
#define UL_LIMIT_MAX 550

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
    void SetServoBaseDegree(uint8_t base);
    void SetServoDegree(int degree);
};
#endif
