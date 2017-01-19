#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "mylagrange.h"

int main(){

    long double data[20][2];
    int time=20;
    int i,j;
    for(i=0;i<time;i++){
	data[i][0]=1*((i)*(i+1));
	data[i][1]=1*((i)*2+1);
    }

    lagrange(data,time);

}
