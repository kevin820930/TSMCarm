#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <assert.h>

#include "straight.h"
#define alongbase 5
#define alongrate2 0.64
#define alongrate3 0.5656
#define movelong 1.414
#define origx 0
#define origy 0
#define endx -6
#define endy 3
#define endvectorx -1;
#define endvectory 1; 

int main(){

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
    testarm->longbase=alongbase;
    testarm->longrate2=alongrate2;
    testarm->longrate3=alongrate3;

    calcu(orig,endaxis,testarm,movelong);

    return 0;

}
