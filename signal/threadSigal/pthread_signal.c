#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void * sigone_program(void *arg);
void * sigtwo_program(void *arg);
void *sigthree_program(void *arg);
void report(int);
void fun(int);

int main(int argc, char *argv[]) {

    int i;
    void *status;
    sigset_t set;
    sigfillset(&set);
    //sigdelset(&set, SIGUSR1);
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
    sleep(1);

    printf("this is parent, send SIGUSR1, SIGUSR2 to thread %u\n", thread_one);
    if (pthread_kill(thread_one, SIGUSR1) != 0) {
        perror("pthread_kill");
        exit(EXIT_FAILURE);
    }
    if (pthread_kill(thread_one, SIGUSR2)  != 0) {
        perror("pthead_kill");
        exit(EXIT_FAILURE);
    }
    
    printf("this is parent, send SIGUSR1, SIGUSR2 to thread %u\n", thread_two);
    if (pthread_kill(thread_two, SIGUSR1) != 0) {
        perror("pthread_kill");
        exit(EXIT_FAILURE);
    }
    if (pthread_kill(thread_two, SIGUSR2) != 0) {
        perror("pthread_kill");
        exit(EXIT_FAILURE);
    }

    sleep(10);
    
    //kill(0, SIGINT);
    if (pthread_kill(thread_one, SIGKILL) != 0) {
        perror("pthread_kill");
        exit(EXIT_FAILURE);
    }
    pthread_join(thread_two, NULL);
    pthread_join(thread_one, NULL);
    pthread_join(thread_three, NULL);
    return 0;
}

void *sigone_program(void *arg) {
    
    int i;
    sigset_t set;
    signal(SIGUSR1, report);
    sigfillset(&set);
    sigdelset(&set, SIGUSR2);
    //pthread_sigmask(SIG_SETMASK, &set, NULL);
    for (i = 0; i < 5; i++) {
        printf("this is set mask %u thread\n", pthread_self());
        pause();
    }
}

void report(int sig) {
    
    printf("\nin fisrt sigalHandler, the sig = %d\t, the thread id = %u\n", sig, pthread_self());
    //signal(SIGUSR1, fun);
}

void fun(int sig) {
    printf("\nin second signalHandler, the sig = %d\t, the thread id = %u\n", sig, pthread_self());
}

void *sigtwo_program(void *arg) {
    
    int i;
    signal(SIGUSR2, report);
    for (i = 0; i < 5; i++) {
        printf("this is set mask %u thread\n", pthread_self());
        pause();
    }
}

void *sigthree_program(void *arg) {
    
    int i;
    sigset_t waitSet;
    sigfillset(&waitSet);
    sigdelset(&waitSet, SIGUSR1);
    int waitRet, sigNo;
    printf("this is thread %u, wait for signal...\n", pthread_self());
    for (i = 0; i < 5; i++) {
        waitRet = sigwait(&waitSet, &sigNo);
        printf("this is thread %u, sigwait return %d, signo = %d\n", pthread_self(), waitRet, sigNo);
    }
}
