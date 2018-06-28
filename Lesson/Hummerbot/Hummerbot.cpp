#include "Hummerbot.h"
#include "ProtocolParser.h"
#include "debug.h"

Hummerbot::Hummerbot(ProtocolParser *Package, uint8_t m1 = HB_LEFT_POSITIVE_PIN, uint8_t m2 = HB_LEFT_NEGATIVE_PIN, uint8_t m3 = HB_RIGHT_POSITIVE_PIN, uint8_t m4 = HB_RIGHT_NEGATIVE_PIN):SmartCar("hummer-bot", E_HUMMER_BOT, 0x01, E_BLUETOOTH_CONTROL)
{
    mProtocolPackage = Package;
    this->left_positive_pin = m2;
    this->right_negative_pin = m3;
    this->right_positive_pin = m4;
}

Hummerbot::~Hummerbot()
{
    delete mIrRecv;
    delete ps2x;
    delete mInfraredTracing;
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
    int value = (Speed/10)*25.5;	 //app contol hbot_speed is 0 ~ 100 ,pwm is 0~255
    DEBUG_LOG(DEBUG_LEVEL_INFO, "GoForward %d \n",value);
    analogWrite(left_positive_pin,value);
    analogWrite(left_negative_pin,0);
    analogWrite(right_positive_pin,value);
    analogWrite(right_negative_pin,0);
}

void Hummerbot::GoBack(void)
{
    int value = (Speed/10)*25.5;   //app contol hbot_speed is 0 ~ 100 ,pwm is 0~255
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
    int value = (Speed/10)*25.5;   //app contol hbot_speed is 0 ~ 100 ,pwm is 0~255
    DEBUG_LOG(DEBUG_LEVEL_INFO, "TurnLeft =%d \n",value);
    analogWrite(left_positive_pin, 0);
    analogWrite(left_negative_pin, value); //the hbot_speed value of motorA is val
    analogWrite(right_negative_pin, 0);
    analogWrite(right_positive_pin, value); //the hbot_speed value of motorB is val
}

void Hummerbot::TurnLeft_L_R(void)
{
    int value_left = (Speed_left/10)*25.5;   //app contol hbot_speed is 0 ~ 100 ,pwm is 0~255
    int value_right = (Speed_right/10)*25.5;
    DEBUG_LOG(DEBUG_LEVEL_INFO, "GoForward %d \n  %d \n",value_left, value_right);
    analogWrite(left_positive_pin, 0);
    analogWrite(left_negative_pin, value_left); //the hbot_speed value of motorA is val
    analogWrite(right_negative_pin, 0);
    analogWrite(right_positive_pin, value_right); //the hbot_speed value of motorB is val
}

void Hummerbot::TurnRight()
{
    int value = (Speed/10)*25.5;   //app contol hbot_speed is 0 ~ 100 ,pwm is 0~255
    DEBUG_LOG(DEBUG_LEVEL_INFO, "TurnRight%d \n",value);
    analogWrite(left_positive_pin, value);
    analogWrite(left_negative_pin, 0); //the hbot_speed value of motorA is val
    analogWrite(right_negative_pin, value);
    analogWrite(right_positive_pin, 0); //the hbot_speed value of motorB is val
}

void Hummerbot::TurnRight_L_R(void)
{
    int value_left = (Speed_left/10)*25.5;   //app contol hbot_speed is 0 ~ 100 ,pwm is 0~255
    int value_right = (Speed_right/10)*25.5;
    DEBUG_LOG(DEBUG_LEVEL_INFO, "TurnRight %d \n  %d \n",value_left, value_right);
    analogWrite(left_positive_pin, value_left);
    analogWrite(left_negative_pin, 0); //the hbot_speed value of motorA is val
    analogWrite(right_negative_pin, value_right);
    analogWrite(right_positive_pin, 0); //the hbot_speed value of motorB is val
}

void Hummerbot::Drive(int digree)
{
    DEBUG_LOG(DEBUG_LEVEL_INFO, "degree:%d\n", Speed);
    int value = (Speed/10)*25;   //app contol hbot_speed is 0 ~ 100 ,pwm is 0~255
    float f  ;
    if (digree >= 0 && digree < 67.5) {
      f = (float)(digree)/68;
      analogWrite(left_positive_pin, value);
      analogWrite(left_negative_pin, 0);
      analogWrite(right_positive_pin,(float)(value*f) );
      analogWrite(right_negative_pin, 0);
    } else if (digree >= 67.5 && digree < 112.5) {
      GoForward();
    } else if (digree >= 112.5 && digree < 180) {
      f = (float)(180 - digree)/68;
      analogWrite(left_positive_pin, (float)(value*f));
      analogWrite(left_negative_pin, 0);
      analogWrite(right_positive_pin, value);
      analogWrite(right_negative_pin, 0);
    } else if (digree >= 180 && digree < 247.5) {
      f = (float)(digree - 180)/68;
      analogWrite(left_positive_pin, 0);
      analogWrite(left_negative_pin, (float)(value*f));
      analogWrite(right_positive_pin, 0);
      analogWrite(right_negative_pin, value);
    } else if (digree >= 247.5 && digree < 292.5) {
      GoBack();
    } else if (digree >= 292.5 && digree <= 360) {
      f = (float)(360 - digree)/68;
      analogWrite(left_positive_pin, 0);
      analogWrite(left_negative_pin, value);
      analogWrite(right_positive_pin, 0);
      analogWrite(right_negative_pin, (float)(value*f));
    } else {
      KeepStop();
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
    servo_angle(60);
    delay(1000);
}

void Hummerbot::servo_angle(float angle) { //定义一个脉冲函数  
  for(int i=0;i<80;i++){  
    float pulsewidth = (angle * 11)+350; 
    digitalWrite(SevoPin, HIGH);   //将舵机接口电平至高  
    delayMicroseconds(pulsewidth);  //延时脉宽值的微秒数  
    digitalWrite(SevoPin, LOW);    //将舵机接口电平至低  
    delayMicroseconds(20000 - pulsewidth);  
  }  
  delay(100);  
}  

float Hummerbot::Ultrasonic_Detection(){
    TrigPin = HB_TRIGPIN;
    analogWrite(TrigPin, 0); //Send a short pulse to TrigPin
    delayMicroseconds(2);
    analogWrite(TrigPin, 255);
    delayMicroseconds(10);
    analogWrite(TrigPin, 0);
    float Ul_value = pulseIn(HB_ECHOPIN, HIGH) / 58.0;
    return Ul_value;
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
    static bool InfraredTracingInit = false;
    if (!InfraredTracingInit) {
        InfraredTracingPin1 = Pin1;
        InfraredTracingPin2 = Pin2;
        InfraredTracingPin3 = Pin3;
        mInfraredTracing = new InfraredTracing(InfraredTracingPin1, InfraredTracingPin2, InfraredTracingPin3);
        //mInfraredTracing->begin();
        InfraredTracingInit = true;
    }
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

void Hummerbot::SetInfraredPin(uint8_t Left_Pin = HB_INFRARED_AVOIDANCE_LEFT_PIN, uint8_t Right_Pin = HB_INFRARED_AVOIDANCE_RIGHT_PIN)
{
    left_read = analogRead(Left_Pin); 
    right_read = analogRead(Right_Pin); 
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

