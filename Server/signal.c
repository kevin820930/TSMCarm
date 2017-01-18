#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<signal.h>


void sig_usr(int sig)
{
    printf("rev sig=%d\n", sig);
}

int main(void)
{
    char buf[BUFSIZ];
    int n;
    struct sigaction act;
    act.sa_handler = sig_usr;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGUSR1, &act, NULL);
    //signal(SIGUSR1, sig_usr);
    while(1) {
        if((n = read(STDIN_FILENO, buf, BUFSIZ)) == -1) {
                printf("read is interrupted/n");
        }
        else {
            write(STDOUT_FILENO, buf, n);
      }
    }
    exit(0);
}


