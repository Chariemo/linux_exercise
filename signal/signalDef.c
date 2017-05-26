/*************************************************************************
	> File Name: signalDef.c
	> Author: 
	> Mail: 
	> Created Time: Fri May 26 08:12:11 2017
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void handler(int signo) {

    printf("In handler\n");
    printf("ResetHandler\n");
    signal(signo, SIG_DFL);
}

int main(void) {

    signal(SIGINT, handler);
    printf("Waiting for signal\n");
    while (1) {
        sleep(2);
    }
    return 0;
}
