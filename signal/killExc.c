/*************************************************************************
	> File Name: killExc.c
	> Author: 
	> Mail: 
	> Created Time: Fri May 26 09:56:25 2017
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

int main(void) {

    pid_t pid;
    
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        printf("This is child Thread %d, and I will sleep 60 seconds\n", getpid());
        sleep(60);
    }
    else {
        printf("This is pThread %d, I will kill child thread %d in %d seconds\n", getpid(), pid, 5);
        sleep(5);
        kill(pid, SIGINT);
        printf("child thread %d has been killed\n", pid);
    }

    return 0;
}
