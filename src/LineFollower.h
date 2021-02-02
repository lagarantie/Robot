#ifndef LineFollower_h
#define LineFollower_h

#include "MeMegaPi.h"
#include "Controlrobot.h"
#include "Config.h"



class LineFollower
{

private:

    int sensorState;
    int rSpeed;
    MeLineFollower lineFinder;
    Controlrobot *robot;
    int accI =0;
    int accD = 0;

public:

    LineFollower(MeLineFollower port, Controlrobot *r):
    lineFinder{port}, robot{r}{}

    void followLine(int speed){
          int state=0;
          sensorState = lineFinder.readSensors();
          switch (sensorState){
              //two sensors inside
              case S1_IN_S2_IN:
                  state=0;
//                  accD=0;
                  accI=0;
                  break;

                  //right sensor outside
              case S1_IN_S2_OUT:
                  state=-1;
                  break;


              case S1_OUT_S2_IN:
                  state=1;
                  break;


              case S1_OUT_S2_OUT:
//                  accD=0;
                  accI=0;
                  state=0;
                  break;

          }
          double Kp=30,Ki=0.5, Kd = 0;
          int err = state;
          int deriv = err -accD;
          accD = err;
          accI+= err;
          accI = max(accI,-40);
          accI = min(accI,40);
          int baseSpeed = (int)(Kp*err + Ki*accI + Kd*deriv);
          if(baseSpeed >0){
              speed = 10;
          }if(baseSpeed <0){
              speed = 10;
          }

          robot->_motorLeft.run((speed+baseSpeed));
          robot->_motorRight.run((-speed+baseSpeed));

      }


      uint8_t getState(){
        sensorState = lineFinder.readSensors();
        switch (sensorState){
            //two sensors inside
            case S1_IN_S2_IN:
                return 2;
                //right sensor outside
            case S1_IN_S2_OUT:
                return -1;
            case S1_OUT_S2_IN:
                return 1;
            case S1_OUT_S2_OUT:
                return 0;
        }
        return -2;
    }





};


#endif
