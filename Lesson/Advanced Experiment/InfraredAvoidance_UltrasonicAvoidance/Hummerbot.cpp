#include "Hummerbot.h"
#include "debug.h"

Hummerbot::Hummerbot( uint8_t m1 = HB_LEFT_POSITIVE_PIN, uint8_t m2 = HB_LEFT_NEGATIVE_PIN, uint8_t m3 = HB_RIGHT_POSITIVE_PIN, uint8_t m4 = HB_RIGHT_NEGATIVE_PIN):SmartCar("hummer-bot", E_HUMMER_BOT, 0x01, E_BLUETOOTH_CONTROL)
{
    this->left_negative_pin = m1;
    this->left_positive_pin = m2;
    this->right_negative_pin = m3;
    this->right_positive_pin = m4;
}

Hummerbot::~Hummerbot()
{

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

void Hummerbot::SetUltrasonicPin(uint8_t Trig_Pin = HB_TRIGPIN, uint8_t Echo_Pin = HB_ECHOPIN, uint8_t Sevo_Pin = HB_SERVOPIN)
{
    TrigPin = Trig_Pin;
    EchoPin = Echo_Pin;
    SevoPin = Sevo_Pin;
    pinMode(TrigPin, OUTPUT);
    pinMode(EchoPin, INPUT);
    pinMode(SevoPin, OUTPUT);
    servo_angle(90);
    delay(1000);
}

void Hummerbot::servo_angle(float angle) {
  for(int i=0;i<80;i++){  
    float pulsewidth = (angle * 11)+350; 
    digitalWrite(SevoPin, HIGH); 
    delayMicroseconds(pulsewidth);
    digitalWrite(SevoPin, LOW);
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

void Hummerbot::SetInfraredPin(uint8_t Left_Pin = HB_INFRARED_AVOIDANCE_LEFT_PIN, uint8_t Right_Pin = HB_INFRARED_AVOIDANCE_RIGHT_PIN)
{
    left_read = analogRead(Left_Pin); 
    right_read = analogRead(Right_Pin); 
}

void Hummerbot::SetInfraredAvoidancePin(uint8_t Left_Pin = HB_INFRARED_AVOIDANCE_LEFT_PIN, uint8_t Right_Pin = HB_INFRARED_AVOIDANCE_RIGHT_PIN)
{
    InfraredAvoidanceLeftPin = Left_Pin;
    InfraredAvoidanceRightPin = Right_Pin;
    pinMode(InfraredAvoidanceLeftPin, INPUT);
    pinMode(InfraredAvoidanceLeftPin, INPUT);
}


