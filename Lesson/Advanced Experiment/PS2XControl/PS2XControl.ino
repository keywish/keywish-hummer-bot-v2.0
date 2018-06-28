
#include "Hummerbot.h"
#include "debug.h"

int E1 = 10;  // PWMB
int M1 = 6;   // DIRB  ---  right
int E2 = 9;   // PWMA
int M2 = 5;   // DIRA  ---  left

Hummerbot hbot( E1, M1, E2, M2);
void setup()
{
    Serial.begin(9600);
    hbot.init();
    hbot.SetControlMode(E_PS2_REMOTE_CONTROL);
    hbot.SetPs2xPin(HB_PS2X_CLK, HB_PS2X_CMD, HB_PS2X_ATT, HB_PS2X_DAT);
    hbot.SetSpeed(80);
}
void Ps2x_control()
{
    hbot.ps2x->read_gamepad(false, 0);
    if ( hbot.ps2x->Button(PSB_L3) || hbot.ps2x->Button(PSB_R3)) {
        hbot.KeepStop();
    }
    if ( hbot.ps2x->Button(PSB_PAD_UP)) {
        hbot.GoForward();
    }
    if ( hbot.ps2x->Button(PSB_R2) || (hbot.ps2x->Button(PSB_PAD_RIGHT))) {
        hbot.SetSpeed(80);
        hbot.TurnRight();
        delay(200);
    }
    if ( hbot.ps2x->Button(PSB_L2) || (hbot.ps2x->Button(PSB_PAD_LEFT))) {
        hbot.SetSpeed(80);
        hbot.TurnLeft();
        delay(200);
    }
    if ( hbot.ps2x->Button(PSB_PAD_DOWN)) {
        hbot.GoBack();
    }
    if ( hbot.ps2x->Button(PSB_L1)) {// print stick values if either is TRUE 
        hbot.L_speed_con = hbot.ps2x->Analog(PSS_LY);
        hbot.SetSpeed((hbot.L_speed_con*10)/25.5);
        hbot.GoBack();
    }
    if ( hbot.ps2x->Button(PSB_R1)) {// print stick values if either is TRUE
        hbot.R_speed_con = hbot.ps2x->Analog(PSS_RY);
        hbot.SetSpeed((hbot.R_speed_con*10)/25.5);
        hbot.GoForward();
    }
    delay(50);  
}
void loop()
{         
    switch(hbot.GetControlMode())
    {
        case E_PS2_REMOTE_CONTROL:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_PS2_REMOTE_CONTROL \n");
            Ps2x_control();
            break;
        default:
            break;
    }
}
