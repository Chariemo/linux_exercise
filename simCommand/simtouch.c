#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdlib.h>

void createfile(char *filename) {
    int fd;
    if ((fd = creat(filename, 0644))) {
        perror("creat");
        exit(EXIT_FAILURE);
    }
}
int main(int argc, char *argv[]) {

    if (argc > 1) {
        createfile(argv[1]);
        return 0;
    }
    createfile("defualt");
    return 0;
}
