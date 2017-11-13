/*************************************************************************
	> File Name: mycopy.c
	> Author: 
	> Mail: 
	> Created Time: Tue Nov  7 14:48:43 2017
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {

    FILE *fp_src, *fp_dst;
    char buf[128];
    int num;

    if (argc != 3) {
        printf("Usage %s <src_file> <dst_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fp_src = fopen(argv[1], "r")) == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    if ((fp_dst = fopen(argv[2], "w")) == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    do {
        num = fread(buf, 1, 128, fp_src);
        fwrite(buf, 1, num, fp_dst);
        if (feof(fp_src)) {
            break;
        }
    } while(1);

    fclose(fp_src);
    fclose(fp_dst);
}
