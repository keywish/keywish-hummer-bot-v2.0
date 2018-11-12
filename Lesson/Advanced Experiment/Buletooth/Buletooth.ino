#include "Hummerbot.h"
#include "ProtocolParser.h"
#include "KeyMap.h"
#include "debug.h"

#define INPUT1_PIN 6   // PWMB
#define INPUT2_PIN 10  // DIRB  ---  right
#define INPUT3_PIN 5   // DIRA  ---  left
#define INPUT4_PIN 9   // PWMA

ProtocolParser *mProtocol = new ProtocolParser();
Hummerbot hbot(mProtocol, INPUT1_PIN, INPUT2_PIN, INPUT3_PIN, INPUT4_PIN);

void setup()
{
    Serial.begin(9600);
    hbot.init();
    hbot.SetControlMode(E_BLUETOOTH_CONTROL);
    hbot.SetSpeed(0);
}
//========================= bluetooth
void HandleBluetoothRemote()
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
            case E_CONTROL_MODE:
                hbot.SetControlMode(mProtocol->GetControlMode());
                break;
            case E_VERSION:
                break;
        }
    }
}

void loop()
{
    mProtocol->RecevData();
    switch(hbot.GetControlMode())
    {
        case E_BLUETOOTH_CONTROL:
            HandleBluetoothRemote();
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_BLUETOOTH_CONTROL \n");
            break;
        default:
            break;
    }
}

