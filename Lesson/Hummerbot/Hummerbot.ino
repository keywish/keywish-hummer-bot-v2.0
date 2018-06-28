
#include "Hummerbot.h"
#include "ProtocolParser.h"
#include "debug.h"

int E1 = 10;  // PWMB
int M1 = 6;   // DIRB  ---  right
int E2 = 9;   // PWMA
int M2 = 5;   // DIRA  ---  left

float Ul_value_mid;
float Ul_value_left;
float Ul_value_right;

const long Irkey_expedite1 = 0xFF6897;
const long Irkey_expedite2 = 0xFFB04F;
const long Irkey_forward = 0xFF18E7;
const long Irkey_back = 0xFF4AB5;
const long Irkey_stop = 0xFF38C7;
const long Irkey_left = 0xFF10EF;
const long Irkey_right = 0xFF5AA5;

ProtocolParser *mProtocol = new ProtocolParser();
Hummerbot hbot(mProtocol, E1, M1, E2, M2);
decode_results results;

void setup()
{
    Serial.begin(9600);
    hbot.init();
    hbot.SetControlMode(E_BLUETOOTH_CONTROL);
    hbot.SetIrPin(HB_IR_PIN);
    hbot.SetInfraredAvoidancePin(HB_INFRARED_AVOIDANCE_LEFT_PIN, HB_INFRARED_AVOIDANCE_RIGHT_PIN);
    hbot.SetUltrasonicPin(HB_TRIGPIN, HB_ECHOPIN, HB_SERVOPIN);
    hbot.SetInfraredTracingPin(HB_INFRARED_TRACING_PIN1, HB_INFRARED_TRACING_PIN2, HB_INFRARED_TRACING_PIN3);
    hbot.SetPs2xPin(HB_PS2X_CLK, HB_PS2X_CMD, HB_PS2X_ATT, HB_PS2X_DAT);
    hbot.SetSpeed(100);
}
//=========================== Ultrasonic_Infrared =====
void HandleUltrasonic_Infrared(){
    hbot.SetInfraredPin();
    Ul_value_mid = hbot.Ultrasonic_Detection();

    if ((Ul_value_mid >= 50) && (Ul_value_mid <= 2000) && (hbot.left_read >= 38) && (hbot.right_read >= 38)) {
        hbot.SetSpeed(90);
        hbot.GoForward();
    }
    if ((Ul_value_mid < 50) && (Ul_value_mid > 30) && (hbot.left_read >= 38) && (hbot.right_read >= 38)) {
        hbot.SetSpeed(90);
        hbot.GoForward();
    }
    if ((hbot.left_read <= 38) && (hbot.right_read >= 38) && (Ul_value_mid >= 30 && Ul_value_mid <= 1000)) {
        hbot.SetSpeed(100);
        hbot.TurnRight();
        delay(200);
        hbot.KeepStop();
    }
    if ((hbot.left_read >= 38) && (hbot.right_read <= 38) && (Ul_value_mid >= 30 && Ul_value_mid <= 1000)) {
        hbot.SetSpeed(100);
        hbot.TurnLeft();
        delay(200);
        hbot.KeepStop();
    }

    else if (Ul_value_mid <= 30) {
        stop:hbot.KeepStop();
        delay(300);

        hbot.servo_angle(155);
        delay(300);

        Ul_value_left = hbot.Ultrasonic_Detection();
        hbot.servo_angle(0);
        delay(300);

        Ul_value_right = hbot.Ultrasonic_Detection();
        hbot.servo_angle(65);

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
            hbot.SetSpeed(100);
            hbot.GoBack();
            delay(500);
            goto stop;
        }
    }
}
//=============================Infrared tracking
void HandleInfraredTracing(void)
{
    switch (hbot.mInfraredTracing->getValue()) {
        case IT_ALL_BLACK:
            hbot.KeepStop();
            break;
        case IT_ALL_WHITE:
            hbot.SetSpeed(70);
            hbot.GoForward();
            break;
        case IT_FORWARD:        
            hbot.SetSpeed(70);
            hbot.GoForward();
            break;

        case IT_RIGHT1:      
            hbot.SetSpeed(70);
            hbot.TurnRight();
            break;
        case IT_LEFT1: 
            hbot.SetSpeed(70);
            hbot.TurnLeft();
            break;
        default:
            hbot.KeepStop();
            break;
    }
}
//========================= bluetooth
void HandleBluetoothRemote()
{
    if (mProtocol->ParserPackage())
    {
        switch(mProtocol->GetRobotControlFun())
        {   
            case E_INFO:
                break;
            case E_ROBOT_CONTROL_DIRECTION:
                hbot.Drive(mProtocol->GetRobotDegree());
                break;
            case E_ROBOT_CONTROL_SPEED:
                hbot.SetSpeed(mProtocol->GetRobotSpeed());
                break ;
            case E_VERSION:
                break;  
        }
    }
}
//===============================红外
void HandleInfaredRemote()
{
    switch(results.value)
    {
        case Irkey_expedite1:
            hbot.SetSpeed(hbot.Speed + 5);
            DEBUG_LOG(DEBUG_LEVEL_INFO, "hbot.Speed = %d \n",hbot.Speed);
            break;
        case Irkey_expedite2:
            hbot.SetSpeed(hbot.Speed - 5);
            DEBUG_LOG(DEBUG_LEVEL_INFO, "hbot.Speed = %d \n",hbot.Speed);
            break;
        case Irkey_forward:
            hbot.GoForward();
            break;
        case Irkey_back:
            hbot.GoBack();
            break;
        case Irkey_stop:
            hbot.KeepStop();
            break;
        case Irkey_left:
            hbot.TurnLeft();
            break;
        case Irkey_right:
            hbot.TurnRight();
            break;
        default:
            break;
    }
    hbot.mIrRecv->resume();
}
//====================================InfraredAvoidance
void HandleInfraredAvoidance(){
    hbot.SetInfraredPin();
    if(hbot.left_read >= 38 && hbot.right_read <= 38){
        hbot.TurnLeft();
        delay(300);
        hbot.KeepStop();
        delay(1000);
    }
    if(hbot.left_read <= 38 && hbot.right_read <= 38){
        hbot.GoBack();
        delay(300);
        hbot.KeepStop();
        delay(1000);
    }
    if(hbot.left_read <= 38 && hbot.right_read >= 38){
        hbot.TurnRight();
        delay(300);
        hbot.KeepStop();
        delay(1000);
    }
    if(hbot.left_read >= 38 && hbot.right_read >= 38){
        hbot.GoForward();
    }
}
//===============================================ps2
void HandlePS2()
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
    mProtocol->RecevData();
    
    switch(hbot.GetControlMode())
    {
        case E_BLUETOOTH_CONTROL:
            HandleBluetoothRemote();
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_BLUTOOTH_CONTROL \n");
            break;
        case E_INFRARED_REMOTE_CONTROL:
            if  (hbot.mIrRecv->decode(&results)) {
              DEBUG_LOG(DEBUG_LEVEL_INFO, "results.value = %lx \n",results.value);
              HandleInfaredRemote();
            }
            break;
        case E_INFRARED_TRACKING_MODE:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_INFRARED_TRACKING \n");
            HandleInfraredTracing();
            break;
        case E_INFRARED_AVOIDANCE:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_INFRARED_AVOIDANCE \n");
            HandleInfraredAvoidance();
            break;
        case E_ULTRASONIC_AVOIDANCE:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_ULTRASONIC_AVOIDANCE \n");
            HandleUltrasonic_Infrared();
            break;
        case E_PS2_REMOTE_CONTROL:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_PS2_REMOTE_CONTROL \n");
            HandlePS2();
            break;
        default:
            break;
    }
}
