#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<stdbool.h>
#include<string.h>
#include<sys/stat.h>
#include<time.h>
#include<pwd.h>
#include<dirent.h>
#include<grp.h>
#include<sys/types.h>

#define MAX_DIR 100

int count = 0; //文件数量

void ptime(long mytime) {
    struct tm *time;
    char *week[] = {"Sun", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat"};
    time = localtime(&mytime);
    printf("  %4d/%2d/%2d %s %2d:%2d:%2d", time->tm_year + 1900, time->tm_mon + 1, time->tm_mday
            , week[time->tm_wday], time->tm_hour, time->tm_min, time->tm_sec);
}

void ptype(mode_t mode) {
    char type[7] = {'p', 'c', 'd', 'b', '-', 'l', 's'};
    int index = ((mode>>12) & 0xf) / 2;
    printf("%c", type[index]);
    char *perm[8] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};
    printf("%s", perm[mode>>6 & 07]);
    printf("%s", perm[mode>>3 & 07]);
    printf("%s", perm[mode>>0 & 07]);
}

void pname_go(uid_t uid, gid_t gid) {
    struct passwd *user;
    user = getpwuid(uid);
    printf("  %-s", user->pw_name);

    struct group *group;
    group = getgrgid(gid);
    printf("  %-s", group->gr_name);
}

void pinfo(char *name) {

    struct stat node;
    if (stat(name, &node) == -1) {
        perror("stat");
        exit(EXIT_SUCCESS);
    }

    ptype(node.st_mode);
    pname_go(node.st_uid, node.st_gid);
    ptime(node.st_ctime);
    ptime(node.st_mtime);
    printf("  %s\n", name);
}

void listdir(char * path) {
    DIR * dir;
    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    struct dirent *node;
    while ((node = readdir(dir)) != NULL) {
        if (node->d_name[0] != '.') {
            pinfo(node->d_name);
        }
    }
    closedir(dir);
}

void riels_l(int argc, char *argv[]) {

    if (argc == 2) {
        listdir(".");
        exit(EXIT_SUCCESS);
    }
    if (argc == 3 && argv[1] != NULL) {
        pinfo(argv[2]);
    }
}


void myread(struct dirent **node, char *dirStr) {
    DIR * dir;
    if ((dir = opendir(dirStr)) == NULL) {
        perror("opendir");
        exit(-1);
    }
    while (true) {
        if (count <= MAX_DIR) {
            if ((node[count++] = readdir(dir)) == NULL) {
                perror("readdir");
                break;
            }
        }
        else {
            perror("num of dir > MAX_DIR");
            break;
        }
    }
    count--;
    closedir(dir);
}

void dirPrint(struct dirent **node) {
    int i;
    for (i = 0; i < count; i++) {
        if (node[i]->d_name[0] == '.') {
            continue;
        }
        printf("%-30s", node[i]->d_name);
        if (i % 5 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void merge(struct dirent ** node, int start, int mid, int end) {
    int sizeOfA = mid - start + 1,
        sizeOfB = end - mid;
    struct dirent stuA[MAX_DIR],
        stuB[MAX_DIR];
    int index = start, indexOfA = 0, indexOfB = 0;
    printf("***********\n");
    dirPrint(node);
    for (indexOfA = 0; indexOfA < sizeOfA; indexOfA++) {
        stuA[indexOfA] = *node[index++];
        printf("index: %d -> %s\n", indexOfA, stuA[indexOfA].d_name);
    }
    strcpy(stuA[sizeOfA].d_name, "~");

    for (indexOfB = 0; indexOfB < sizeOfB; indexOfB++) {
        stuB[indexOfB] = (*node)[index++];
    }
    strcpy(stuB[sizeOfB].d_name, "~");
    index = 0;
    while (index <= end) {
        if (stuA[indexOfA].d_name[0] <= stuB[indexOfB].d_name[0]) {
            (*node)[index++] = stuA[indexOfA++];
        }
        else {
            *(node)[index++] = stuB[indexOfB++];
        }
    }
}

void mergeSortByname(struct dirent **node, int start, int end) {
    if (start < end) {
        int mid = (int) (start + end) / 2;
        mergeSortByname(node, start, mid);
        mergeSortByname(node, mid + 1, end);
        merge(node, start, mid, end);
    }
}


int main(int argc, char * argv[]) {
    struct dirent *node[MAX_DIR];
    if (argc == 1) {
        myread(node, ".");
        dirPrint(node);
    }
    else {
        if (strcmp(argv[1], "-l") == 0) {
            riels_l(argc, argv);   
        }
    }
  //  mergeSortByname(node, 0, count - 1);
   // dirPrint(node);
    return 0;
}

