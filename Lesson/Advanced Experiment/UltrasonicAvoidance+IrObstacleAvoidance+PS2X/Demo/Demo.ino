
#include "Hummerbot.h"
#include "debug.h"

int E1 = 10;  // PWMB
int M1 = 6;   // DIRB  ---  right
int E2 = 9;   // PWMA
int M2 = 5;   // DIRA  ---  left

float Ul_value_mid;
float Ul_value_left;
float Ul_value_right;

int horizontal_direction;
int vertical_direction;
float distance;

Hummerbot hbot( E1, M1, E2, M2);

void setup()
{
    Serial.begin(9600);
    hbot.init();
    hbot.SetInfraredAvoidancePin(HB_INFRARED_AVOIDANCE_LEFT_PIN, HB_INFRARED_AVOIDANCE_RIGHT_PIN);
    hbot.SetUltrasonicPin(HB_TRIGPIN, HB_ECHOPIN, HB_SERVOPIN);
    hbot.SetPs2xPin(HB_PS2X_CLK, HB_PS2X_CMD, HB_PS2X_ATT, HB_PS2X_DAT);
}

void HandleDemo(){
    hbot.ps2x->read_gamepad(false, 0); 

    if ( hbot.ps2x->Button( PSB_R1)) {
    horizontal_direction = hbot.ps2x->Analog(PSS_RX); 
        if ( horizontal_direction < 5) {
            hbot.SetSpeed(100);
            hbot.TurnLeft(); 
        } 
        else if ( horizontal_direction > 250) { 
            hbot.SetSpeed(100);
            hbot.TurnRight(); 
        } 
        else {
            hbot.KeepStop();
        }
    }
    if ( hbot.ps2x->Button(PSB_R1)) {
        vertical_direction = hbot.ps2x->Analog(PSS_RY); 
        if ( vertical_direction < 5) {
            distance = hbot.Ultrasonic_Detection(); 
        if ( distance >= 20) {
            hbot.SetSpeed(100);
            hbot.GoForward();
        }
        else {
            hbot.KeepStop();
        }
        } 
        else if ( vertical_direction > 250) { 
            hbot.SetSpeed(100);
            hbot.GoBack();
        }
    }
    else {
        hbot.KeepStop();
    }
    delay(50);

    hbot.SetInfraredPin();
    if (hbot.left_read >= 38 && hbot.right_read <= 38) { 
        hbot.SetSpeed(100);
        hbot.TurnLeft();
        delay(100);
        hbot.KeepStop();
    }

    if (hbot.left_read <= 38 && hbot.right_read <= 38) {
        hbot.SetSpeed(100);
        hbot.GoBack();
        delay(500);
        hbot.KeepStop();
    }

    if (hbot.left_read <= 38 && hbot.right_read >= 38) {
        hbot.SetSpeed(100);
        hbot.TurnRight();
        delay(100);
        hbot.KeepStop();
    }
}
void loop()
{         
    HandleDemo();
}
