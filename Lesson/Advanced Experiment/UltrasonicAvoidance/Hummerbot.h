#ifndef _HUMMERBOT_H_
#define _HUMMERBOT_H_
#include <stdint.h>
#include "Arduino.h"
#include "SmartCar.h"
#include "Servo.h"

#define HB_LEFT_POSITIVE_PIN 10
#define HB_LEFT_NEGATIVE_PIN 6
#define HB_RIGHT_POSITIVE_PIN 9
#define HB_RIGHT_NEGATIVE_PIN 5

#define HB_TRIGPIN 2
#define HB_ECHOPIN 3
#define HB_SERVOPIN 13

class Hummerbot : public SmartCar {

private :
    uint8_t left_positive_pin, left_negative_pin, right_positive_pin, right_negative_pin;
    uint8_t TrigPin, EchoPin, SevoPin;   // For Ultrasonic Avoidance
    float Ul_value_mid;
    float Ul_value_left;
    float Ul_value_right;
public :
    Hummerbot( uint8_t m1 = HB_LEFT_POSITIVE_PIN, uint8_t m2 = HB_LEFT_NEGATIVE_PIN, uint8_t m3 = HB_RIGHT_POSITIVE_PIN, uint8_t m4 = HB_RIGHT_NEGATIVE_PIN);
    ~Hummerbot();
    void GoForward(void);
    void GoBack(void);
    void TurnLeft(void);
    void TurnRight(void);
    void TurnLeft_L_R(void);
    void TurnRight_L_R(void);
    void KeepStop(void);
    void servo_angle(float angle);
    void SetUltrasonicPin(uint8_t Trig_Pin = HB_TRIGPIN, uint8_t Echo_Pin = HB_ECHOPIN, uint8_t Sevo_Pin = HB_SERVOPIN);
    float Ultrasonic_Detection();
    void init(void);
};

#endif  /* _HUMMERBOT_H_ */
