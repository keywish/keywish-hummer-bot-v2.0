
#include "Hummerbot.h"
#include "debug.h"

int E1 = 10;  // PWMB
int M1 = 6;   // DIRB  ---  right
int E2 = 9;   // PWMA
int M2 = 5;   // DIRA  ---  left

#define HB_INFRARED_AVOIDANCE_LEFT_PIN A3
#define HB_INFRARED_AVOIDANCE_RIGHT_PIN A4

Hummerbot hbot( E1, M1, E2, M2);

void setup()
{
    Serial.begin(9600);
    hbot.init();
    hbot.SetControlMode(E_INFRARED_AVOIDANCE);
    hbot.SetInfraredAvoidancePin(HB_INFRARED_AVOIDANCE_LEFT_PIN, HB_INFRARED_AVOIDANCE_RIGHT_PIN);
}

void HandleInfraredAvoidance(){
    hbot.SetInfraredPin();
    if(hbot.left_read >= 38 && hbot.right_read <= 38){
        hbot.Speed = 80;
        hbot.TurnLeft();
        delay(300);
        hbot.KeepStop();
        delay(1000);
    }
    if(hbot.left_read <= 38 && hbot.right_read <= 38){
        hbot.Speed = 80;
        hbot.GoBack();
        delay(300);
        hbot.KeepStop();
        delay(1000);
    }
    if(hbot.left_read <= 38 && hbot.right_read >= 38){
        hbot.Speed = 80;
        hbot.TurnRight();
        delay(300);
        hbot.KeepStop();
        delay(1000);
    }
    if(hbot.left_read >= 38 && hbot.right_read >= 38){
        hbot.Speed = 100;
        hbot.GoForward();
    }
}
void loop()
{          
    switch(hbot.GetControlMode())
    {
        case E_INFRARED_AVOIDANCE:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_INFRARED_AVOIDANCE \n");
            HandleInfraredAvoidance();
            break;
        default:
            break;
    }
}
