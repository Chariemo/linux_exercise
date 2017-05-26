/*************************************************************************
	> File Name: sigactionInsSa_Sig.c
	> Author: 
	> Mail: 
	> Created Time: Fri May 26 09:46:17 2017
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void handler(int signo, siginfo_t *siginfo, void * context) {

    printf("In sa_sigaction ...\n");
}

int main(void) {

    struct sigaction action, oldaction;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = handler;
    sigaction(SIGINT, &action, &oldaction);
    int i = 3;
    printf("waiting for signal ...\n");
    while (i-- >= 0) {
        pause();
    }
    return 0;
}
