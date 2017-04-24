#include <stdio.h>
#include <stdlib.h>
#include "scheduleing.h"

void ScheduleFunction(int scheduleing[100][2]){

    int x,y;
    for(x=0;x<100;x++){
	for(y=0;y<2;y++){
	    scheduleing[x][y]=0;
	}
    }
    scheduleing[0][0]=1;
    scheduleing[0][1]=5;

    scheduleing[1][0]=2;
    scheduleing[1][1]=4;


}


