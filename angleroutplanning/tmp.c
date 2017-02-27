#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "straight.h"
#define npart 10
#define scale 1 // scale 1:?(m)

motor calcu(arm *orig,motor *orig,double distance,int pointsnum){
    
    int count=0;
    double pi=3.14159265359;
    double angleE_O,angleB_O,angleorig1,angleorig2,angleorig3,angleafter1,angleafter2,angleafter3;
    double moveangle1,moveangle2,moveangle3;
    double totalmove1=0,totalmove2=0,totallong=0;
    double origx=orig->xpoint;
    double origy=orig->ypoint;
    double endx=endaxis->xpoint;
    double endy=endaxis->ypoint;
    double O_Elong,afterO_Elong,firstlong,secondlong,thirdlong;
    double endvector[2];
    endvector[0]=myarm->vector[0];
    endvector[1]=myarm->vector[1];
    double firstvector[2];
    double partmovex,partmovey;

    firstlong=myarm->longbase;
    secondlong=(myarm->longbase)*(myarm->longrate2);
    thirdlong=(myarm->longbase)*(myarm->longrate3);

    double partdistance=distance/npart;
    partmovex=(endvector[0]/(sqrt(endvector[0]*endvector[0]+endvector[1]*endvector[1])))*partdistance;
    partmovey=(endvector[1]/(sqrt(endvector[0]*endvector[0]+endvector[1]*endvector[1])))*partdistance;

    FILE *fp,*fpspace;
    fp=fopen("moveangle.txt","w");
    //fpspace=fopen("movespace","w");

    for(count=0;count<npart;count++){
        firstvector[0]=endx-origx;
        firstvector[1]=endy-origy;


        O_Elong=sqrt((firstvector[0]*firstvector[0])+(firstvector[1]*firstvector[1]));
        O_Elong=O_Elong*scale;
        //supporting triangle1 angle
        angleE_O=acos((firstvector[0]*endvector[0]+firstvector[1]*endvector[1])/((sqrt(firstvector[0]*firstvector[0]+firstvector[1]*firstvector[1]))*(sqrt(endvector[0]*endvector[0]+endvector[1]*endvector[1]))  ));
     
        //orig triangle angle
        angleorig1=acos((O_Elong*O_Elong+firstlong*firstlong-secondlong*secondlong)/(2*O_Elong*firstlong));
        angleorig2=acos((firstlong*firstlong+secondlong*secondlong-O_Elong*O_Elong)/(2*firstlong*secondlong));
    
        //supporting triangle2 angle
        double c,sup2angle;
        c=(partdistance*partdistance)+(O_Elong*O_Elong)-(2*O_Elong*partdistance*cos(pi-angleE_O));
        afterO_Elong=sqrt(c);
        sup2angle=acos((O_Elong*O_Elong+afterO_Elong*afterO_Elong-partdistance*partdistance)/(2*O_Elong*afterO_Elong));
  
        //after triangle angle
        double tmpangle;
        tmpangle=acos((firstlong*firstlong+afterO_Elong*afterO_Elong-secondlong*secondlong)/(2*firstlong*afterO_Elong));
        angleafter1=sup2angle+tmpangle;
        angleafter2=acos((firstlong*firstlong+secondlong*secondlong-afterO_Elong*afterO_Elong)/(2*firstlong*secondlong));

        //the need of angle move
        moveangle1=angleafter1-angleorig1;
        moveangle2=angleafter2-angleorig2;
        fprintf(fp,"%f,%f \n",angleafter1*(180/pi),angleafter2*(180/pi));
        //fprintf(fpspace,"%f %f\n",angleafter1*(180/pi),angleafter2*(180/pi));
        
        totalmove1+=moveangle1;
        totalmove2+=moveangle2;
        totallong+=partdistance;
        endx=endx+partmovex;
        endy=endy+partmovey;

    }
    printf("totalmove1: %f,totalmove2: %f , totallong: %f\n",totalmove1*(180/pi),totalmove2*(180/pi),totallong);

        
    fclose(fp);
    //fclose(fpspace);
    return *orig;
}

