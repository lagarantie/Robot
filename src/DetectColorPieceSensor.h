#ifndef DetectColorPieceSensor_h
#define DetectColorPieceSensor_h

#include "MeMegaPi.h"
#include "Controlrobot.h"
#include "AutomaticBehavior.h"
#include "Config.h"





class DetectColorPieceSensor {
  private:
    uint8_t colorResult;
    MeColorSensor colorsensor0;
    Controlrobot *robot;
    bool detected=false;

  public :

    DetectColorPieceSensor(MeColorSensor colorsensor, Controlrobot *r){
      colorsensor0=colorsensor;
      robot=r;
    };

    int detectColor(){

      colorResult=colorsensor0.ColorIdentify();
      detected=false;

      /* on avance pas à pas tant qu'on détecte pas une pièce */
      while(detected==false){

        while(colorResult!=RED && colorResult!=GREEN){


          robot->forward(50*RATIO);
          delay(30);
          robot->forward(0);
          colorResult=colorsensor0.ColorPieceIdentify();
          Serial.println(colorResult);

        }

        detected=true;

        for (int i=0 ; i<10; i++){
          colorResult=colorsensor0.ColorPieceIdentify();
          Serial.println(colorResult);
          if(colorResult!=RED && colorResult!=GREEN){
            detected=false;
          }
        }


        Serial.println("couleur:");
        Serial.println(colorResult);


      }

      return colorResult;

    }

};


#endif
