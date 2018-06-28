
#include "Hummerbot.h"
#include "debug.h"

int E1 = 10;  // PWMB
int M1 = 6;   // DIRB  ---  right
int E2 = 9;   // PWMA
int M2 = 5;   // DIRA  ---  left

const long Irkey_expedite1 = 0xFF6897;
const long Irkey_expedite2 = 0xFFB04F;
const long Irkey_forward = 0xFF18E7;
const long Irkey_back = 0xFF4AB5;
const long Irkey_stop = 0xFF38C7;
const long Irkey_left = 0xFF10EF;
const long Irkey_right = 0xFF5AA5;

Hummerbot hbot( E1, M1, E2, M2);
decode_results results;

void setup()
{
    Serial.begin(9600);
    hbot.init();
    hbot.SetControlMode(E_INFRARED_REMOTE_CONTROL);
    hbot.SetIrPin(HB_IR_PIN);
    hbot.SetSpeed(50);
}

void HandleInfaredRemote()
{
    switch(results.value)
    {
        case Irkey_expedite1:
            hbot.SetSpeed(hbot.Speed + 5);
            DEBUG_LOG(DEBUG_LEVEL_INFO, "hbot.Speed = %d \n",hbot.Speed);
            break;
        case Irkey_expedite2:
            hbot.SetSpeed(hbot.Speed - 5);
            DEBUG_LOG(DEBUG_LEVEL_INFO, "hbot.Speed = %d \n",hbot.Speed);
            break;
        case Irkey_forward:
            hbot.GoForward();
            break;
        case Irkey_back:
            hbot.GoBack();
            break;
        case Irkey_stop:
            hbot.KeepStop();
            break;
        case Irkey_left:
            hbot.TurnLeft();
            break;
        case Irkey_right:
            hbot.TurnRight();
            break;
        default:
            break;
    }
    hbot.mIrRecv->resume();
}

void loop()
{         
    switch(hbot.GetControlMode())
    {
        case E_INFRARED_REMOTE_CONTROL:
            if  (hbot.mIrRecv->decode(&results)) {
              DEBUG_LOG(DEBUG_LEVEL_INFO, "results.value = %lx \n",results.value);
              HandleInfaredRemote();
            }
            break;
        default:
            break;
    }
}
