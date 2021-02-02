#include "MeMegaPi.h"

#include "Controlrobot.h"
#include "LineFollower.h"
#include "UltraSonicSensor.h"
#include "AutomaticBehavior.h"
#include "DetectColorSensor.h"
#include "ControlFork.h"
#include "TrueLineFollower.h"
#include "DetectColorPieceSensor.h"


#include <Wire.h>

#include "Config.h"






MeMegaPiDCMotor motor_left (PORT2B) ;
MeMegaPiDCMotor motor_right (PORT1B);
MeMegaPiDCMotor motorFork (PORT3B);
MeLineFollower lineFinder(PORT_5);
MeColorSensor colorsensor1(PORT_7);

MeColorSensor colorsensor0(PORT_8);
MeGyro gyro(PORT_6, 0x68);



Controlrobot robot(motor_left, motor_right);
LineFollower lineFolowerWorshop(lineFinder, &robot);
UltraSonicSensor ultraSonicSensor(&robot);

DetectColorSensor sensorColor(colorsensor0, &robot);
DetectColorPieceSensor sensorColorPiece(colorsensor1, &robot);
ControlFork fork(motorFork, &gyro, &robot);
TrueLineFollower trueLineFollower(lineFinder, &robot);
AutomaticBehavior automaticBehavior(&gyro,&robot, &trueLineFollower, &ultraSonicSensor, &fork, &sensorColorPiece, &lineFolowerWorshop, &sensorColor);

unsigned long time1=0;
unsigned long time2=0;

uint8_t mode=0; //0=auto, 1=manuel


int tabCommandes[80];
int numberCommandes;
int indexCommandes=0;
bool commandValid=false;
bool passedPastille=false;






int tourne=0;

bool state=false;

void clearTabCommandes(){
  for (int i=0; i<50;i++){
    tabCommandes[i]=0;
  }
}



void setup(){

  Serial3.begin(115200);
  Serial.begin(9600);

  gyro.begin();
  colorsensor0.SensorInit();

  delay(2000);
  //robot.forward(80);
  //time1=millis();
  //fork.downFork();
  // delay(1000);
  //delay(1000);
  //fork.upFork();
  // delay(1000);
  // fork.middleFork();
  // delay(1000);
  // fork.upFork();
}


/********************start of the loop************************/
void loop(){



  //-------------------------Read serial-------------------

  if(Serial3.available()){
    Serial.println("données reçues");
    String dataRecieved=Serial3.readString();

   Serial.println(dataRecieved);

   if(dataRecieved.toInt()==AUTOMATIC){
     mode=0;
     clearTabCommandes();

   }else if(dataRecieved.toInt()==MANUEL){
     mode=1;
     clearTabCommandes();

   }else if(dataRecieved=="STOP"){
     robot.forward(0);
     clearTabCommandes();

     //si on recoit une commande
   }else{
     clearTabCommandes();
     int r=0, t=0;
     numberCommandes=1;
     for (uint8_t i=0; i<dataRecieved.length();i++){
       if(dataRecieved.charAt(i)=='/'){ //split au slash
         tabCommandes[t]=dataRecieved.substring(r,i).toInt();
         r=i+1;
         t++;
         numberCommandes+=1;
       }
     }
     indexCommandes=0;
     Serial.println("traitement terminé");
   }
 }



 //-----------------------end read serial---------------------------/

commandValid=false;

switch (mode){
  //automatic
  case AUTOMATIC:
    switch(tabCommandes[indexCommandes]){
      case LEFT_90:
       automaticBehavior.turnLeftAndGetLine();
       commandValid=true;
       break;

      case RIGHT_90:
        Serial.println("right");
       automaticBehavior.turnRightAndGetLine();
       commandValid=true;
       break;

       case RIGHT_90_GYRO:
         Serial.println("right");
        automaticBehavior.turnRight90();
        commandValid=true;
        break;

        case LEFT_90_GYRO:
          Serial.println("right");
         automaticBehavior.turnLeft90();
         commandValid=true;
         break;

      case FOLLOW_LINE_COLOR:

        time1 = millis();
        while(sensorColor.detectWhiteBlack()!=true || (millis() - time1)<1000){
          lineFolowerWorshop.followLine(30*RATIO);
          //detection d'objet
          while(ultraSonicSensor.detectPiece(5)==true){
            robot.forward(0);
          }
        }
        time1=0;
        while(sensorColor.detectColor()!=true){
          lineFolowerWorshop.followLine(50*RATIO);
          //detection d'objet
          while(ultraSonicSensor.detectPiece(5)==true){
            robot.forward(0);
          }

        }

        robot.forward(0);
        robot.forward(-30*RATIO);
        delay(100);
        robot.forward(0);
        delay(500);

        Serial.println("Pasttile tourvée");
        commandValid=true;

        break;



      case TAKE_PIECES_SAME_COLOR:
        indexCommandes+=1;
        delay(500);
        automaticBehavior.takePiecesSameColor(tabCommandes[indexCommandes]);
        commandValid=true;
        break;

      case TAKE_PIECES:

        indexCommandes+=1;
        automaticBehavior.takePieces(tabCommandes[indexCommandes]);
        commandValid=true;
        break;

      case DROP_PIECES:
        indexCommandes+=1;
        automaticBehavior.putPieces(tabCommandes[indexCommandes]);
        commandValid=true;
        break;

      case DROP_PIECES_BRUTS:
          indexCommandes+=1;
          automaticBehavior.putBrutPieces();
          commandValid=true;
          break;

      case ENTER_REST_ZONE:
        automaticBehavior.enterResteZone();
        commandValid=true;
        break;

      case OUT_REST_ZONE:
        automaticBehavior.exitRestZone();
        commandValid=true;
        break;

      default:
        break;
    }
  //manuel
  case MANUEL:
    switch (tabCommandes[indexCommandes]){
      case FORWARD :
        indexCommandes+=1;
        robot.forward(tabCommandes[indexCommandes]*RATIO);
        commandValid=true;
        delay(DELAY_FORWARD);
        break;

      case LEFT :
        robot.left(45*RATIO);
        commandValid=true;
        delay(DELAY_ROTATION);
        break;

      case RIGHT :
        robot.right(45*RATIO);
        commandValid=true;
        delay(DELAY_ROTATION);
        break;

      case STOP :
        robot.forward(0);
        commandValid=true;
        break;

      case TAKE_PIECES_SAME_COLOR:
        delay(500);
        automaticBehavior.takePiecesSameColor(1);
        commandValid=true;
        break;

      case DROP_PIECES:
        automaticBehavior.putPieces(1);
        commandValid=true;
        break;

      default:
        break;
    }

    // no value in array
  default :
    break;

}


 if(commandValid==true){
   indexCommandes+=1;
   // if end of tab
   if(tabCommandes[indexCommandes]==0){
     clearTabCommandes();
     Serial3.println("A");

   }
 }






}
