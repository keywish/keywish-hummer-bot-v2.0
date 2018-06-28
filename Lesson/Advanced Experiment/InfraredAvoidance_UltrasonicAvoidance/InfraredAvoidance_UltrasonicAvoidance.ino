
#include "Hummerbot.h"
#include "debug.h"

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
    hbot.SetInfraredAvoidancePin(HB_INFRARED_AVOIDANCE_LEFT_PIN, HB_INFRARED_AVOIDANCE_RIGHT_PIN);
    hbot.SetUltrasonicPin(HB_TRIGPIN, HB_ECHOPIN, HB_SERVOPIN);
}

void HandleUltrasonic_Infrared(){
    hbot.SetInfraredPin();
    Ul_value_mid = hbot.Ultrasonic_Detection(); 

    if ((Ul_value_mid >= 50) && (Ul_value_mid <= 2000) && (hbot.left_read >= 38) && (hbot.right_read >= 38)) {
        hbot.Speed = 90;
        hbot.GoForward();
    }
    if ((Ul_value_mid < 50) && (Ul_value_mid > 30) && (hbot.left_read >= 38) && (hbot.right_read >= 38)) {
        hbot.Speed = 50;
        hbot.GoForward();
    }
    if ((hbot.left_read <= 38) && (hbot.right_read >= 38) && (Ul_value_mid >= 30 && Ul_value_mid <= 1000)) {
        hbot.Speed = 100;
        hbot.TurnRight();
        delay(200);
        hbot.KeepStop();
    }
    if ((hbot.left_read >= 38) && (hbot.right_read <= 38) && (Ul_value_mid >= 30 && Ul_value_mid <= 1000)) {
        hbot.Speed = 100;
        hbot.TurnLeft();
        delay(200);
        hbot.KeepStop();
    }

    else if (Ul_value_mid <= 30) {
        stop:hbot.KeepStop();
        delay(300);

        hbot.servo_angle(190);
        delay(300);
        Ul_value_left = hbot.Ultrasonic_Detection();

        hbot.servo_angle(0);
        delay(300);
        Ul_value_right = hbot.Ultrasonic_Detection();

        hbot.servo_angle(80);

        if (Ul_value_left >= 20 && Ul_value_left <= 1000 && Ul_value_left > Ul_value_right) {
            hbot.SetSpeed_Left(100);
            hbot.SetSpeed_Right(70);
            hbot.TurnLeft_L_R();
            delay(300);
        }
        else if (Ul_value_left >= 1000) {
            hbot.SetSpeed_Left(70);
            hbot.SetSpeed_Right(100);
            hbot.TurnRight_L_R();
            delay(300);
        }
        else if (Ul_value_right >= 20 && Ul_value_right <= 1000 && Ul_value_right > Ul_value_left) {
            hbot.SetSpeed_Left(70);
            hbot.SetSpeed_Right(100);
            hbot.TurnRight_L_R();
            delay(300);
        }
        else if (Ul_value_right >= 1000) {
            hbot.SetSpeed_Left(100);
            hbot.SetSpeed_Right(70);
            hbot.TurnLeft_L_R();
            delay(300);
        }
        else if (Ul_value_right <= 20 && Ul_value_left <= 20) {
            hbot.Speed = 100;
            hbot.GoBack();
            delay(500);
            goto stop;
        }
    }
}
void loop()
{
    switch(hbot.GetControlMode())
    {
        case E_ULTRASONIC_AVOIDANCE:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_INFRARED_AVOIDANCE \n");
            HandleUltrasonic_Infrared();
            break;
        default:
            break;
    }
}
