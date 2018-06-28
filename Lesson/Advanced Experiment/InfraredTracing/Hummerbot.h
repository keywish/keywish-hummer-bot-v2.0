#ifndef _HUMMERBOT_H_
#define _HUMMERBOT_H_
#include <stdint.h>
#include "Arduino.h"
#include "SmartCar.h"
#include "InfraredTracing.h"

#define HB_LEFT_POSITIVE_PIN 10
#define HB_LEFT_NEGATIVE_PIN 6
#define HB_RIGHT_POSITIVE_PIN 9
#define HB_RIGHT_NEGATIVE_PIN 5

#define HB_INFRARED_TRACING_PIN1 A0
#define HB_INFRARED_TRACING_PIN2 A1
#define HB_INFRARED_TRACING_PIN3 A2

class Hummerbot : public SmartCar {

private :
    uint8_t left_positive_pin, left_negative_pin, right_positive_pin, right_negative_pin;
    uint8_t InfraredTracingPin1, InfraredTracingPin2, InfraredTracingPin3;    // for Infrared tracing pin

public :
    Hummerbot( uint8_t m1 = HB_LEFT_POSITIVE_PIN, uint8_t m2 = HB_LEFT_NEGATIVE_PIN, uint8_t m3 = HB_RIGHT_POSITIVE_PIN, uint8_t m4 = HB_RIGHT_NEGATIVE_PIN);
    ~Hummerbot();
    InfraredTracing *mInfraredTracing;
    void GoForward(void);
    void GoBack(void);
    void TurnLeft(void);
    void TurnRight(void);
    void KeepStop(void);
    void SetInfraredTracingPin(uint8_t Pin1 = HB_INFRARED_TRACING_PIN1, uint8_t Pin2 = HB_INFRARED_TRACING_PIN2, uint8_t Pin3 = HB_INFRARED_TRACING_PIN3);
    void init(void);
};

#endif  /* _HUMMERBOT_H_ */
