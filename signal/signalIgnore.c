/*************************************************************************
	> File Name: signalIgnore.c
	> Author: 
	> Mail: 
	> Created Time: Fri May 26 09:24:14 2017
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<signal.h>

int main(void) {

    int i = 5;
    signal(SIGINT, SIG_IGN);
    printf("waiting for signal ...\n");
    while (i-- >= 0) {
        sleep(1);
        printf("Please Enter Ctrl+C to quit\n");
    }
}
