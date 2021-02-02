#ifndef Controlrobot_h
#define Controlrobot_h

#include "MeMegaPi.h"



/* class that control the motors of the robot*/

class Controlrobot
{

  public:
      MeMegaPiDCMotor _motorLeft;
      MeMegaPiDCMotor _motorRight;
      int leftSpeed;
      int rightSpeed;
      int rotationSpeed;


      Controlrobot(MeMegaPiDCMotor motorLeft, MeMegaPiDCMotor motorRight):
        _motorLeft{motorLeft},_motorRight{motorRight}{};

      void forward(int speed){
        leftSpeed=speed;
        rightSpeed=-speed;
        rotationSpeed=0;
        _motorLeft.run(leftSpeed);
        _motorRight.run(rightSpeed);

    };

      void rotate(int rSpeed){
          rotationSpeed=rSpeed;
          if (rSpeed>0){
            _motorLeft.run(rSpeed);
            _motorRight.run(rSpeed);
          }else if (rSpeed<0){
            _motorLeft.run(rSpeed);
            _motorRight.run(rSpeed);
          }else{
            _motorLeft.run(leftSpeed);
            _motorRight.run(rightSpeed);
          }
      }

      void left(int rSpeed){
        rotate(-rSpeed);
      }

      void right(int rSpeed){
        rotate(rSpeed);
      }



    int getLeftSpeed(){
      return leftSpeed;
    }

    int getRightSpeed(){
      return rightSpeed;
    }




  private:



};

#endif
