/*************************************************************************
	> File Name: redirectLs.c
	> Author:
	> Mail:
	> Created Time: Fri May 12 09:11:48 2017
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/stat.h>

int main(int argc, char * argv) {

    pid_t pid;
    int fd;

    if ((fd = open("list.txt", O_WRONLY|O_CREAT|O_APPEND, 0644)) < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        dup2(fd, 1);
        if (execlp("ls", "ls", "-l", (void *)0) == -1) {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    }
    else {
        wait(NULL);
        close(fd);
    }

    return 0;
}
