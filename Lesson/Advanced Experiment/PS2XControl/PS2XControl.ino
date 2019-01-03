#include "Hummerbot.h"
#include "ProtocolParser.h"
#include "KeyMap.h"
#include "debug.h"

#define INPUT2_PIN 10 // PWMB
#define INPUT1_PIN 6  // DIRB  ---  right
#define INPUT4_PIN 5  // PWMA
#define INPUT3_PIN 9  // DIRA  ---  left
#define PS2X_CLK 11
#define PS2X_CMD 7
#define PS2X_CS  8
#define PS2X_DAT 4

ProtocolParser *mProtocol = new ProtocolParser();
Hummerbot hbot(mProtocol, INPUT2_PIN, INPUT1_PIN, INPUT3_PIN, INPUT4_PIN);
byte Ps2xStatus, Ps2xType;

void setup()
{
    Serial.begin(9600);
    hbot.init();
    hbot.SetControlMode(E_PS2_REMOTE_CONTROL);
    hbot.SetPs2xPin(HB_PS2X_CLK, HB_PS2X_CMD, HB_PS2X_ATT, HB_PS2X_DAT);
    hbot.SetSpeed(0);
    Ps2xType = hbot.mPs2x->readType();
}

void HandlePS2()
{
    static int vibrate = 0;
    byte PSS_X = 0, PSS_Y = 0;
    hbot.mPs2x->read_gamepad(false, vibrate); // read controller and set large motor to spin at 'vibrate' speed
    if (hbot.mPs2x->ButtonDataByte()) {
        if (hbot.mPs2x->Button(PSB_PAD_UP)) {     //will be TRUE as long as button is pressed
          hbot.GoForward();
        }
        if (hbot.mPs2x->Button(PSB_PAD_RIGHT)) {
          hbot.Drive(20);
        }
        if (hbot.mPs2x->Button(PSB_PAD_LEFT)) {
          hbot.Drive(160);
        }
        if (hbot.mPs2x->Button(PSB_PAD_DOWN)) {
          hbot.GoBack();
        }
        vibrate = hbot.mPs2x->Analog(PSAB_CROSS);  //this will set the large motor vibrate speed based on how hard you press the blue (X) button
        if (hbot.mPs2x->Button(PSB_CROSS)) {             //will be TRUE if button was JUST pressed OR released
          hbot.SpeedDown(5);
        }
        if (hbot.mPs2x->Button(PSB_TRIANGLE)) {
          hbot.SpeedUp(5);
        }
        if (hbot.mPs2x->Button(PSB_SQUARE)) {
          hbot.TurnLeft();
        }
        if (hbot.mPs2x->Button(PSB_CIRCLE)) {
          hbot.TurnRight();
        }
    }
      else {
        hbot.KeepStop();
      }
  delay(50);
}

void loop()
{
    mProtocol->RecevData();
    switch(hbot.GetControlMode())
    {
        case E_PS2_REMOTE_CONTROL:
            while (Ps2xStatus != 0) { //skip loop if no controller found
            delay(500);
            Ps2xStatus = hbot.ResetPs2xPin();
            Ps2xType = hbot.mPs2x->readType();
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_PS2_REMOTE_CONTROL \n");
            }
            if (Ps2xType != 2) {
              HandlePS2();
            }
            break;
        default:
            break;
    }
}

