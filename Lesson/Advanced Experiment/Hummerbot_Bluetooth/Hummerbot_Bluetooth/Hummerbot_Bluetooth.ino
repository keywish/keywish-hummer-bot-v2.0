/***********************************************************************
 *       __                                                          _
 *      / /        _____  __    __  _          _   (_)   ________   | |
 *     / /____   / _____) \ \  / / | |   __   | |  | |  (  ______)  | |_____
 *    / / ___/  | |_____   \ \/ /  | |  /  \  | |  | |  | |______   |  ___  |
 *   / /\ \     | |_____|   \  /   | | / /\ \ | |  | |  (_______ )  | |   | |
 *  / /  \ \__  | |_____    / /    | |/ /  \ \| |  | |   ______| |  | |   | |
 * /_/    \___\  \______)  /_/      \__/    \__/   |_|  (________)  |_|   |_|
 *
 *
 * KeyWay Tech firmware
 *
 * Copyright (C) 2015-2020
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, in version 3.
 * learn more you can see <http://www.gnu.org/licenses/>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#include "Hummerbot.h"
#include "ProtocolParser.h"
#include "KeyMap.h"
#include "debug.h"

#define INPUT2_PIN 10 // PWMB
#define INPUT1_PIN 6  // DIRB  ---  right
#define INPUT4_PIN 9  // PWMA
#define INPUT3_PIN 5  // DIRA  ---  left

ProtocolParser *mProtocol = new ProtocolParser();
Hummerbot hbot(mProtocol, INPUT2_PIN, INPUT1_PIN, INPUT3_PIN, INPUT4_PIN);

void setup()
{
    Serial.begin(9600);
    hbot.init();
    hbot.SetControlMode(E_BLUETOOTH_CONTROL);
    hbot.SetSpeed(100);
    Serial.println("Get last update from https://github.com/keywish/keywish-hummer-bot-v2.0");
}

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
