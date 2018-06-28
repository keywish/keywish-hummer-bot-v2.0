#ifndef _HUMMERBOT_H_
#define _HUMMERBOT_H_
#include <stdint.h>
#include "Arduino.h"
#include "SmartCar.h"
#include "IRremote.h"
#include "IRremoteInt.h"

#define HB_IR_PIN 12
#define HB_LEFT_POSITIVE_PIN 10
#define HB_LEFT_NEGATIVE_PIN 6
#define HB_RIGHT_POSITIVE_PIN 9
#define HB_RIGHT_NEGATIVE_PIN 5



class Hummerbot : public SmartCar {

private :
    uint8_t left_positive_pin, left_negative_pin, right_positive_pin, right_negative_pin;
    uint8_t IrPin;                       // Infrared remoter pin

public :
    Hummerbot( uint8_t m1 = HB_LEFT_POSITIVE_PIN, uint8_t m2 = HB_LEFT_NEGATIVE_PIN, uint8_t m3 = HB_RIGHT_POSITIVE_PIN, uint8_t m4 = HB_RIGHT_NEGATIVE_PIN);
    ~Hummerbot();
    IRrecv *mIrRecv;
    void GoForward(void);
    void GoBack(void);
    void TurnLeft(void);
    void TurnRight(void);
    void KeepStop(void);
    // void SetSpeed(uint8_t s);
    void SetIrPin(uint8_t pin = HB_IR_PIN);
    void init(void);
};

#endif  /* _HUMMERBOT_H_ */
