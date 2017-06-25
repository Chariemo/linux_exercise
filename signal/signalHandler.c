/*************************************************************************
	> File Name: sigactionInsSa_Sig.c
	> Author: 
	> Mail: 
	> Created Time: Fri May 26 09:46:17 2017
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

void handler(int signo, siginfo_t *siginfo, void * context) {

    if (signo == SIGINT) {
        printf("uid: %d\n", siginfo->si_uid);
    }
    else if (signo == SIGTERM) {
        printf("pid: %d\n", siginfo->si_pid);
    }
}

int main(void) {

    struct sigaction action, oldaction, act, olac;
    pid_t pid;

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        sigemptyset(&action.sa_mask);
        action.sa_flags = SA_SIGINFO | SA_RESETHAND;
        action.sa_sigaction = handler;
        sigaction(SIGINT, &action, &oldaction);
    
        sigemptyset(&act.sa_mask);
        act.sa_flags = SA_SIGINFO | SA_RESETHAND;
        act.sa_sigaction = handler;
        sigaction(SIGTERM, &act, &olac);

        int i = 3;
        printf("This is child thread %d, waiting for signal ...\n", getpid());
        while (i-- > 0) {
            pause();
        }

    }
    else {
        sleep(2);
        printf("send child thread %d a SIGING in 2 second\n", pid);
        sleep(2);
        kill(pid, SIGINT);
        /*printf("send child thread %d a SIGTERM in 2 second\n", pid);
        sleep(2);
        kill(pid, SIGTERM);*/
        printf("send child thread %d a SIGINT again in 2 second\n", pid);
        sleep(2);
        kill(pid, SIGINT);
    }
    return 0;
}
