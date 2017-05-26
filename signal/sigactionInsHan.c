/*************************************************************************
	> File Name: sigactionIns1.c
	> Author: 
	> Mail: 
	> Created Time: Fri May 26 09:35:49 2017
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void handler(int signo) {

    printf("This is a signal handler\n");
}

int main(void) {

    struct sigaction action, oldaction;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, &oldaction);
    int i = 5;
    printf("waiting for signal ...\n");
    while (i-- >= 0) {
        pause();
    }

    return 0;
}
