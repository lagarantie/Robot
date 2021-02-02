#ifndef CONFIG_H
#define CONFIG_H


#define RATIO 1.5

/*-----Colors------*/

#define GREEN 5
#define BLUE 7
#define RED 2





/*----Position gyroscope------*/
#define FORK_UP -30.0
#define FORK_DOWN 22.8
#define FORK_COLOR_SENSOR -32.5




#define DISTANCE_OBJECT 5





/*----Speed motors-------------*/

 #define SPEED_FORK_UP 20
 #define SPEED_FORK_DOWN -20



 #define SPEED_FORWARD_MAX 40*RATIO
 #define SPEED_FORWARD_PUT_PIECE 30*RATIO

 #define SPEED_LINEF_MAX 35*RATIO

 #define SPEED_LINEF_WORKSHOP 35*RATIO

 #define ROTATION_SPEED 40*RATIO






/*-------------list commandes bluetooth--------------------*/

#define AUTOMATIC 0
#define LEFT_90 3
#define RIGHT_90 4
#define FOLLOW_LINE_COLOR 5
#define TAKE_PIECES_SAME_COLOR 9
#define TAKE_PIECES 10
#define DROP_PIECES 11
#define ENTER_REST_ZONE 12
#define OUT_REST_ZONE 13
#define RIGHT_90_GYRO 6
#define LEFT_90_GYRO 7
#define FOWARWARD_WITHOUT_PASTILLE 14

#define DROP_PIECES_BRUTS 15

#define MANUEL 1

#define STOP 50

#define FORWARD 20
#define LEFT 21
#define RIGHT 22




#define DELAY_FORWARD 100
#define DELAY_ROTATION 200





#endif
