#ifndef _HUMMERBOT_H_
#define _HUMMERBOT_H_
#include <stdint.h>
#include "Arduino.h"
#include "SmartCar.h"
#include "IRremote.h"
#include "PS2X_lib.h"  //for v1.6
#include "InfraredAvoidance.h"
#include "InfraredTracing.h"
#include "ProtocolParser.h"
#include "Ultrasonic.h"

#define HB_IR_PIN 12
#define HB_INPUT1_PIN 6
#define HB_INPUT2_PIN 10
#define HB_INPUT4_PIN 9
#define HB_INPUT3_PIN 5

#define HB_TRIGPIN 2
#define HB_ECHOPIN 3
#define HB_SERVOPIN 13

#define HB_INFRARED_AVOIDANCE_LEFT_PIN A3
#define HB_INFRARED_AVOIDANCE_RIGHT_PIN A4

#define HB_INFRARED_TRACING_PIN1 A0
#define HB_INFRARED_TRACING_PIN2 A1
#define HB_INFRARED_TRACING_PIN3 A2

#define HB_PS2X_CLK 11
#define HB_PS2X_CMD 7
#define HB_PS2X_ATT 8
#define HB_PS2X_DAT 4

class Hummerbot : public SmartCar {
private :
    uint8_t InPut2PIN, InPut1PIN, PwmaPin, InPut3PIN, InPut4PIN;
    uint8_t IrPin;      // Infrared remoter pin
    uint8_t InfraredTracingPin1, InfraredTracingPin2, InfraredTracingPin3, InfraredTracingPin4, InfraredTracingPin5;    // for Infrared tracing pin
    uint8_t Ps2xClkPin, Ps2xCmdPin, Ps2xAttPin, Ps2xDatPin;    // for Ps2 remoter
    uint8_t InfraredAvoidancePin1,InfraredAvoidancePin2;     //For infrared obstacle avoidance
    uint8_t EchoPin,TrigPin,ServoPin;
    ST_PROTOCOL SendData;
    ProtocolParser *mProtocolPackage;

public :
    Hummerbot(ProtocolParser *Package, uint8_t input1 = HB_INPUT1_PIN, uint8_t input2 = HB_INPUT2_PIN, uint8_t input3 = HB_INPUT3_PIN, uint8_t input4 = HB_INPUT4_PIN);
    ~Hummerbot();
    IRremote  *mIrRecv;
    PS2X *mPs2x;
    InfraredTracing *mInfraredTracing;
    InfraredAvoidance *mInfraredAvoidance;
    Ultrasonic *mUltrasonic;

    void GoForward(void);
    void GoBack(void);
    void TurnLeft(void);
    void TurnRight(void);
    void KeepStop(void);
    void Drive(void);
    void Drive(int degree);
    void SetIrPin(uint8_t pin = HB_IR_PIN);
	void SetMotorPin(uint8_t input2, uint8_t input1, uint8_t input3, uint8_t input4);
    void SetUltrasonicPin(uint8_t Trig_Pin = HB_TRIGPIN, uint8_t Echo_Pin = HB_ECHOPIN, uint8_t Sevo_Pin = HB_SERVOPIN);
    void SetInfraredAvoidancePin(uint8_t Left_Pin = HB_INFRARED_AVOIDANCE_LEFT_PIN, uint8_t Right_Pin = HB_INFRARED_AVOIDANCE_RIGHT_PIN);
    void SetInfraredTracingPin(uint8_t Pin1 = HB_INFRARED_TRACING_PIN1, uint8_t Pin2 = HB_INFRARED_TRACING_PIN2, uint8_t Pin3 = HB_INFRARED_TRACING_PIN3);
    int SetPs2xPin(uint8_t clk = HB_PS2X_CLK, uint8_t cmd = HB_PS2X_CMD, uint8_t att = HB_PS2X_ATT, uint8_t dat = HB_PS2X_DAT);
    uint16_t GetUltrasonicDistance(byte);//front 0 left 1 right 2
    uint8_t GetInfraredAvoidance(byte); //left 0 right 2
    int ResetPs2xPin(void);
    void SendBatteryPackage(byte *battery_value);
    void SendTracingSignal();
    void SendInfraredData();
    void SendUltrasonicData();
    void init(void);
};

#endif  /* _HUMMERBOT_H_ */
