#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


int Sock;

int main(){

    int Server();//setup server
    void Setup();
    void Initial();//initialize coordinate of platform
    void SendToPi();//Send message to pi
    

    Sock=Server();

    Setup();



}


int Server(){

}

void Setup(){



}

void Initail(){


}
