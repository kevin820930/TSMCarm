#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "straight.h"

point calcu(point *orig,point *endaxis,arm *myarm,double distance){
    
    double pi=3.14159265359;
    void *move(motor mymotor);
    double angleE_O,angleB_O,angleorig1,angleorig2,angleorig3,angleafter1,angleafter2,angleafter3;
    double moveangle1,moveangle2,moveangle3;;
    double origx=orig->xpoint;
    double origy=orig->ypoint;
    double endx=endaxis->xpoint;
    double endy=endaxis->ypoint;
    double O_Elong,afterO_Elong,firstlong,secondlong,thirdlong;
    double endvector[2];
    endvector[0]=myarm->vector[0];
    endvector[1]=myarm->vector[1];
    double firstvector[2];
    firstvector[0]=endx-origx;
    firstvector[1]=endy-origy;

    firstlong=myarm->longbase;
    secondlong=(myarm->longbase)*(myarm->longrate2);
    thirdlong=(myarm->longbase)*(myarm->longrate3);
    printf("O_E vector vector: %f,%f,3axis vector:%f,%f\n",firstvector[0],firstvector[1],endvector[0],endvector[1]);

    O_Elong=sqrt((firstvector[0]*firstvector[0])+(firstvector[1]*firstvector[1]));
    //supporting triangle1 angle
    angleE_O=acos((firstvector[0]*endvector[0]+firstvector[1]*endvector[1])/((sqrt(firstvector[0]*firstvector[0]+firstvector[1]*firstvector[1]))*(sqrt(endvector[0]*endvector[0]+endvector[1]*endvector[1]))  ));
     
    printf("angleE_O 3axis: %f,O_Elong:%f\n",angleE_O,O_Elong);
    //orig triangle angle
    angleorig1=acos((O_Elong*O_Elong+firstlong*firstlong-secondlong*secondlong)/(2*O_Elong*firstlong));
    angleorig2=acos((firstlong*firstlong+secondlong*secondlong-O_Elong*O_Elong)/(2*firstlong*secondlong));
    
    printf("angleorig1: %f,angleorig2: %f\n",angleorig1,angleorig2);
    //supporting triangle2 angle
    double c,sup2angle;
    c=(distance*distance)+(O_Elong*O_Elong)-(2*O_Elong*distance*cos(pi-angleE_O));
    afterO_Elong=sqrt(c);
    sup2angle=acos((O_Elong*O_Elong+afterO_Elong*afterO_Elong-distance*distance)/(2*O_Elong*afterO_Elong));

    printf("sup2angle: %f,afterE_Olong:%f,movelong:%f\n",sup2angle,afterO_Elong,distance);
    //after triangle angle
    double tmpangle;
    tmpangle=acos((firstlong*firstlong+afterO_Elong*afterO_Elong-secondlong*secondlong)/(2*firstlong*afterO_Elong));
    angleafter1=sup2angle+tmpangle;
    angleafter2=acos((firstlong*firstlong+secondlong*secondlong-afterO_Elong*afterO_Elong)/(2*firstlong*secondlong));

    printf("angleafter1: %f,angleafter2: %f\n",angleafter1,angleafter2);
    //the need of angle move
    moveangle1=angleafter1-angleorig1;
    moveangle2=angleafter2-angleorig2;
    printf("moveangle1: %f,moveangle2: %f\n",moveangle1*(180/pi),moveangle2*(180/pi));

    return *orig;
}



void *move(motor mymotor){
;
}
