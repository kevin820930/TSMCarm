#include<stdio.h>
#include"initialize.h"
#include<math.h>

#define pi 3.1415926

void Initialize(double coordinate[10][4],double armbaselong,double arm2rate,double arm3rate,double distance,double ratio){

/*
the first layer(highter one) are 0~3(left to right);second layer(lower one) are 4~7(left to right)
*/
    int i;
    double measureangle[10][4];
    double realcd[5][2];
    double centerx[4],centery[4],avcx,avcy;
    double reference[5][2];
    double armlong1=armbaselong;
    double armlong2=armbaselong*arm2rate;
    double armlong3=armbaselong*arm3rate;


//need to edit.This is just for test
    for(i=0;i<10;i++){
	measureangle[i][1]=0;
    }

//


//calculate the real(x,y)coordinate(realcd) of each platform

    for(i=0;i<5;i++){
	realcd[i][0]=(armlong1*cos(measureangle[i][0]))+(armlong2*cos(measureangle[i][0]+measureangle[i][2]))+(armlong3*cos(measureangle[i][0]+measureangle[i][2]-measureangle[i][3]));
	realcd[i][1]=(armlong1*sin(measureangle[i][0]))+(armlong2*sin(measureangle[i][0]+measureangle[i][2]))+(armlong3*sin(measureangle[i][0]+measureangle[i][2]-measureangle[i][3]));;
    }
//



//for test,because no measureangle
    double topanglez=0,loweranglez=0;
    realcd[0][0]=3.1*(ratio/5);
    realcd[0][1]=4.2*(ratio/5);
    realcd[1][0]=4.1*(ratio/5);
    realcd[1][1]=3.2*(ratio/5);
    realcd[2][0]=5.1*(ratio/5);
    realcd[2][1]=0.2*(ratio/5);
    realcd[3][0]=4.1*(ratio/5);
    realcd[3][1]=(-2.8)*(ratio/5);
    realcd[4][0]=3.1*(ratio/5);
    realcd[4][1]=(-3.8)*(ratio/5);
//need to deleted

//count the center of cycle
    double cx,cy,dx,dy,l,h,tdx,tdy;
    
    for(i=0;i<4;i++){
  
        cx=(realcd[i][0]+realcd[i+1][0])/2;
        cy=(realcd[i][1]+realcd[i+1][1])/2;
	if(realcd[i+1][1]-realcd[i][1]<0){
	    dx=realcd[i+1][0]-realcd[i][0];
	    dy=realcd[i+1][1]-realcd[i][1];
	}
	else{
	    dx=realcd[i][0]-realcd[i+1][0];
	    dy=realcd[i][1]-realcd[i+1][1];
	}
    l=sqrt(dx*dx+dy*dy);
    h=sqrt(ratio*ratio-(l/2)*(l/2));
    tdx=(-1)*h*dy/l;
    tdy=h*dx/l;
    centerx[i]=cx-tdx;
    centery[i]=cy-tdy;
    }
    avcx=(centerx[0]+centerx[1]+centerx[2]+centerx[3])/4;
    avcy=(centery[0]+centery[1]+centery[2]+centery[3])/4;
    printf("\n中心位置 x:%f y: %f\n",avcx,avcy);

//calculate center

    double tmplong1=0;//original pointer to forth modor
    double tmplong2=0;//avcenter to reference
    double tmpangle1=0;//tmplong and y axis;
    double tmpangle2=0;//tmplong and (avcenter to reference)


    for(i=0;i<5;i++){
        reference[i][0]=avcx+(realcd[i][0]-avcx)*((ratio-distance-armlong3)/ratio);
	reference[i][1]=avcy+(realcd[i][1]-avcy)*((ratio-distance-armlong3)/ratio);
	//printf("\n%f %f %f\n",reference[i][0],reference[i][1],(reference[i][0]-avcx)*(reference[i][0]-avcx)+(reference[i][1]-avcy)*(reference[i][1]-avcy));
	printf("各平台直線進入點  x:%f y:%f\n",reference[i][0],reference[i][1]);
    }
    
    for(i=0;i<5;i++){
        tmplong1=sqrt(reference[i][0]*reference[i][0]+reference[i][1]*reference[i][1]);
        tmpangle1=(reference[i][0]*1)/(tmplong1);
        tmpangle1=(acos(tmpangle1))*180/pi;
	coordinate[i][0]=(tmplong1*tmplong1+armlong1*armlong1-armlong2*armlong2)/(2*tmplong1*armlong1);
	coordinate[i][0]=(acos(coordinate[i][0]))*180/pi;
	coordinate[i][0]=tmpangle1+coordinate[i][0];
	coordinate[i][1]=measureangle[i][1];
	coordinate[i][2]=(armlong1*armlong1+armlong2*armlong2-tmplong1*tmplong1)/(2*armlong1*armlong2);
	coordinate[i][2]=(acos(coordinate[i][2]))*180/pi;
	coordinate[i][3]=(armlong2*armlong2+tmplong1*tmplong1-armlong1*armlong1)/(2*tmplong1*armlong2);
	coordinate[i][3]=(acos(coordinate[i][3]))*180/pi;
	tmplong2=sqrt((reference[i][0]-avcx)*(reference[i][0]-avcx)+(reference[i][1]-avcy)*(reference[i][1]-avcy));
	tmpangle2=(reference[i][0]*(reference[i][0]-avcx)+reference[i][1]*(reference[i][1]-avcy))/(tmplong2*tmplong1);
	tmpangle2=(acos(tmpangle2))*180/pi;
        coordinate[i][3]=180-tmpangle2-coordinate[i][3];
	printf("各平台直線進入初始四軸角度 1axis:%f 2axis:%f 3axis:%f 4axis:%f \n",coordinate[i][0],coordinate[i][1],coordinate[i][2],coordinate[i][3]);
    }


}
