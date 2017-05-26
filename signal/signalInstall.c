/*************************************************************************
	> File Name: signalInstall.c
	> Author: 
	> Mail: 
	> Created Time: Fri May 26 09:18:16 2017
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void capture(int signo) {

    printf("Captured\n");
}

int main(void) {

    signal(SIGINT, capture);
    printf("waiting for signal SIGINT\n");
    int i = 0;
    while (i++ <= 10) {
        sleep(1);
    }
    return 0;
}
