
#include "Hummerbot.h"
#include "ProtocolParser.h"
#include "debug.h"

int E1 = 5;  //PWMA
int M1 = 9;  //DIRA  ---  left
int E2 = 6;  //PWMB
int M2 = 10; //DIRB  ---  right

const long Irkey_expedite1 = 0xFF6897;
const long Irkey_expedite2 = 0xFFB04F;
const long Irkey_forward = 0xFF18E7;
const long Irkey_back = 0xFF4AB5;
const long Irkey_stop = 0xFF38C7;
const long Irkey_left = 0xFF10EF;
const long Irkey_right = 0xFF5AA5;

ProtocolParser *mProtocol = new ProtocolParser();
Hummerbot hbot(mProtocol, E1, M1, E2, M2);
decode_results results;

void setup()
{
    DEBUG_LOG(DEBUG_LEVEL_INFO, "setup \n");
    Serial.begin(9600);
    hbot.init();
    hbot.SetControlMode(E_INFRARED_REMOTE_CONTROL);
    hbot.SetIrPin(HB_IR_PIN);
    hbot.SetInfraredAvoidancePin(HB_INFRARED_AVOIDANCE_LEFT_PIN, HB_INFRARED_AVOIDANCE_RIGHT_PIN);
    hbot.SetUltrasonicPin(HB_TRIGPIN, HB_ECHOPIN, HB_SEVOPIN);
    hbot.SetInfraredTracingPin(HB_INFRARED_TRACING_PIN1, HB_INFRARED_TRACING_PIN2, HB_INFRARED_TRACING_PIN3);
}

void HandleBloothRemote()
{
    if (mProtocol->ParserPackage())
    {
        switch(mProtocol->GetRobotControlFun())
        {   
            case E_INFO:
                break;
            case E_ROBOT_CONTROL_DIRECTION:
                hbot.Drive(mProtocol->GetRobotDegree());
                break;
            case E_ROBOT_CONTROL_SPEED:
                hbot.SetSpeed(mProtocol->GetRobotSpeed());
                break ;
            case E_VERSION:
                break;  
        }
   }
}

void HandleInfaredRemote()
{
    switch(results.value)
    {
        case Irkey_expedite1:
            hbot.SetSpeed(hbot.Speed + 5);
        case Irkey_expedite2:
            hbot.SetSpeed(hbot.Speed - 5);
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
    mProtocol->RecevData();
    
    switch(hbot.GetControlMode())
    {
        case E_BLUTOOTH_CONTROL:
            HandleBloothRemote();
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_BLUTOOTH_CONTROL \n");
            break;
        case E_INFRARED_REMOTE_CONTROL:
            if  (hbot.mIrRecv->decode(&results)) {
              DEBUG_LOG(DEBUG_LEVEL_INFO, "results.value = %lx \n",results.value);
              HandleInfaredRemote();
            }
            break;
        case E_INFRARED_TRACKING_MODE:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_INFRARED_TRACKING \n");
            break;
        case E_INFRARED_AVOIDANCE:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_INFRARED_AVOIDANCE \n");
            break;
        case E_ULTRASONIC_AVOIDANCE:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_ULTRASONIC_AVOIDANCE \n");
            break;
        case E_PS2_REMOTE_CONTROL:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_PS2_REMOTE_CONTROL \n");
            break;
        case E_NRF24L01_CONTROL:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_NRF24L01_CONTROL \n");
            break;
        default:
            break;
    }
}

