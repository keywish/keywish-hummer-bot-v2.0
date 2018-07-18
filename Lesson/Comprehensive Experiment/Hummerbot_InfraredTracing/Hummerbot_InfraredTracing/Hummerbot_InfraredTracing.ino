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
#define INFRARED_TRACING_PIN1 A0
#define INFRARED_TRACING_PIN2 A1
#define INFRARED_TRACING_PIN3 A2

ProtocolParser *mProtocol = new ProtocolParser();
Hummerbot hbot(mProtocol, INPUT2_PIN, INPUT1_PIN, INPUT3_PIN, INPUT4_PIN);

void setup()
{
    Serial.begin(9600);
    hbot.init();
    hbot.SetControlMode(E_INFRARED_TRACKING_MODE);
    hbot.SetInfraredTracingPin(HB_INFRARED_TRACING_PIN1, HB_INFRARED_TRACING_PIN2, HB_INFRARED_TRACING_PIN3);
    Serial.println("Get last update from https://github.com/keywish/keywish-hummer-bot-v2.0");
}
void HandleInfraredTracing(void)
{
      switch (hbot.mInfraredTracing->getValue()) {
        case IT_ALL_BLACK:
        case IT_ALL_WHITE:
          hbot.KeepStop();
          break;
        case IT_CENTER:
          hbot.SetSpeed(80);
          hbot.GoForward();
          break;
        case IT_RIGHT1:
          hbot.SetSpeed(60);
          hbot.Drive(160);
          break;
        case IT_LEFT1:
          hbot.SetSpeed(60);
          hbot.Drive(30);
          break;
  }
}

void loop()
{
    mProtocol->RecevData();
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
