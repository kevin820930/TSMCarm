#include<stdlib.h>
#include<stdio.h>
#include"generator.h"
#include"routplanning.h"

int waitaccess(FILE *nc,int access,int communication);
long double suck(FILE *nc,int touch);
long double put(FILE *nc,int touch);
int sendcomplete(FILE *nc,int complete,int communication);

void generator(anglelist *go[10],int scheduling[100][2]){

    const int complete=11,access=10,touch=12,grab=13,communication=322;//O pin

    long double savedata[80][4];
    int i,number,count;
    long double afterz;
    FILE *ncfile;
    int tesknum=0;
    if(!(ncfile=fopen("Nccode.txt","a"))){
        printf("write Nccode failed\r\n");
    }
    fprintf(ncfile,"%%@MACRO\r\n#1510 := @115221;\r\n");
    fprintf(ncfile,"MOVJ C1=0.0 C2=0.0 C3=0.0 C4=0.0 FJ20;\r\n");
    for(i=0;scheduling[i][0]!=0;i++){

	//catch
	number=scheduling[i][0];
	count=0;

	waitaccess(ncfile,access,communication);

	anglelist *tmp=(anglelist *)malloc(sizeof(anglelist));
        tmp=go[number-1];
	while(tmp!=NULL){
	    fprintf(ncfile,"MOVJ C1=%LF C2=%LF C3=%LF C4=%LF FJ10 PL10;\r\n",tmp->one,tmp->two,tmp->three,tmp->four);
	    savedata[count][0]=tmp->one;
	    savedata[count][1]=tmp->two;
	    savedata[count][2]=tmp->three;
	    savedata[count][3]=tmp->four;
	    tmp=tmp->nextangle;
	    count++;
	}
	count--;

	afterz=suck(ncfile,touch);

	while(count!=0){
	    fprintf(ncfile,"MOVJ C1=%LF C2=%LF C3=%LF C4=%LF FJ10 PL10;\r\n",savedata[count][0],afterz,savedata[count][2],savedata[count][3]);
	    count--;
	}
	sendcomplete(ncfile,complete,communication);

	//put
        number=scheduling[i][1];
        count=0;

        waitaccess(ncfile,access,communication);

        tmp=go[number-1];
        while(tmp!=NULL){
            fprintf(ncfile,"MOVJ C1=%LF C2=%LF C3=%LF C4=%LF FJ10 PL10;\r\n",tmp->one,tmp->two,tmp->three,tmp->four);
            savedata[count][0]=tmp->one;
            savedata[count][1]=tmp->two;
            savedata[count][2]=tmp->three;
            savedata[count][3]=tmp->four;
            tmp=tmp->nextangle;
            count++;
        }
	count--;
        afterz=put(ncfile,touch);
        while(count!=0){
            fprintf(ncfile,"MOVJ C1=%LF C2=%LF C3=%LF C4=%LF FJ10 PL10;\r\n",savedata[count][0],afterz,savedata[count][2],savedata[count][3]);
            count--;
        }
	sendcomplete(ncfile,complete,communication);
	
    }
    
    fprintf(ncfile,"M30;\r\n");

    //printf("begin code generate,%LF,%LF\n",go[0]->one,go[0]->two);
    
}


int waitaccess(FILE *nc,int access,int communication){

    fprintf(nc,"SETDO(%d,1);\r\n",communication);
    fprintf(nc,"WHILE (@%d=0) DO\r\nSLEEP();\r\nEND_WHILE;\r\n",access);
    fprintf(nc,"SETDO(%d,0);\r\n",access);
    
    return 1;

}

long double suck(FILE *nc,int touch){

    //fprintf(nc,"WHILE (@%d=0) DO\r\nSLEEP();\r\nEND_WHILE;\r\n",touch);
    //fprintf(nc,"SETDO(%d,0);\r\n",touch);

    return 0;

}

long double put(FILE *nc,int touch){

    //fprintf(nc,"WHILE (READDO(%d)=0) DO\r\nSLEEP();\r\nEND_WHILE;\r\n",touch);
    //fprintf(nc,"SETDO(%d,0);\r\n",touch);

    return 0;

}

int sendcomplete(FILE *nc,int complete,int communication){

    //fprintf(nc,"SETDO(%d,1);\r\n",communication);
    //fprintf(nc,"WHILE (READDO(%d)=0) DO\r\nSLEEP();\r\nEND_WHILE;\r\n",complete);
    //fprintf(nc,"SETDO(%d,0);\r\n",complete);
}
