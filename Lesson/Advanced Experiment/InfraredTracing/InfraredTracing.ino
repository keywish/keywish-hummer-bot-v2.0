
#include "Hummerbot.h"
#include "debug.h"

int E1 = 10;  // PWMB
int M1 = 6;   // DIRB  ---  right
int E2 = 9;   // PWMA
int M2 = 5;   // DIRA  ---  left

Hummerbot hbot( E1, M1, E2, M2);

void setup()
{
    Serial.begin(9600);
    hbot.init();
    hbot.SetControlMode(E_INFRARED_TRACKING_MODE);
    hbot.SetInfraredTracingPin(HB_INFRARED_TRACING_PIN1, HB_INFRARED_TRACING_PIN2, HB_INFRARED_TRACING_PIN3);
}

void HandleInfraredTracing(void)
{
    switch (hbot.mInfraredTracing->getValue()) {
        case IT_ALL_BLACK:
            hbot.KeepStop();
            break;
        case IT_ALL_WHITE:
            hbot.SetSpeed(70);
            hbot.GoForward();
            break;
        case IT_FORWARD:        
            hbot.SetSpeed(70);
            hbot.GoForward();
            break;

        case IT_RIGHT1:      
            hbot.SetSpeed(70);
            hbot.TurnRight();
            break;
        case IT_LEFT1: 
            hbot.SetSpeed(70);
            hbot.TurnLeft();
            break;
        default:
            hbot.KeepStop();
            break;
    }
}
void loop()
{         
    switch(hbot.GetControlMode())
    {
        case E_INFRARED_TRACKING_MODE:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_INFRARED_TRACKING \n");
            HandleInfraredTracing();
            break;
        default:
            break;
    }
}
