#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("chose a file to change mode:\n");
        exit(-1);
    }
    /*if (argc <= 2) {*/
        /*printf("chose a mode for the file \"%s\"\n", argv[1]);*/
        /*exit(-1);*/
    /*};*/
    if (chmod(argv[1], 0664) < 0) {
        perror("chmod");
        exit(EXIT_FAILURE);
    }
    return 0;
}
