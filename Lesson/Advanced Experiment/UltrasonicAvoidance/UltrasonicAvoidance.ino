#include "Hummerbot.h"
#include "ProtocolParser.h"
#include "KeyMap.h"
#include "debug.h"

#define INPUT1_PIN 6   // PWMB
#define INPUT2_PIN 10  // DIRB  ---  right
#define INPUT3_PIN 5   // DIRA  ---  left
#define INPUT4_PIN 9   // PWMA
#define IR_PIN 12
#define SERVO_PIN 13
#define ECHO_PIN 3

ProtocolParser *mProtocol = new ProtocolParser();
Hummerbot hbot(mProtocol, INPUT1_PIN, INPUT2_PIN, INPUT3_PIN, INPUT4_PIN);

void setup()
{
    Serial.begin(9600);
    hbot.init();
    hbot.SetControlMode(E_ULTRASONIC_AVOIDANCE);
    hbot.SetUltrasonicPin(TRIG_PIN, ECHO_PIN, SERVO_PIN);
    hbot.SetSpeed(0);
    hbot.mUltrasonic->SetServoBaseDegree(90);
    hbot.mUltrasonic->SetServoDegree(90);
}

void HandleUltrasonicAvoidance()
{
    uint16_t UlFrontDistance,UlLeftDistance,UlRightDistance;
    UlFrontDistance =  hbot.mUltrasonic->GetUltrasonicFrontDistance();
    DEBUG_LOG(DEBUG_LEVEL_INFO, "UlFrontDistance =%d \n",UlFrontDistance);
    if ((UlFrontDistance < UL_LIMIT_MIN))
    {
        hbot.SetSpeed(100);
        hbot.GoBack();
        delay(250);
    }
    if (UlFrontDistance < UL_LIMIT_MID)
    {
        hbot.KeepStop();
        delay(100);
        UlRightDistance = hbot.mUltrasonic->GetUltrasonicRightDistance();
        UlLeftDistance = hbot.mUltrasonic->GetUltrasonicLeftDistance();
        if((UlRightDistance > UL_LIMIT_MIN) && (UlRightDistance < UL_LIMIT_MAX))
        {
            hbot.SetSpeed(80);
            hbot.TurnRight();
            delay(310);
        }
        else if((UlLeftDistance > UL_LIMIT_MIN) && (UlLeftDistance < UL_LIMIT_MAX))
        {
            hbot.SetSpeed(80);
            hbot.TurnLeft();
            delay(310);
        }
        else if((UlRightDistance < UL_LIMIT_MIN) && (UlLeftDistance < UL_LIMIT_MIN) )
        {
            hbot.SetSpeed(80);
            hbot.Drive(0);
            delay(510);
        }
    } else{
          hbot.SetSpeed(80);
          hbot.GoForward();
      }
}

void loop()
{
    mProtocol->RecevData();
    switch(hbot.GetControlMode())
    {
        case E_ULTRASONIC_AVOIDANCE:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_ULTRASONIC_AVOIDANCE \n");
            HandleUltrasonicAvoidance();
            break;
        default:
            break;
    }
}

