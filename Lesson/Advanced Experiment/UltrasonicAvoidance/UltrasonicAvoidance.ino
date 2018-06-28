#include "Hummerbot.h"
#include "Servo.h"
#include "debug.h"

#define HB_TRIGPIN 2
#define HB_ECHOPIN 3
#define HB_SERVOPIN 13

int E1 = 10;  // PWMB
int M1 = 6;   // DIRB  ---  right
int E2 = 9;   // PWMA
int M2 = 5;   // DIRA  ---  left

float Ul_value_mid;
float Ul_value_left;
float Ul_value_right;

Hummerbot hbot( E1, M1, E2, M2);

void setup()
{
    Serial.begin(9600);
    hbot.init();
    hbot.SetControlMode(E_ULTRASONIC_AVOIDANCE);
    hbot.SetUltrasonicPin(HB_TRIGPIN, HB_ECHOPIN, HB_SERVOPIN);
}

void HandleUltrasonic(){
    Ul_value_mid = hbot.Ultrasonic_Detection();
    if ((Ul_value_mid >= 50) && (Ul_value_mid <= 2000) ) {
        hbot.SetSpeed(90);
        hbot.GoForward();
    }
    if ((Ul_value_mid < 50) && (Ul_value_mid > 30) ) {
        hbot.SetSpeed(50);
        hbot.GoForward();
    }
    else if (Ul_value_mid <= 30) {
        stop:hbot.KeepStop();
        delay(300);

        hbot.servo_angle(195);
        delay(300);
        Ul_value_left = hbot.Ultrasonic_Detection();

        hbot.servo_angle(0);
        delay(300);
        Ul_value_right = hbot.Ultrasonic_Detection();

        hbot.servo_angle(85);
        if (Ul_value_left >= 20 && Ul_value_left <= 1000 && Ul_value_left > Ul_value_right) {
            hbot.SetSpeed_Left(100);
            hbot.SetSpeed_Right(70);
            hbot.TurnLeft_L_R();
            delay(900);
        }
        else if (Ul_value_left >= 1000) {
            hbot.SetSpeed_Left(70);
            hbot.SetSpeed_Right(100);
            hbot.TurnRight_L_R();
            delay(900);
        }
        else if (Ul_value_right >= 20 && Ul_value_right <= 1000 && Ul_value_right > Ul_value_left) {
            hbot.SetSpeed_Left(70);
            hbot.SetSpeed_Right(100);
            hbot.TurnRight_L_R();
            delay(900);
        }
        else if (Ul_value_right >= 1000) {
            hbot.SetSpeed_Left(100);
            hbot.SetSpeed_Right(70);
            hbot.TurnLeft_L_R();
            delay(900);
        }
        else if (Ul_value_right <= 20 && Ul_value_left <= 20) {
            hbot.SetSpeed(100);
            hbot.GoBack();
            delay(300);
            goto stop;
        }
    }
}

void loop()
{
    switch(hbot.GetControlMode())
    {
        case E_ULTRASONIC_AVOIDANCE:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_ULTRASONIC_AVOIDANCE \n");
            HandleUltrasonic();
            break;
        default:
            break;
    }
}
