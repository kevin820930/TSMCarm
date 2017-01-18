#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){
    //创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每字都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("169.254.8.50");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口


    for(int n=0;connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1&&n<60;n++){
	printf("connecting\n");
	sleep(10);
	printf("can't connect,retry after 10s\n");
    }
    /*char buffer[40];
    int cache=read(sock, buffer, sizeof(buffer)-1);
    
    printf("Message form server: %s\n", cache,buffer);
    */
    int i=0,x=0;
    char str[99]="Hello World!\n";
    write(sock, str, 99);
    while(str!="0"){
    printf("Enter comment\n");
    fgets(str,99,stdin);
    write(sock,str, 99);
    }

    close(sock);
    return 0;
}
