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
#define SERVO_PIN 13
#define ECHO_PIN 3
#define TRIG_PIN 2
#define UL_LIMIT_MIN 50
#define UL_LIMIT_MID 40
#define UL_LIMIT_MAX 2000

ProtocolParser *mProtocol = new ProtocolParser();
Hummerbot hbot(mProtocol, INPUT2_PIN, INPUT1_PIN, INPUT3_PIN, INPUT4_PIN);

void setup()
{
    Serial.begin(9600);
    hbot.init();
    hbot.SetControlMode(E_ULTRASONIC_AVOIDANCE);
    hbot.SetUltrasonicPin(HB_TRIGPIN, HB_ECHOPIN, HB_SERVOPIN);
    hbot.SetSpeed(100);
    hbot.mUltrasonic->SetServoBaseDegree(90);
    hbot.mUltrasonic->SetServoDegree(90);
    Serial.println("Get last update from https://github.com/keywish/keywish-hummer-bot-v2.0");
}

void HandleUltrasonicAvoidance()
{
    uint16_t UlFrontDistance,UlLeftDistance,UlRightDistance;
    UlFrontDistance =  hbot.mUltrasonic->GetUltrasonicFrontDistance();
    if ((UlFrontDistance > UL_LIMIT_MID) && (UlFrontDistance < UL_LIMIT_MAX))
    {
        hbot.SetSpeed(100);
        hbot.GoForward();
    }
    else if ((UlFrontDistance < UL_LIMIT_MIN) || (UlFrontDistance > UL_LIMIT_MAX))
    {
        hbot.KeepStop();
        UlRightDistance = hbot.mUltrasonic->GetUltrasonicRightDistance();
        UlLeftDistance = hbot.mUltrasonic->GetUltrasonicLeftDistance();
        if((UlRightDistance > UL_LIMIT_MIN) && (UlRightDistance < UL_LIMIT_MAX) && (UlRightDistance > UlLeftDistance))
        {
            hbot.SetSpeed(80);
            hbot.TurnRight();
            delay(605);
            /*The delay time and speed determine the turning angle. (100/speed) *425+((100-speed)*3.3)= equal to the delay time required for the current speed to turn 90 degrees.
              This formula has errors and external factors Impact, for reference only*/
        }
        else if((UlLeftDistance > UL_LIMIT_MIN) && (UlLeftDistance < UL_LIMIT_MAX) && (UlLeftDistance > UlRightDistance))
        {
            hbot.SetSpeed(80);
            hbot.TurnLeft();
            delay(605);
            /*The delay time and speed determine the turning angle. (100/speed) *425+((100-speed)*3.3)= equal to the delay time required for the current speed to turn 90 degrees.
              This formula has errors and external factors Impact, for reference only*/
        }
        else if((UlRightDistance < UL_LIMIT_MIN) && (UlLeftDistance < UL_LIMIT_MIN) )
        {
            hbot.SetSpeed(80);
            hbot.Drive(0);
            delay(1210);
            /*The delay time and speed determine the turning angle. (100/speed) *425+((100-speed)*3.3)= equal to the delay time required for the current speed to turn 180 degrees.
              This formula has errors and external factors Impact, for reference only*/
        }
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
