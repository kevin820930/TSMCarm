#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<signal.h>

#define ERR_EXIT(m) \
    do { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while(0)

void handler(int sig);


int main(int argc, char *argv[])
{
    printf("%d\n",getpid());
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    if (sigaction(SIGINT, &act, NULL) < 0)
        ERR_EXIT("sigaction error");

    struct sigaction quit;
    quit.sa_handler = handler;
    sigemptyset(&quit.sa_mask);
    quit.sa_flags = 0;

    if (sigaction(SIGINT, &quit, NULL) < 0)
        ERR_EXIT("sigaction error");


    for (; ;)
        pause();

    return 0;

}

void handler(int sig)
{
    if(sig==2)
        printf("rev sig=%d\n", sig);
    else if(sig==3)
        printf("qrev sig=%d\n", sig);
}
