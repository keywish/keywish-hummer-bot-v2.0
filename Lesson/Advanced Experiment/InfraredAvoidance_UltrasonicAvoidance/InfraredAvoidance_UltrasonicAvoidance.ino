#include "Hummerbot.h"
#include "ProtocolParser.h"
#include "KeyMap.h"
#include "debug.h"

#define INPUT1_PIN 6   // PWMB
#define INPUT2_PIN 10  // DIRB  ---  right
#define INPUT3_PIN 5   // DIRA  ---  left
#define INPUT4_PIN 9   // PWMA
#define SERVO_PIN 13
#define ECHO_PIN 3
#define TRIG_PIN 2
#define INFRARED_AVOIDANCE_LEFT_PIN A3
#define INFRARED_AVOIDANCE_RIGHT_PIN A4

ProtocolParser *mProtocol = new ProtocolParser();
Hummerbot hbot(mProtocol, INPUT1_PIN, INPUT2_PIN, INPUT3_PIN, INPUT4_PIN);

void setup()
{
    Serial.begin(9600);
    hbot.init();
    hbot.SetControlMode(E_ULTRASONIC_INFRARED_AVOIDANCE);
    hbot.SetUltrasonicPin(TRIG_PIN, ECHO_PIN, SERVO_PIN);
    hbot.SetSpeed(0);
    hbot.mUltrasonic->SetServoBaseDegree(90);
    hbot.mUltrasonic->SetServoDegree(90);
}
//=========================== Ultrasonic_Infrared =====
void HandleUltrasonicInfraredAvoidance()
{
    uint16_t RightValue,LeftValue;
    uint16_t UlFrontDistance,UlLeftDistance,UlRightDistance;
    RightValue = hbot.mInfraredAvoidance->GetInfraredAvoidanceRightValue();
    LeftValue = hbot.mInfraredAvoidance->GetInfraredAvoidanceLeftValue();
    UlFrontDistance =  hbot.mUltrasonic->GetUltrasonicFrontDistance();
    DEBUG_LOG(DEBUG_LEVEL_INFO, "UlFrontDistance =%d \n",UlFrontDistance);

   if ((RightValue >= IA_THRESHOLD) && (LeftValue <= IA_THRESHOLD)) {
        hbot.SetSpeed(80);
        hbot.Drive(10 );
    } else if ((RightValue < IA_THRESHOLD) && (LeftValue > IA_THRESHOLD)) {
        hbot.SetSpeed(80);
        hbot.Drive(170);
    } else {
        hbot.SetSpeed(50);
        hbot.GoForward();
    }
    DEBUG_LOG(DEBUG_LEVEL_INFO, "UlFrontDistance = %d \n\r", UlFrontDistance);
    if (UlFrontDistance < UL_LIMIT_MID) {
        hbot.KeepStop();
        if (UlFrontDistance <= UL_LIMIT_MIN || RightValue <= IA_THRESHOLD || LeftValue <= IA_THRESHOLD) {
            hbot.SetSpeed(60);
            hbot.GoBack();
            delay(300);
            hbot.KeepStop();
        }
            UlRightDistance = hbot.mUltrasonic->GetUltrasonicRightDistance();
            UlLeftDistance = hbot.mUltrasonic->GetUltrasonicLeftDistance();
            if (UlRightDistance >= UlLeftDistance) {
                hbot.SetSpeed(100);
                hbot.TurnRight();
                delay(310);
            }
            if (UlLeftDistance > UlRightDistance) {
                hbot.SetSpeed(100);
                hbot.TurnLeft();
                delay(310);
            }
            if (UlLeftDistance <= UL_LIMIT_MIN && UlRightDistance <= UL_LIMIT_MIN ) {
                hbot.SetSpeed(100);
                hbot.Drive(0);
                delay(530);
                 hbot.KeepStop();
            }
            hbot.KeepStop();
    }
}

void loop()
{
    mProtocol->RecevData();
    switch(hbot.GetControlMode())
    {
		    case E_ULTRASONIC_INFRARED_AVOIDANCE:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_ULTRASONIC_INFRARED_AVOIDANCE \n");
            HandleUltrasonicInfraredAvoidance();
            break;
        default:
            break;
    }
}

