#include "Hummerbot.h"
#include "ProtocolParser.h"
#include "debug.h"

Hummerbot::Hummerbot(ProtocolParser *Package, uint8_t m1 = HB_LEFT_POSITIVE_PIN, uint8_t m2 = HB_LEFT_NEGATIVE_PIN, uint8_t m3 = HB_RIGHT_POSITIVE_PIN, uint8_t m4 = HB_RIGHT_NEGATIVE_PIN):SmartCar("hummer-bot", E_HUMMER_BOT, 0x01, E_BLUTOOTH_CONTROL)
{
    mProtocolPackage = Package;
    this->left_negative_pin = m1;
    this->left_positive_pin = m2;
    this->right_negative_pin = m3;
    this->right_positive_pin = m4;
}

Hummerbot::~Hummerbot()
{
    delete mIrRecv;
}

void Hummerbot::init(void)
{
    pinMode(left_positive_pin, OUTPUT);
    digitalWrite(left_negative_pin, LOW); // When not sending PWM, we want it low
    pinMode(right_positive_pin, OUTPUT);
    digitalWrite(right_positive_pin, LOW); // When not sending PWM, we want it low
    pinMode(left_negative_pin, OUTPUT);
    digitalWrite(left_negative_pin, LOW);  // When not sending PWM, we want it low
    pinMode(right_negative_pin, OUTPUT);
    digitalWrite(right_negative_pin, LOW); // When not sending PWM, we want it low
}

void Hummerbot::GoForward(void)
{
    int value = (Speed/10)*25;	 //app contol hbot_speed is 0 ~ 100 ,pwm is 0~255
    DEBUG_LOG(DEBUG_LEVEL_INFO, "GoForward %d \n",value);
    analogWrite(left_positive_pin,value);
    analogWrite(left_negative_pin,0);
    analogWrite(right_positive_pin,value);
    analogWrite(right_negative_pin,0);
}

void Hummerbot::GoBack(void)
{
    int value = (Speed/10)*25;   //app contol hbot_speed is 0 ~ 100 ,pwm is 0~255
    DEBUG_LOG(DEBUG_LEVEL_INFO, "GoBack %d \n",value);
    analogWrite(left_negative_pin,value);
    analogWrite(left_positive_pin,0);
    analogWrite(right_negative_pin,value);
    analogWrite(right_positive_pin,0);
}

void Hummerbot::KeepStop(void)
{
    DEBUG_LOG(DEBUG_LEVEL_INFO, "KeepStop \n");
    analogWrite(left_positive_pin,0);
    analogWrite(left_negative_pin,0);
    analogWrite(right_positive_pin,0);
    analogWrite(right_negative_pin,0);
}

void Hummerbot::TurnLeft()
{   
    int value = (Speed/10)*25;   //app contol hbot_speed is 0 ~ 100 ,pwm is 0~255
    DEBUG_LOG(DEBUG_LEVEL_INFO, "TurnLeft =%d \n",value);
    analogWrite(left_positive_pin, 0);
    analogWrite(left_negative_pin, value); //the hbot_speed value of motorA is val
    analogWrite(right_negative_pin, 0);
    analogWrite(right_positive_pin, value); //the hbot_speed value of motorB is val
}

void Hummerbot::TurnRight()
{
    int value = (Speed/10)*25;   //app contol hbot_speed is 0 ~ 100 ,pwm is 0~255
    DEBUG_LOG(DEBUG_LEVEL_INFO, "TurnRight%d \n",value);
    analogWrite(left_positive_pin, value);
    analogWrite(left_negative_pin, 0); //the hbot_speed value of motorA is val
    analogWrite(right_negative_pin, value);
    analogWrite(right_positive_pin, 0); //the hbot_speed value of motorB is val
}

void Hummerbot::Drive(int degree)
{
    DEBUG_LOG(DEBUG_LEVEL_INFO, "degree:%d\n", Speed);
    int value = (Speed/10)*25;	 //app contol hbot_speed is 0 ~ 100 ,pwm is 0~255
    float f;
    if (degree > 360 ||degree <= 0)
    {
        KeepStop();
    }
    if( degree >= 75 && degree<= 110 )
   {
        GoForward();
    }
   if(degree >= 345 || degree <= 15) 
   {
       TurnRight();
   }
    if( degree >= 250 && degree<= 290)
    {
        GoBack();
    }
    if( degree >= 175 && degree <= 195 )
    {
        TurnLeft();
    }
    if (degree > 30 && degree < 60) 
    {
        f = (float)(90-degree)/90;
        analogWrite(left_positive_pin,value);
        analogWrite(left_negative_pin, 0); //the hbot_speed value of motorA is val
        analogWrite(right_positive_pin,0);
        analogWrite(right_negative_pin,(float)(value*f)); //the hbot_speed value of motorB is val
    }
    if (degree > 130 && degree < 153)
    {
        f = (float)(180-degree)/90;
        analogWrite(left_negative_pin,value);
        analogWrite(left_positive_pin, 0); //the hbot_hbot_speed value of motorA is val
        analogWrite(right_negative_pin,0);
        analogWrite(right_positive_pin,(float)(value*f)); //the hbot_hbot_speed value of motorB is val
       
    }
    if (degree > 208 && degree < 238) 
    {
        f = (float)(degree-180)/90;
        analogWrite(right_positive_pin,0);
        analogWrite(right_negative_pin, (float)(value*f));          //the hbot_speed value of motorA is val
        analogWrite(left_positive_pin,value);
        analogWrite(left_negative_pin,0); //the hbot_speed value of motorB is val
    } 
    if (degree > 311 && degree < 335  )
    {
        f = (float)(360-degree)/90;
        analogWrite(right_positive_pin,value);
        analogWrite(right_negative_pin, 0);          //the hbot_speed value of motorA is val
        analogWrite(left_positive_pin,0);
        analogWrite(left_negative_pin,(float)(value*f)); //the hbot_speed value of motorB is val
    }
}

void Hummerbot::SetIrPin(uint8_t pin = HB_IR_PIN)
{
    IrPin = pin;
    mIrRecv = new IRrecv(IrPin);
    mIrRecv->enableIRIn();  // Initialize the infrared receiver
}

void Hummerbot::SetUltrasonicPin(uint8_t Trig_Pin = HB_TRIGPIN, uint8_t Echo_Pin = HB_ECHOPIN, uint8_t Sevo_Pin = HB_SERVOPIN)
{
    TrigPin = Trig_Pin;
    EchoPin = Echo_Pin;
    SevoPin = Sevo_Pin;
    pinMode(TrigPin, OUTPUT);
    pinMode(EchoPin, INPUT);
    pinMode(SevoPin, OUTPUT);
}

void Hummerbot::SetInfraredAvoidancePin(uint8_t Left_Pin = HB_INFRARED_AVOIDANCE_LEFT_PIN, uint8_t Right_Pin = HB_INFRARED_AVOIDANCE_RIGHT_PIN)
{
    InfraredAvoidanceLeftPin = Left_Pin;
    InfraredAvoidanceRightPin = Right_Pin;
    pinMode(InfraredAvoidanceLeftPin, INPUT);
    pinMode(InfraredAvoidanceLeftPin, INPUT);
}

void Hummerbot::SetInfraredTracingPin(uint8_t Pin1 = HB_INFRARED_TRACING_PIN1, uint8_t Pin2 = HB_INFRARED_TRACING_PIN2, uint8_t Pin3 = HB_INFRARED_TRACING_PIN3)
{
    InfraredTracingPin1 = Pin1;
    InfraredTracingPin2 = Pin2;
    InfraredTracingPin2 = Pin3;
    pinMode(InfraredTracingPin1, INPUT);
    pinMode(InfraredTracingPin2, INPUT);
    pinMode(InfraredTracingPin3, INPUT);
}

void Hummerbot::SetPs2xPin(uint8_t clk = HB_PS2X_CLK, uint8_t cmd = HB_PS2X_CMD, uint8_t att = HB_PS2X_ATT, uint8_t dat = HB_PS2X_DAT)
{
    DEBUG_LOG(DEBUG_LEVEL_INFO, "SetPs2xPin \n");
    Ps2xClkPin = HB_PS2X_CLK;
    Ps2xCmdPin = HB_PS2X_CMD;
    Ps2xAttPin = HB_PS2X_ATT;
    Ps2xDatPin = HB_PS2X_DAT;
    ps2x = new PS2X();
    ps2x->config_gamepad(HB_PS2X_CLK, HB_PS2X_CMD, HB_PS2X_ATT, HB_PS2X_DAT, true, true);
}

void Hummerbot::SendBatteryPackage(byte *battery_value)
{
    ST_PROTOCOL send_dat;
    send_dat.start_code = PROTOCOL_START_CODE;
    send_dat.type = 0x01;
    send_dat.addr = 0x01;
    send_dat.function = E_BATTERY;
    send_dat.data = battery_value;
    send_dat.end_code = PROTOCOL_END_CODE;
    mProtocolPackage->SendPackage(&send_dat,1);
}

