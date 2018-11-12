#include "Hummerbot.h"
#include "ProtocolParser.h"
#include "KeyMap.h"
#include "debug.h"

#define INPUT1_PIN 6   // PWMB
#define INPUT2_PIN 10  // DIRB  ---  right
#define INPUT3_PIN 5   // DIRA  ---  left
#define INPUT4_PIN 9   // PWMA
#define INFRARED_AVOIDANCE_LEFT_PIN A3
#define INFRARED_AVOIDANCE_RIGHT_PIN A4

ProtocolParser *mProtocol = new ProtocolParser();
Hummerbot hbot(mProtocol, INPUT1_PIN, INPUT2_PIN, INPUT3_PIN, INPUT4_PIN);

void setup()
{
    Serial.begin(9600);
    hbot.init();
    hbot.SetControlMode(E_INFRARED_AVOIDANCE_MODE);
    hbot.SetInfraredAvoidancePin(INFRARED_AVOIDANCE_LEFT_PIN, INFRARED_AVOIDANCE_RIGHT_PIN);
    hbot.SetSpeed(0);
}
//====================================InfraredAvoidance
void HandleInfraredAvoidance()
{
    uint16_t RightValue,LeftValue;
    RightValue = hbot.mInfraredAvoidance->GetInfraredAvoidanceRightValue();
    LeftValue = hbot.mInfraredAvoidance->GetInfraredAvoidanceLeftValue();
    if((RightValue > IA_THRESHOLD)&&(LeftValue >IA_THRESHOLD))
    {
        hbot.SetSpeed(80);
        hbot.GoForward();
      }
    else if((RightValue > IA_THRESHOLD)&&(LeftValue < IA_THRESHOLD))
    {
        hbot.SetSpeed(70);
        hbot.TurnRight();
        delay(200);
    }
    else if((RightValue < IA_THRESHOLD)&&(LeftValue > IA_THRESHOLD))
    {
        hbot.SetSpeed(70);
        hbot.TurnLeft();
        delay(200);
    }
    else if((RightValue < IA_THRESHOLD)&&(LeftValue < IA_THRESHOLD))
    {
        hbot.SetSpeed(80);
        hbot.Drive(0);
        delay(200);
    }
}

void loop()
{
    mProtocol->RecevData();
    switch(hbot.GetControlMode())
    {
        case E_INFRARED_AVOIDANCE_MODE:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_INFRARED_AVOIDANCE \n");
            HandleInfraredAvoidance();
            break;
        default:
            break;
    }
}

