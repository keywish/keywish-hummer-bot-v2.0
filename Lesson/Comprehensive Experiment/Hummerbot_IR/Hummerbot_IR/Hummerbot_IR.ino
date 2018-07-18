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
#define IR_PIN 12

ProtocolParser *mProtocol = new ProtocolParser();
Hummerbot hbot(mProtocol, INPUT2_PIN, INPUT1_PIN, INPUT3_PIN, INPUT4_PIN);


void setup()
{
    Serial.begin(9600);
    hbot.init();
    hbot.SetControlMode(E_INFRARED_REMOTE_CONTROL);
    hbot.SetIrPin(HB_IR_PIN);
    hbot.SetSpeed(100);
    Serial.println("Get last update from https://github.com/keywish/keywish-hummer-bot-v2.0");
}

void HandleInfaredRemote(byte irKeyCode)
{
    switch ((E_IR_KEYCODE)hbot.mIrRecv->getIrKey(irKeyCode)) {
        case IR_KEYCODE_STAR:
          hbot.SpeedUp(10);
          DEBUG_LOG(DEBUG_LEVEL_INFO, "hbot.Speed = %d \n", hbot.Speed);
          break;
        case IR_KEYCODE_POUND:
          DEBUG_LOG(DEBUG_LEVEL_INFO, " start Degree = %d \n", hbot.Degree);
          hbot.SpeedDown(10);
          break;
        case IR_KEYCODE_UP:
          hbot.GoForward();
          break;
        case IR_KEYCODE_DOWN:
          hbot.GoBack();
          break;
        case IR_KEYCODE_OK:
          hbot.KeepStop();
          break;
        case IR_KEYCODE_LEFT:
          hbot.TurnLeft();
          break;
        case IR_KEYCODE_RIGHT:
          hbot.TurnRight();
          break;
        default:
          break;
    }
}

void loop()
{
    mProtocol->RecevData();
    switch(hbot.GetControlMode())
    {
        case E_INFRARED_REMOTE_CONTROL:
            byte irKeyCode;
            if (irKeyCode = hbot.mIrRecv->getCode()) {
            DEBUG_LOG(DEBUG_LEVEL_INFO, "irKeyCode = %lx \n", irKeyCode);
            HandleInfaredRemote(irKeyCode);
            delay(110);
            }
            else {
                if (hbot.GetStatus() != E_STOP ) {
                    hbot.KeepStop();
                    }
                 }
            break;
        default:
            break;
    }
}
