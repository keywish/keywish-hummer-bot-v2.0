#include "Hummerbot.h"
#include "ProtocolParser.h"
#include "KeyMap.h"
#include "debug.h"

#define INPUT2_PIN 10 // PWMB
#define INPUT1_PIN 6  // DIRB  ---  right
#define INPUT4_PIN 5  // PWMA
#define INPUT3_PIN 9  // DIRA  ---  left
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
    hbot.SetSpeed(0);
}

void HandleInfraredTracing(void)
{
      static byte old;
      switch (hbot.mInfraredTracing->getValue()) {
        case IT_ALL_BLACK:
          hbot.KeepStop();
          break;
        case IT_ALL_WHITE:
          if(old == IT_RIGHT1){ 
              while(hbot.mInfraredTracing->getValue()==IT_ALL_WHITE){
                  hbot.SetSpeed(70);
                  hbot.Drive(174);
              }
            old = 0;
            break;
            } if(old == IT_LEFT1){
                while(hbot.mInfraredTracing->getValue()==IT_ALL_WHITE){
                    hbot.SetSpeed(70);
                    hbot.Drive(6);
                  }
              old = 0;
              break;
            }  if(old == IT_RIGHT2){
                while(hbot.mInfraredTracing->getValue()==IT_ALL_WHITE){
                    hbot.SetSpeed(70);
                    hbot.Drive(150);
                  }
              old = 0;
              break;
            } if(old == IT_LEFT2){
                while(hbot.mInfraredTracing->getValue()==IT_ALL_WHITE){
                    hbot.SetSpeed(70);
                    hbot.Drive(30);
                  }
              old = 0;
              break;
              }
          hbot.KeepStop();
          break;
        case IT_CENTER:
          hbot.SetSpeed(45);
          hbot.GoForward();
          break;
        case IT_RIGHT1:
          hbot.SetSpeed(70);
          hbot.Drive(174);
          old = IT_RIGHT1;
          break;
        case IT_RIGHT2:
          hbot.SetSpeed(70);
          hbot.Drive(150);
          old = IT_RIGHT2;
          break;
        case IT_LEFT1:
          hbot.SetSpeed(70);
          hbot.Drive(6);
          old = IT_LEFT1;
          break;
        case IT_LEFT2:
          hbot.SetSpeed(70);
          hbot.Drive(30);
          old = IT_LEFT2;
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
            hbot.SendTracingSignal();
            break;
        default:
            break;
    }
}

