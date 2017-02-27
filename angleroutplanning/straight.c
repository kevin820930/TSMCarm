#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "straight.h"

motor calcu(arm *armdata,motor *origangle,double distance,int pointsnum){

    double pi=3.1415926;
    int count=0;    

    motor *afterangle=(motor *)malloc(sizeof(motor));
    double arm1long=armdata->longbase;
    double arm2long=arm1long*(armdata->longrate2);
    double arm3long=arm1long*(armdata->longrate3);

    double angle1=(origangle->motor1angle)*pi/180;
    double angle2=(origangle->motor2angle)*pi/180;
    double angle3=(origangle->motor3angle)*pi/180;
    double angle4=(origangle->motor4angle)*pi/180;

    printf("initial %f,%f,%f\n",origangle->motor1angle,origangle->motor3angle,origangle->motor4angle);

    double tmpangle1,tmpangle7,tmpangle8,tmpangle4,tmpangle2,tmpangle9,tmpangle6;    
    double tmpline1;//origangle2,arm1,arm2

    double movelong=distance/pointsnum;

    double afterline1,afterangle1,afterangle3,afterangle4;

    FILE *fp;
    fp=fopen("moveangle.txt\0","w");

    //check if the distance is able to move
    tmpline1=pow(arm1long,2)+pow(arm2long,2)-2*arm1long*arm2long*cos(angle3);
    tmpline1=sqrt(tmpline1);
    if(distance>(arm1long+arm2long)-tmpline1){
	printf("the distance is too long,the longest distance is %f\n",tmpline1);
	return *origangle;
    }
    //
    for(count=0;count<pointsnum;count++){

        tmpline1=pow(arm1long,2)+pow(arm2long,2)-2*arm1long*arm2long*cos(angle3);
        tmpline1=sqrt(tmpline1);     

        tmpangle8=(pow(tmpline1,2)+pow(arm1long,2)-pow(arm2long,2))/(2*arm1long*tmpline1);
        tmpangle8=acos(tmpangle8);

        tmpangle7=(pow(tmpline1,2)+pow(arm2long,2)-pow(arm1long,2))/(2*arm2long*tmpline1);
        tmpangle7=acos(tmpangle7);

        tmpangle4=angle4+tmpangle7;

        afterline1=pow(tmpline1,2)+pow(movelong,2)-2*tmpline1*movelong*cos(tmpangle4);
        afterline1=sqrt(afterline1);
    
        afterangle3=(pow(arm2long,2)+pow(arm1long,2)-pow(afterline1,2))/(2*arm1long*arm2long);
        afterangle3=acos(afterangle3);

        tmpangle9=(pow(afterline1,2)+pow(arm1long,2)-pow(arm2long,2))/(2*arm1long*afterline1);
        tmpangle9=acos(tmpangle9);
    
        tmpangle6=(pow(tmpline1,2)+pow(afterline1,2)-pow(movelong,2))/(2*tmpline1*afterline1);
        tmpangle6=acos(tmpangle6);

        afterangle1=angle1-(tmpangle8-tmpangle9-tmpangle6);//

        afterangle4=pi-(pi-tmpangle4-tmpangle6)-(pi-afterangle3-tmpangle9);
    
        printf("angle1:%f ,angle3:%f ,angle4:%f \n",afterangle1*180/pi,afterangle3*180/pi,afterangle4*180/pi);
        fprintf(fp,"%f,%f \n",afterangle1*180/pi,afterangle3*180/pi);    

        angle1=afterangle1;
        angle3=afterangle3;
        angle4=afterangle4;
    }      

    afterangle->motor1angle=afterangle1;
    afterangle->motor2angle=angle2;
    afterangle->motor3angle=afterangle3;
    afterangle->motor4angle=afterangle4;
    fclose(fp);
    return *afterangle;
}

