#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void * sigone_program(void *arg);
void * sigtwo_program(void *arg);
void *sigthree_program(void *arg);

int main(int argc, char *argv[]) {

    int i;
    void *status;
    sigset_t set;
    sigfillset(&set);
    sigdelset(&set, SIGINT);
    sigdelset(&set, SIGSTOP);
    //屏蔽所有信号
    pthread_sigmask(SIG_SETMASK, &set, NULL);
    pthread_t thread_one, thread_two, thread_three;
    if (pthread_create(&thread_one, NULL, sigone_program, NULL) != 0) {
        fprintf(stderr, "pthread_create failure\n");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread_two, NULL, sigtwo_program, NULL) != 0) {
        fprintf(stderr, "pthread_create failure\n");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&thread_three, NULL, sigthree_program, NULL) != 0) {
        fprintf(stderr, "pthread_create failure\n");
        exit(EXIT_FAILURE);
    }

    pthread_join(thread_two, NULL);
    pthread_join(thread_one, NULL);
    pthread_join(thread_three, NULL);
    return 0;
}

//产生SIGUSR1信号
void *sigone_program(void *arg) {
    
    int i;
    for (i = 0; i < 5; i++) {
        printf("tahis is %u thread, and i will send a SIGUSR1 to the thread group\n", pthread_self());
        kill(0, SIGUSR1);
        sleep(3);
    }
}

//产生SIGUSR2信号
void *sigtwo_program(void *arg) {
    
    int i;
    for (i = 0; i < 5; i++) {
        printf("this is %u thread, and i will send a SIGUSR2 to the thread group\n", pthread_self());
        kill(0, SIGUSR2);
        sleep(3);
    }
}

//对信号进行处理
void *sigthree_program(void *arg) {
    
    int i;
    sigset_t waitSet;
    sigfillset(&waitSet);
    int waitRet, sigNo;
    printf("this is thread %u, wait for signal...\n", pthread_self());
    for (i = 0; i < 10; i++) {
        waitRet = sigwait(&waitSet, &sigNo);
        printf("this is thread %u, sigwait return %d, signo = %d\n", pthread_self(), waitRet, sigNo);
    }
}
