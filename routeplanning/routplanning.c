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
    char readdata[100];
    int i=0,a=0;
    int mid=0,end=0;
    char first[40],second[40];
    int linenum=0;
    long double data[100][2];
    int time=10;

    
    for(i=0;i<100;i++){
	readdata[i]='\0';
    }
    for(i=0;i<40;i++){
	first[i]=0;
	second[i]=0;
    }
    
    fp=fopen("moveangle.txt","r");
    while(fgets(readdata,sizeof(readdata),fp)){
	for(i=0;readdata[i]!=' ';i++){
	    if(readdata[i]==','){
		mid=i;
	    }
	}
	end=i;
	for(a=0;a<mid;a++){
            first[a]=readdata[a];
        }
	data[linenum][0]=atof(first);

        for(i=0,a=(mid+1);a<end;a++,i++){
	    second[i]=readdata[a];
	}
	data[linenum][1]=atof(second);

	for(i=0;i<100;i++){
        readdata[i]='\0';
        }
        for(i=0;i<40;i++){
            first[i]=0;
            second[i]=0;
        }
        linenum++;
    }


    long double data[10][2];
    int time=10;
    int i,j;
    for(i=0;i<time;i++){
        data[i][0]=i*i*i*i*i*i*i*i*i*4.1544444549561;
        data[i][1]=1.2564564*i*2.454517945412145114;
    }
   
    lagrange(data,time);
   
}

