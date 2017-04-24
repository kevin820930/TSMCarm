#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <assert.h>
#include "routplanning.h"

int main(){
    rout *routpoly=(rout *)malloc(sizeof(rout));
/*
    double armbaselong=50;
    double arm2rate=0.63245;
    double arm3rate=0.5657;
    double motor1angle=53;
    double motor2angle=20;
    double motor3angle=107;
    double motor4angle=115;
    double movedistance=14;

*/
    double armbaselong=315;
    double arm2rate=((double)166/315);
    double arm3rate=((double)295/315);
    double motor1angle=53;
    double motor2angle=50;
    double motor3angle=78.32;
    double motor4angle=108.34;
    double movedistance=95;

    int pointsnum=10,i;
    *routpoly=routplanning(armbaselong,arm2rate,arm3rate,motor1angle,motor2angle,motor3angle,motor4angle,movedistance,pointsnum);

/*
    for(i=pointsnum-1;i>=0;i--){
	printf("%Lf ",routpoly->polynomial[i]);
    }
*/
}

