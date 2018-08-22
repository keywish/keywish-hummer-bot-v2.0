#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(byte trig_pin, byte echo_pin, byte servo_pin)
{
    TrigPin = trig_pin;
    EchoPin = echo_pin;
    ServoPin = servo_pin;
    pinMode(EchoPin, INPUT);
    pinMode(TrigPin, OUTPUT);
    pinMode(ServoPin,OUTPUT);
}

uint16_t Ultrasonic::GetUltrasonicFrontDistance()
{
    static byte count = 0;
    do {
        digitalWrite(TrigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(TrigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(TrigPin, LOW);
        count ++;
        FrontDistance = pulseIn(EchoPin, HIGH) / 58.00;
    } while (FrontDistance > UL_LIMIT_MAX  && (count > 3));
    if ( count >= 3 )
    {
       FrontDistance = 10;
    }
    count = 0;
    return FrontDistance;
}

uint16_t Ultrasonic::GetUltrasonicLeftDistance()
{
    SetServoDegree(180);
    LeftDistance = GetUltrasonicFrontDistance();
    SetServoDegree(90);
    return LeftDistance;
}

uint16_t Ultrasonic::GetUltrasonicRightDistance()
{
    SetServoDegree(20);
    RightDistance = GetUltrasonicFrontDistance();
    SetServoDegree(90);
    return RightDistance;
}

Ultrasonic::SetServoBaseDegree(uint8_t base)
{
    ServoBaseDegree = base;
}

Ultrasonic::SetServoDegree(int Angle)
{
	int Degree = Angle;
	int servo_degree;
	if (Degree > 360) {
		return;
	}
	if (Degree == 90 || Degree == 270) {
		servo_degree = ServoBaseDegree;
	} else if (Degree >= 0 && Degree <= 180) {
		servo_degree = ServoBaseDegree - 90 + Degree;   // 180-degree-diff
	}

	for (int i = 0; i < 80; i++) {
		float pulsewidth = (servo_degree * 11) + 350;
		digitalWrite(ServoPin, HIGH);   //Set the servo interface level to high
		delayMicroseconds(pulsewidth);  //The number of microseconds of the delay pulse width value
		digitalWrite(ServoPin, LOW);    //Set the servo interface level to low
		delayMicroseconds(20000 - pulsewidth);
	}
	delay(250);
}
