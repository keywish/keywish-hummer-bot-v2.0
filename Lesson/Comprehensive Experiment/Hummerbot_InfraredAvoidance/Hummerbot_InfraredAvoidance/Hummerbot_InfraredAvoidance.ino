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
#define INFRARED_AVOIDANCE_LEFT_PIN A3
#define INFRARED_AVOIDANCE_RIGHT_PIN A4
#define IA_THRESHOLD 40

ProtocolParser *mProtocol = new ProtocolParser();
Hummerbot hbot(mProtocol, INPUT2_PIN, INPUT1_PIN, INPUT3_PIN, INPUT4_PIN);

void setup()
{
    Serial.begin(9600);
    hbot.init();
    hbot.SetControlMode(E_INFRARED_AVOIDANCE);
    hbot.SetInfraredAvoidancePin(HB_INFRARED_AVOIDANCE_LEFT_PIN, HB_INFRARED_AVOIDANCE_RIGHT_PIN);
    hbot.SetSpeed(100);
    Serial.println("Get last update from https://github.com/keywish/keywish-hummer-bot-v2.0");
}

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
        delay(706);
        /*The delay time and speed determine the turning angle. (100/speed) *425+((100-speed)*3.3)= equal to the delay time required for the current speed to turn 90 degrees.
          This formula has errors and external factors Impact, for reference only*/
    }
    else if((RightValue < IA_THRESHOLD)&&(LeftValue > IA_THRESHOLD))
    {
        hbot.SetSpeed(70);
        hbot.TurnLeft();
        delay(706);
        /*The delay time and speed determine the turning angle. (100/speed) *425+((100-speed)*3.3)= equal to the delay time required for the current speed to turn 90 degrees.
          This formula has errors and external factors Impact, for reference only*/
    }
    else if((RightValue < IA_THRESHOLD)&&(LeftValue < IA_THRESHOLD))
    {
        hbot.SetSpeed(80);
        hbot.Drive(0);
        delay(1210);
        /*The delay time and speed determine the turning angle. (100/speed) *425+((100-speed)*3.3)= equal to the delay time required for the current speed to turn 180 degrees.
          This formula has errors and external factors Impact, for reference only*/
        
    }
}

void loop()
{
    mProtocol->RecevData();
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
