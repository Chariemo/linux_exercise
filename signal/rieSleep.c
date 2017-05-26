/*************************************************************************
	> File Name: rieSleep.c
	> Author: 
	> Mail: 
	> Created Time: Fri May 26 10:08:28 2017
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void wakeup(int signo) {

    printf("Captured a signal to Wake up\n");
}

int main(int argc, char *argv[]) {

    long time;
    if (argc < 2) {
        printf("Usage: ./rieSleep 5\n");
        exit(EXIT_FAILURE);
    }
    time  = atoi(argv[1]);
    signal(SIGALRM, wakeup);
    alarm(time);
    printf("sleeping...\n");
    pause();
    printf("Wake up\n");
    return 0;
}
