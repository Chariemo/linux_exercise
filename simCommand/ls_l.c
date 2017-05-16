#include"./ls_l.h"
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<string.h>
#include<time.h>
#include<pwd.h>
#include<dirent.h>

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

    if (argc == 1) {
        listdir(".");
        exit(EXIT_SUCCESS);
    }
    if (argc == 2 && argv[1] != NULL) {
        pinfo(argv[1]);
    }
}
