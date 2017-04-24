#include <stdio.h>
#include <stdlib.h>
#include "scheduleing.h"
#include "initialize.h"
#include "routplanning.h"
#include "generator.h"

#define armbaselong 320
#define arm2rate 0.53125
#define arm3rate 1.1
#define ratio 780

//need modify
#define tmp1 28.1748
#define tmp2 89.1047
#define tmp3 62.72038
#define distance 120
//need modify

#define pointsnum 30

int main(){

    double coordinate[10][4];
    int scheduleing[100][2];
    anglelist *go[10];
    /*
    Double digits.first digit is the task cassetteA:0,A:1,B:2,C:3,cassetteB:4
    Second digit is the chamber number of task
    */


    printf("-------game start-------\n");

    //initialize coordinate
    Initialize(coordinate,armbaselong,arm2rate,arm3rate,distance,ratio);    

    //scheduleing
    ScheduleFunction(scheduleing);
    

    //roudplaining
    int i=0;
    for(i=0;i<10;i++){
        go[i]=(anglelist *)malloc(sizeof(anglelist));
        *go[i]=routplanning(armbaselong,arm2rate,arm3rate,coordinate[i][1]+tmp1,coordinate[i][2],tmp2,180-tmp3,distance,pointsnum);
    }
//    anglelist *tmp=(anglelist *)malloc(sizeof(anglelist));
   
    //end plaining 

    //Nccode generator
    generator(go,scheduleing);    

    //end generate
    printf("-------game over,good luck-------\n");

}
