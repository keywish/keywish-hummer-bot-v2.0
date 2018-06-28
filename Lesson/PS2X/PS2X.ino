#include "PS2X_lib.h"
int E1 = 5; //PWMA
int M1 = 9; //DIRA****************************************left
int E2 = 6; //PWMB
int M2 = 10; //DIRB****************************************right

PS2X ps2x;

int error = 0;
byte type = 0;
byte vibrate = 0;
int vb;
int KK;

void setup()
{
  Serial.begin(9600);
  error = ps2x.config_gamepad(11,7,8,4, true, true);
}

void loop()
{
  ps2x.read_gamepad(false, vibrate);
  if(ps2x.Button(PSB_PAD_UP))
  {
      Serial.println("PSB_PAD_UP ");
  }
  /*
  if(ps2x.Button(PSB_L3))
  {
   int val=0;
   digitalWrite(M1,0);
   analogWrite(E1, val); //the speed value of motorA is 255
   digitalWrite(M2,0);
   analogWrite(E2, val); //the speed value of motorB is 255
  }
  if(ps2x.Button(PSB_PAD_UP))
  {
    int val=180;
    digitalWrite(M1,0);
    analogWrite(E1, val); //the speed value of motorA is 255
    digitalWrite(M2,0);
    analogWrite(E2, val); //the speed value of motorB is 255
   }
  if(ps2x.Button(PSB_R2)||(ps2x.Button(PSB_PAD_RIGHT)))
  {
    int val=200;
    digitalWrite(E1,0);
    analogWrite(M1, val); //the speed value of motorA is 255
    digitalWrite(M2,0);
    analogWrite(E2, val); //the speed value of motorB is 255
    delay(200);
    digitalWrite(M1,0);
    analogWrite(E1, 0); //the speed value of motorA is 255
    digitalWrite(M2,0);
    analogWrite(E2, 0); //the speed value of motorB is 255
  }
  if(ps2x.Button(PSB_L2)||(ps2x.Button(PSB_PAD_LEFT)))
  {
    int val=200;
    digitalWrite(M1,0);
    analogWrite(E1, val); //the speed value of motorA is 255
    digitalWrite(E2,0);
    analogWrite(M2, val); //the speed value of motorB is 255
    delay(200);
    digitalWrite(M1,0);
    analogWrite(E1, 0); //the speed value of motorA is 255
    digitalWrite(M2,0);
    analogWrite(E2, 0); //the speed value of motorB is 255
  }
  if(ps2x.Button(PSB_PAD_DOWN))
  {
    int val=180;
    digitalWrite(E1,0);
    analogWrite(M1, val); //the speed value of motorA is 255
    digitalWrite(E2,0);
    analogWrite(M2, val); //the speed value of motorB is 255
    }
   if(ps2x.Button(PSB_L1))// print stick values if either is TRUE
   {
     vb = ps2x.Analog(PSS_LY);
     digitalWrite(M1,0);
     analogWrite(E1, vb); //the speed value of motorA is 255
     digitalWrite(M2,0);
     analogWrite(E2, vb); //the speed value of motorB is 255
   }
   if(ps2x.Button(PSB_R1))// print stick values if either is TRUE
   {
     KK = ps2x.Analog(PSS_RY);
     analogWrite(M1,KK);
     analogWrite(E1, 0); //the speed value of motorA is 255
     analogWrite(M2,KK);
     analogWrite(E2,0); //the speed value of motorB is 255
   } 
   */
   
    delay(50);
}
