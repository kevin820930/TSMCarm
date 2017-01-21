#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <assert.h>

#include "straight.h"
#include "mylagrange.h"

//Following are the data you need to key in.
/*
#define armbaselong 5
#define axis2rate 0.64
#define axis3rate 0.5656
#define distance 1.414
#define origx 0
#define origy 0
#define endx -6
#define endy 3
#define endvectorx -1;
#define endvectory 1; 
*/
//ending of key in
 
void routplanning(double armbaselong,double axis2rate,double axis3rate,double distance,double origx,double origy,double endx,double endy,double endvectorx,double endvectory){

    point *orig,*endaxis;
    arm *testarm;
    double endvector[2];
    
    orig =(point *)malloc(sizeof(point));
    endaxis =(point *)malloc(sizeof(point));
    testarm=(arm *)malloc(sizeof(arm)); 
   
    orig->xpoint=origx;
    orig->ypoint=origy;
    endaxis->xpoint=endx;
    endaxis->ypoint=endy;
    testarm->vector[0]=endvectorx;
    testarm->vector[1]=endvectory;
    testarm->longbase=armbaselong;
    testarm->longrate2=axis2rate;
    testarm->longrate3=axis3rate;

    calcu(orig,endaxis,testarm,distance);

    sleep(1);

    FILE *fp;
    fp=fopen("moveangle.txt","r");
    long double data[10][2];
    int time=10;

    

    lagrange(data,time);

    
}
