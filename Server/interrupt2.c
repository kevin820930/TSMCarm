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
/* 系統調用signal()實際上調用了sigaction() */
__sighandler_t my_signal(int sig, __sighandler_t handler);

int main(int argc, char *argv[])
{
    my_signal(SIGINT, handler);

    for (; ;)
        pause();

    return 0;

}

__sighandler_t my_signal(int sig, __sighandler_t handler)
{
    struct sigaction act;
    struct sigaction oldact;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    if (sigaction(sig, &act, &oldact) < 0)
        return SIG_ERR;

    return oldact.sa_handler; // 返回先前的處理函數指針
}

void handler(int sig)
{
    printf("rev sig=%d\n", sig);
}
