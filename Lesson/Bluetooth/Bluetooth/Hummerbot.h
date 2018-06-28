#ifndef _HUMMERBOT_H_
#define _HUMMERBOT_H_
#include "Arduino.h"
#include "SmartCar.h"
#include "IRremote.h"
#include "IRremoteInt.h"
#include "ProtocolParser.h"
#include <stdint.h>

#define HB_IR_PIN 12
#define HB_LEFT_POSITIVE_PIN 5
#define HB_LEFT_NEGATIVE_PIN 9
#define HB_RIGHT_POSITIVE_PIN 6
#define HB_RIGHT_NEGATIVE_PIN 10

#define HB_TRIGPIN 2
#define HB_ECHOPIN 3
#define HB_SEVOPIN 13

#define HB_INFRARED_AVOIDANCE_LEFT_PIN A3
#define HB_INFRARED_AVOIDANCE_RIGHT_PIN A4

#define HB_INFRARED_TRACING_PIN1 A0
#define HB_INFRARED_TRACING_PIN2 A1
#define HB_INFRARED_TRACING_PIN3 A2

class Hummerbot : public SmartCar {

private :
    uint8_t left_positive_pin, left_negative_pin, right_positive_pin, right_negative_pin;
    uint8_t TrigPin, EchoPin, SevoPin;   // For Ultrasonic Avoidance
    uint8_t IrPin;                       // Infrared remoter pin
    uint8_t InfraredAvoidanceLeftPin, InfraredAvoidanceRightPin;        // for Infrared Avoidance pin
    uint8_t InfraredTracingPin1, InfraredTracingPin2, InfraredTracingPin3;    // for Infrared tracing pin
    ProtocolParser *mProtocolPackage;

public :
    Hummerbot(ProtocolParser *Package, uint8_t m1 = HB_LEFT_POSITIVE_PIN, uint8_t m2 = HB_LEFT_NEGATIVE_PIN, uint8_t m3 = HB_RIGHT_POSITIVE_PIN, uint8_t m4 = HB_RIGHT_NEGATIVE_PIN);
    ~Hummerbot();
    IRrecv *mIrRecv;
    void GoForward(void);
    void GoBack(void);
    void TurnLeft(void);
    void TurnRight(void);
    void KeepStop(void);
    void Drive(int degree);
    // void SetSpeed(uint8_t s);
    void SetIrPin(uint8_t pin = HB_IR_PIN);
    void SetUltrasonicPin(uint8_t Trig_Pin = HB_TRIGPIN, uint8_t Echo_Pin = HB_ECHOPIN, uint8_t Sevo_Pin = HB_SEVOPIN);
    void SetInfraredAvoidancePin(uint8_t Left_Pin = HB_INFRARED_AVOIDANCE_LEFT_PIN, uint8_t Right_Pin = HB_INFRARED_AVOIDANCE_RIGHT_PIN);
    void SetInfraredTracingPin(uint8_t Pin1 = HB_INFRARED_TRACING_PIN1, uint8_t Pin2 = HB_INFRARED_TRACING_PIN2, uint8_t Pin3 = HB_INFRARED_TRACING_PIN3);
    void SetPs2Pin(uint8_t clk, uint8_t cmd, uint8_t att, uint8_t dat); //11,7,8,4
    void SendBatteryPackage(byte *battery_value);
    void init(void);
};

#endif  /* _HUMMERBOT_H_ */
