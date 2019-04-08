#include "Hummerbot.h"
#include "ProtocolParser.h"
#include "debug.h"

Hummerbot::Hummerbot(ProtocolParser *Package, uint8_t input1, uint8_t input2, uint8_t input3, uint8_t input4): SmartCar("Hummerbot", 0x01, E_BLUETOOTH_CONTROL)
{
  this->InPut1PIN = input1;
	this->InPut2PIN = input2;
	this->InPut3PIN = input3;
	this->InPut4PIN = input4;
	SetStatus(E_STOP);
	mProtocolPackage = Package;
	Speed = 0;
}

Hummerbot::~Hummerbot(void)
{
    delete mIrRecv;
    delete mPs2x;
    delete mInfraredTracing;
    delete mInfraredAvoidance;
    delete mUltrasonic;
}

#if ARDUINO > 10609
void Hummerbot::SetMotorPin(uint8_t input1=HB_INPUT1_PIN, uint8_t input2=HB_INPUT2_PIN, uint8_t input3=HB_INPUT3_PIN, uint8_t input4=HB_INPUT4_PIN)
#else
void Hummerbot::SetMotorPin(uint8_t input1, uint8_t input2, uint8_t input3, uint8_t input4)
#endif
{
    this->InPut1PIN = input1;
    this->InPut2PIN = input2;
    this->InPut3PIN = input3;
    this->InPut4PIN = input4;
    pinMode(InPut1PIN, OUTPUT);
    digitalWrite(InPut1PIN, LOW);
    pinMode(InPut2PIN, OUTPUT);
    digitalWrite(InPut2PIN, LOW);
    pinMode(InPut3PIN, OUTPUT);
    digitalWrite(InPut3PIN, LOW);
    pinMode(InPut4PIN, OUTPUT);
    digitalWrite(InPut4PIN, LOW);
}

void Hummerbot::init(void)
{
     pinMode(InPut1PIN, OUTPUT);
    digitalWrite(InPut1PIN, LOW);
    pinMode(InPut2PIN, OUTPUT);
    digitalWrite(InPut2PIN, LOW);
    pinMode(InPut3PIN, OUTPUT);
    digitalWrite(InPut3PIN, LOW);
    pinMode(InPut4PIN, OUTPUT);
    digitalWrite(InPut4PIN, LOW);
}

void Hummerbot::GoForward(void)
{
    int value = (Speed / 10) * 25;
    DEBUG_LOG(DEBUG_LEVEL_INFO, "GoForward\n");
    SetStatus(E_FORWARD);
    analogWrite(InPut1PIN, value);
    analogWrite(InPut2PIN, LOW);
    analogWrite(InPut3PIN, LOW);
    analogWrite(InPut4PIN, value);
}

void Hummerbot::GoBack(void)
{
    int value = (Speed / 10) * 25;
    DEBUG_LOG(DEBUG_LEVEL_INFO, "GoBack\n");
    SetStatus(E_BACK);
    analogWrite(InPut1PIN, LOW);
    analogWrite(InPut2PIN, value);
    analogWrite(InPut3PIN, value);
    analogWrite(InPut4PIN, LOW);
}

void Hummerbot::KeepStop(void)
{
    DEBUG_LOG(DEBUG_LEVEL_INFO, "KeepStop\n");
    SetStatus(E_STOP);
    analogWrite(InPut1PIN, LOW);
    analogWrite(InPut2PIN, LOW);
    analogWrite(InPut3PIN, LOW);
    analogWrite(InPut4PIN, LOW);
}

void Hummerbot::TurnLeft(void)
{
    int value = (Speed/10)*25.5;   //app contol hbot_speed is 0 ~ 100 ,pwm is 0~255
    DEBUG_LOG(DEBUG_LEVEL_INFO, "TurnLeft =%d \n",value);
    analogWrite(InPut1PIN, LOW);
    analogWrite(InPut2PIN, value);
    analogWrite(InPut3PIN, LOW);
    analogWrite(InPut4PIN, value);
    SetStatus(E_LEFT);
}

void Hummerbot::TurnRight(void)
{
    int value = (Speed/10)*25.5;   //app contol hbot_speed is 0 ~ 100 ,pwm is 0~255
    analogWrite(InPut1PIN, value);
    analogWrite(InPut2PIN, LOW);
    analogWrite(InPut3PIN, value);
    analogWrite(InPut4PIN, LOW);
    SetStatus(E_RIGHT);

}
void Hummerbot::Drive(void)
{
    Drive(Degree);
}

#if ARDUINO > 10609
void Hummerbot::Drive(int degree=90)
#else
void Hummerbot::Drive(int degree)
#endif
{
	DEBUG_LOG(DEBUG_LEVEL_INFO, "degree = %d speed = %d\n", degree, Speed);
	int value = (Speed / 10) * 25.5;	 //app contol hbot_speed is 0 ~ 100 ,pwm is 0~255
	float f;
    if (degree >= 0 && degree <= 90) {
		f = (float)(degree) / 90;
    analogWrite(InPut1PIN, value);
		analogWrite(InPut2PIN, LOW);
		analogWrite(InPut3PIN, LOW);
		analogWrite(InPut4PIN, (float)(value * f));
		DEBUG_LOG(DEBUG_LEVEL_INFO, "TurnRight\n");
		SetStatus(E_RIGHT);
	} else if (degree > 90 && degree <= 180) {
		f = (float)(180 - degree) / 90;
		analogWrite (InPut1PIN, (float)(value * f));
    analogWrite(InPut2PIN, LOW);
		analogWrite(InPut3PIN, LOW);
		analogWrite(InPut4PIN, value);
		SetStatus(E_LEFT);
	} else if (degree > 180 && degree <= 270) {
		f = (float)(degree - 180) / 90;
	    analogWrite(InPut1PIN, LOW);
		analogWrite(InPut2PIN, value * f);
		analogWrite(InPut3PIN, (float)(value));
		analogWrite(InPut4PIN, LOW);
		DEBUG_LOG(DEBUG_LEVEL_INFO, "TurnLeft\n");
		SetStatus(E_LEFT);
	} else if(degree >=270 && degree <= 360) {
		f = (float)(360 - degree) / 90;
		analogWrite(InPut1PIN, LOW);
		analogWrite(InPut2PIN, (float)(value));
		analogWrite(InPut3PIN, value* f);
		analogWrite(InPut4PIN, LOW);
		DEBUG_LOG(DEBUG_LEVEL_INFO, "TurnRight\n");
		SetStatus(E_RIGHT);
	}
	else {
		KeepStop();
	}
}

#if ARDUINO > 10609
void Hummerbot::SetIrPin(uint8_t pin = HB_IR_PIN)
#else
void Hummerbot::SetIrPin(uint8_t pin )
#endif
{
	IrPin = pin;
	mIrRecv = new IRremote (IrPin);
	mIrRecv->begin();  // Initialize the infrared receiver
}

#if ARDUINO > 10609
void Hummerbot::SetInfraredTracingPin(uint8_t Pin1 = HB_INFRARED_TRACING_PIN1, uint8_t Pin2 = HB_INFRARED_TRACING_PIN2, uint8_t Pin3 = HB_INFRARED_TRACING_PIN3)
#else
void Hummerbot::SetInfraredTracingPin(uint8_t Pin1, uint8_t Pin2, uint8_t Pin3)
#endif
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

#if ARDUINO > 10609
int Hummerbot::SetPs2xPin(uint8_t clk = HB_PS2X_CLK, uint8_t cmd = HB_PS2X_CMD, uint8_t att = HB_PS2X_ATT, uint8_t dat = HB_PS2X_DAT)
#else
int Hummerbot::SetPs2xPin(uint8_t clk , uint8_t cmd , uint8_t att , uint8_t dat)
#endif
{
    static bool Ps2xInit = false;
    int error = 0 ;
    if (!Ps2xInit) {
        DEBUG_LOG(DEBUG_LEVEL_INFO, "SetPs2xPin\n");
        Ps2xClkPin = clk;
        Ps2xCmdPin = cmd;
        Ps2xAttPin = att;
        Ps2xDatPin = dat;
        mPs2x = new PS2X();
        //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
        //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
        error = mPs2x->config_gamepad(Ps2xClkPin, Ps2xCmdPin, Ps2xAttPin, Ps2xDatPin, false, false);
        if (error == 1) {
            DEBUG_LOG(DEBUG_LEVEL_ERR, "No controller found, check wiring\n");
        } else if (error == 2) {
            DEBUG_LOG(DEBUG_LEVEL_ERR, "Controller found but not accepting commands\n");
        } else if (error == 3) {
            DEBUG_LOG(DEBUG_LEVEL_ERR, "Controller refusing to enter Pressures mode, may not support it\n");
        } else if (error == 0) {
            DEBUG_LOG(DEBUG_LEVEL_INFO, "Found Controller, configured successful\n");
        }
        Ps2xInit = true;
    }
    return error;
}
int Hummerbot::ResetPs2xPin(void)
{
	int error = mPs2x->config_gamepad(Ps2xClkPin, Ps2xCmdPin, Ps2xAttPin, Ps2xDatPin, false, false);
	if (error == 1) {
		DEBUG_LOG(DEBUG_LEVEL_ERR, "No controller found, check wiring\n");
	} else if (error == 2) {
		DEBUG_LOG(DEBUG_LEVEL_ERR, "Controller found but not accepting commands\n");
	} else if (error == 3) {
		DEBUG_LOG(DEBUG_LEVEL_ERR, "Controller refusing to enter Pressures mode, may not support it\n");
	} else if (error == 0) {
		DEBUG_LOG(DEBUG_LEVEL_INFO, "Found Controller, configured successful\n");
	}
	return error;
}

 //front 0 left 1 right 2
 #if ARDUINO > 10609
uint16_t Hummerbot::GetUltrasonicDistance(byte direction=0)
#else
uint16_t Hummerbot::GetUltrasonicDistance(byte direction)
#endif
{
	if (direction == 0) {
		return mUltrasonic->GetUltrasonicFrontDistance();
	} else if (direction == 1) {
		return mUltrasonic->GetUltrasonicLeftDistance();
	} else if (direction == 2) {
		return mUltrasonic->GetUltrasonicRightDistance();
	}
}

 #if ARDUINO > 10609
void Hummerbot::SetInfraredAvoidancePin(uint8_t Left_Pin=HB_INFRARED_AVOIDANCE_LEFT_PIN, uint8_t Right_Pin=HB_INFRARED_AVOIDANCE_RIGHT_PIN)
#else
void Hummerbot::SetInfraredAvoidancePin(uint8_t Left_Pin, uint8_t Right_Pin)
#endif
{
	static bool InfraredAvoidanceInit = false;
	if (!InfraredAvoidanceInit) {
		InfraredAvoidancePin1 = Right_Pin;
		InfraredAvoidancePin2 = Left_Pin;
		mInfraredAvoidance = new InfraredAvoidance(InfraredAvoidancePin1, InfraredAvoidancePin2);
		InfraredAvoidanceInit = true;
	}
}

//left 0 right 1
#if ARDUINO > 10609
uint8_t Hummerbot::GetInfraredAvoidance(byte direction=0)
#else
uint8_t Hummerbot::GetInfraredAvoidance(byte direction)
#endif
{
  if (direction == 0 ) {
    return mInfraredAvoidance->GetInfraredAvoidanceLeftValue();
  } else if (direction == 1) {
    return mInfraredAvoidance->GetInfraredAvoidanceRightValue();
  }
}

void Hummerbot::SendTracingSignal(void)
{
    unsigned int TracingSignal = mInfraredTracing->getValue();
    SendData.start_code = 0xAA;
    SendData.type = (E_TYPE)0x01;
    SendData.addr = 0x01;
    SendData.function = E_INFRARED_TRACKING;
    SendData.data = (byte *)&TracingSignal;
    SendData.len = 7;
    SendData.end_code = 0x55;
    mProtocolPackage->SendPackage(&SendData, 1);
}

void Hummerbot::SendInfraredData(void)
{
    unsigned int RightValue = mInfraredAvoidance->GetInfraredAvoidanceRightValue();
    unsigned int LeftValue = mInfraredAvoidance->GetInfraredAvoidanceLeftValue();
    byte buffer[2];
    SendData.start_code = 0xAA;
    SendData.type = (E_TYPE)0x01;
    SendData.addr = 0x01;
    SendData.function = E_INFRARED_AVOIDANCE_MODE;
    buffer[0] = LeftValue & 0xFF;
    buffer[1] = RightValue & 0xFF;
    SendData.data = buffer;
    SendData.len = 8;
    SendData.end_code = 0x55;
    mProtocolPackage->SendPackage(&SendData, 2);
}

void Hummerbot::SendUltrasonicData(void)
{
    uint16_t UlFrontDistance = mUltrasonic->GetUltrasonicFrontDistance();
    SendData.start_code = 0xAA;
    SendData.type = (E_TYPE)0x01;
    SendData.addr = 0x01;
    SendData.function = E_ULTRASONIC_AVOIDANCE;
    SendData.data = (byte *)&UlFrontDistance;
    SendData.len = 7;
    SendData.end_code = 0x55;
    mProtocolPackage->SendPackage(&SendData, 1);
}
#if ARDUINO > 10609
void Hummerbot::SetUltrasonicPin(uint8_t Trig_Pin= HB_TRIGPIN, uint8_t Echo_Pin = HB_ECHOPIN)
#else
void Hummerbot::SetUltrasonicPin(uint8_t Trig_Pin, uint8_t Echo_Pin)
#endif
{
    static bool UltrasonicInit = false;
    if (!UltrasonicInit) {
        EchoPin = Echo_Pin;
        TrigPin = Trig_Pin;

        mUltrasonic = new Ultrasonic(TrigPin, EchoPin);
        UltrasonicInit = true;
    }
}
#if ARDUINO > 10609
void Hummerbot::SetServoPin(uint8_t Servo_Pin = HB_SERVOPIN)
#else
void Hummerbot::SetServoPin(uint8_t Servo_Pin)
#endif
{
	ServoPin = Servo_Pin;
	mUltrasonic->ServoPIN(ServoPin);
}