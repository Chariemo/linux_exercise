/*************************************************************************
	> File Name: rieRedirect.c
	> Author:
	> Mail:
	> Created Time: Fri May 12 08:21:12 2017
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/wait.h>

int main(int argc, char *argv[]) {

    int fds[2];
    pid_t pid;
    int fd;

    if (pipe(fds) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        char buf[256];
        if ((fd = creat("result.txt", 0644)) < 0) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd, 1);
        dup2(fds[0], 0);
        close(fds[1]);
        execlp("sort", "sort", (void *)0);
    }
    else {
        if ((pid = fork()) < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            dup2(fds[1], 1);
            close(fds[0]);
        //    fd = open("infile.txt", O_RDONLY);
        //   dup2(fd, 0);
            execlp("who", "who", (void *)0);
        }
        else {
            close(fds[0]);
            close(fds[1]);
            wait(NULL);
            wait(NULL);
        }
    }

    return  0;
}
