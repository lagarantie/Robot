#ifndef TrueLineFollower_h
#define TrueLineFollower_h

#include "MeMegaPi.h"
#include "Controlrobot.h"
#include "Config.h"





class TrueLineFollower
{

  private:

      int sensorState;
      int rSpeed;
      MeLineFollower lineFinder;
      Controlrobot *robot;

  public:

      TrueLineFollower(MeLineFollower port, Controlrobot *r):
      lineFinder{port}, robot{r}{}

      void followLine(){
        sensorState = lineFinder.readSensors();
        switch (sensorState){
           //two sensors inside
          case S1_IN_S2_IN:
              robot->forward(SPEED_LINEF_MAX);
              break;

          //right sensor outside
          case S1_IN_S2_OUT:
              robot->_motorLeft.run(-SPEED_LINEF_MAX);
              robot->_motorRight.run(-SPEED_LINEF_MAX);
              break;


          case S1_OUT_S2_IN:
              robot->_motorRight.run(SPEED_LINEF_MAX);
              robot->_motorLeft.run(SPEED_LINEF_MAX);
              break;


          case S1_OUT_S2_OUT:
            robot->forward(SPEED_LINEF_MAX);
            break;

        }
      }





};


#endif
