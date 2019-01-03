#include "Hummerbot.h"
#include "ProtocolParser.h"
#include "KeyMap.h"
#include "debug.h"

#define INPUT1_PIN 6   // PWMB
#define INPUT2_PIN 10  // DIRB  ---  right
#define INPUT4_PIN 9   // PWMA
#define INPUT3_PIN 5   // DIRA  ---  left
#define IR_PIN 12
#define SERVO_PIN 13
#define ECHO_PIN 3
#define TRIG_PIN 2
#define PS2X_CLK 11
#define PS2X_CMD 7
#define PS2X_CS  8
#define PS2X_DAT 4
#define INFRARED_TRACING_PIN1 A0
#define INFRARED_TRACING_PIN2 A1
#define INFRARED_TRACING_PIN3 A2
#define INFRARED_AVOIDANCE_LEFT_PIN A3
#define INFRARED_AVOIDANCE_RIGHT_PIN A4

ProtocolParser *mProtocol = new ProtocolParser();
Hummerbot hbot(mProtocol, INPUT1_PIN, INPUT2_PIN, INPUT3_PIN, INPUT4_PIN);
byte Ps2xStatus, Ps2xType;

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
    hbot.SetSpeed(0);
    Ps2xType = hbot.mPs2x->readType();
    hbot.mUltrasonic->SetServoBaseDegree(70);
    hbot.mUltrasonic->SetServoDegree(90);
}
//=========================== Ultrasonic_Infrared =====
void HandleUltrasonicInfraredAvoidance(void)
{
    uint16_t RightValue,LeftValue;
    uint16_t UlFrontDistance,UlLeftDistance,UlRightDistance;
    RightValue = hbot.mInfraredAvoidance->GetInfraredAvoidanceRightValue();
    LeftValue = hbot.mInfraredAvoidance->GetInfraredAvoidanceLeftValue();
    UlFrontDistance =  hbot.mUltrasonic->GetUltrasonicFrontDistance();
    DEBUG_LOG(DEBUG_LEVEL_INFO, "UlFrontDistance =%d \n",UlFrontDistance);

   if ((RightValue >= IA_THRESHOLD) && (LeftValue <= IA_THRESHOLD)) {
        hbot.SetSpeed(80);
        hbot.Drive(10 );
    } else if ((RightValue < IA_THRESHOLD) && (LeftValue > IA_THRESHOLD)) {
        hbot.SetSpeed(80);
        hbot.Drive(170);
    } else {
        hbot.SetSpeed(50);
        hbot.GoForward();
    }
    DEBUG_LOG(DEBUG_LEVEL_INFO, "UlFrontDistance = %d \n\r", UlFrontDistance);
    if (UlFrontDistance < UL_LIMIT_MID) {
        hbot.KeepStop();
        if (UlFrontDistance <= UL_LIMIT_MIN || RightValue <= IA_THRESHOLD || LeftValue <= IA_THRESHOLD) {
            hbot.SetSpeed(60);
            hbot.GoBack();
            delay(300);
            hbot.KeepStop();
        }
            UlRightDistance = hbot.mUltrasonic->GetUltrasonicRightDistance();
            UlLeftDistance = hbot.mUltrasonic->GetUltrasonicLeftDistance();
            if (UlRightDistance >= UlLeftDistance) {
                hbot.SetSpeed(100);
                hbot.TurnRight();
                delay(310);
            }
            if (UlLeftDistance > UlRightDistance) {
                hbot.SetSpeed(100);
                hbot.TurnLeft();
                delay(310);
            }
            if (UlLeftDistance <= UL_LIMIT_MIN && UlRightDistance <= UL_LIMIT_MIN ) {
                hbot.SetSpeed(100);
                hbot.Drive(0);
                delay(530);
                 hbot.KeepStop();
            }
            hbot.KeepStop();
    }
}

void HandleUltrasonicAvoidance(void)
{
    uint16_t UlFrontDistance,UlLeftDistance,UlRightDistance;
    UlFrontDistance =  hbot.mUltrasonic->GetUltrasonicFrontDistance();
    DEBUG_LOG(DEBUG_LEVEL_INFO, "UlFrontDistance =%d \n",UlFrontDistance);
    if ((UlFrontDistance < UL_LIMIT_MIN))
    {
        hbot.SetSpeed(100);
        hbot.GoBack();
        delay(250);
    }
    if (UlFrontDistance < UL_LIMIT_MID)
    {
        hbot.KeepStop();
        delay(100);
        UlRightDistance = hbot.mUltrasonic->GetUltrasonicRightDistance();
        UlLeftDistance = hbot.mUltrasonic->GetUltrasonicLeftDistance();
        if((UlRightDistance > UL_LIMIT_MIN) && (UlRightDistance < UL_LIMIT_MAX))
        {
            hbot.SetSpeed(80);
            hbot.TurnRight();
            delay(310);
        }
        else if((UlLeftDistance > UL_LIMIT_MIN) && (UlLeftDistance < UL_LIMIT_MAX))
        {
            hbot.SetSpeed(80);
            hbot.TurnLeft();
            delay(310);
        }
        else if((UlRightDistance < UL_LIMIT_MIN) && (UlLeftDistance < UL_LIMIT_MIN) )
        {
            hbot.SetSpeed(80);
            hbot.Drive(0);
            delay(510);
        }
    } else{
          hbot.SetSpeed(80);
          hbot.GoForward();
      }
}
//=============================Infrared tracking
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
//========================= bluetooth
void HandleBluetoothRemote(void)
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
            case E_CONTROL_MODE:
                hbot.SetControlMode(mProtocol->GetControlMode());
                break;
            case E_VERSION:
                break;
        }
    }
}

void HandleInfaredRemote(byte irKeyCode)
{
    switch ((E_IR_KEYCODE)hbot.mIrRecv->getIrKey(irKeyCode)) {
        case IR_KEYCODE_STAR:
          hbot.SpeedUp(10);
          DEBUG_LOG(DEBUG_LEVEL_INFO, "hbot.Speed = %d \n", hbot.Speed);
          break;
        case IR_KEYCODE_POUND:
          DEBUG_LOG(DEBUG_LEVEL_INFO, " start Degree = %d \n", hbot.Degree);
          hbot.SpeedDown(10);
          break;
        case IR_KEYCODE_UP:
          hbot.GoForward();
          break;
        case IR_KEYCODE_DOWN:
          hbot.GoBack();
          break;
        case IR_KEYCODE_OK:
          hbot.KeepStop();
          break;
        case IR_KEYCODE_LEFT:
          hbot.TurnLeft();
          break;
        case IR_KEYCODE_RIGHT:
          hbot.TurnRight();
          break;
        default:
          break;
    }
}

//====================================InfraredAvoidance
void HandleInfraredAvoidance()
{
    uint16_t RightValue,LeftValue;
    RightValue = hbot.mInfraredAvoidance->GetInfraredAvoidanceRightValue();
    LeftValue = hbot.mInfraredAvoidance->GetInfraredAvoidanceLeftValue();
    if((RightValue > IA_THRESHOLD)&&(LeftValue >IA_THRESHOLD))
    {
        hbot.SetSpeed(80);
        hbot.GoForward();
      }
    else if((RightValue > IA_THRESHOLD)&&(LeftValue < IA_THRESHOLD))
    {
        hbot.SetSpeed(70);
        hbot.TurnRight();
        delay(200);
    }
    else if((RightValue < IA_THRESHOLD)&&(LeftValue > IA_THRESHOLD))
    {
        hbot.SetSpeed(70);
        hbot.TurnLeft();
        delay(200);
    }
    else if((RightValue < IA_THRESHOLD)&&(LeftValue < IA_THRESHOLD))
    {
        hbot.SetSpeed(80);
        hbot.Drive(0);
        delay(200);
    }
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
    if (hbot.GetControlMode() !=  E_BLUETOOTH_CONTROL) {
        if (mProtocol->ParserPackage()) {
            if (mProtocol->GetRobotControlFun() == E_CONTROL_MODE) {
            hbot.SetControlMode(mProtocol->GetControlMode());
           }
        }
    }
    switch(hbot.GetControlMode())
    {
        case E_BLUETOOTH_CONTROL:
            HandleBluetoothRemote();
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_BLUETOOTH_CONTROL \n");
            break;
        case E_INFRARED_REMOTE_CONTROL:
            byte irKeyCode;
            if (irKeyCode = hbot.mIrRecv->getCode()) {
            DEBUG_LOG(DEBUG_LEVEL_INFO, "irKeyCode = %lx \n", irKeyCode);
            HandleInfaredRemote(irKeyCode);
            delay(110);
            }
            else {
                if (hbot.GetStatus() != E_STOP ) {
                    hbot.KeepStop();
                    }
                 }
            break;
        case E_INFRARED_TRACKING_MODE:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_INFRARED_TRACKING \n");
            HandleInfraredTracing();
            hbot.SendTracingSignal();
            break;
        case E_INFRARED_AVOIDANCE:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_INFRARED_AVOIDANCE \n");
            HandleInfraredAvoidance();
            break;
        case E_ULTRASONIC_AVOIDANCE:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_ULTRASONIC_AVOIDANCE \n");
            HandleUltrasonicAvoidance();
            break;
		    case E_ULTRASONIC_INFRARED_AVOIDANCE:
            DEBUG_LOG(DEBUG_LEVEL_INFO, "E_ULTRASONIC_INFRARED_AVOIDANCE \n");
            HandleUltrasonicInfraredAvoidance();
            hbot.SendInfraredData();
            hbot.SendUltrasonicData();
            break;
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

