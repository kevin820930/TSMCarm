#ifndef _STRAIGHT_H
#define _STRAIGHT_H

/*point style */
typedef struct ARM {
    double longbase;
    double longrate2;
    double longrate3;
} arm;

typedef struct motor{
    double motor1angle;
    double motor2angle;
    double motor3angle;
    double motor4angle;
}motor;


motor calcu(arm *armdata,motor *origangle,double distance,int pointsnum);


#endif

