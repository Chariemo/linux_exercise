/*************************************************************************
	> File Name: mmapcopy.c
	> Author: 
	> Mail: 
	> Created Time: Mon Oct 23 17:24:10 2017
 ************************************************************************/

#include<stdio.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

void mmapcopy(int src_fd, size_t len, int dst_fd);

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage: %s <src_file> <dst_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int src_fd;
    int dst_fd;
    if ((src_fd = open(argv[1], O_RDONLY)) < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if ((dst_fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC | S_IRWXU)) < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct stat filestat;
    fstat(src_fd, &filestat);
    truncate(argv[2], filestat.st_size);
    mmapcopy(src_fd, filestat.st_size, dst_fd);

    close(src_fd);
    close(dst_fd);
}

void mmapcopy(int src_fd, size_t len, int dst_fd) {
    
    void *src_ptr, * dst_ptr;
    src_ptr = mmap(NULL, len, PROT_READ, MAP_PRIVATE, src_fd, 0);
    dst_ptr = mmap(NULL, len, PROT_WRITE | PROT_READ, MAP_SHARED, dst_fd, 0);
    if (dst_ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    memcpy(dst_ptr, src_ptr, len);

    munmap(src_ptr, len);
    munmap(dst_ptr, len);
}

