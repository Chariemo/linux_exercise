/*************************************************************************
	> File Name: my_who.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2017年03月20日 星期一 22时07分43秒
	> Description: who命令的简单实现
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <utmp.h>
#include <time.h>

// 显示时间
void timeToStr(time_t time, char timeStr[])
{
    strcpy(timeStr, ctime(&time));
    timeStr[strlen(timeStr) - 1] = '\0';
}

// 显示信息,将info中的信息显示出来
void displayInfo(struct utmp *info) {
    char timeStr[32];
    timeToStr(info->ut_tv.tv_sec, timeStr);
    printf("%s\t", info->ut_user);
    printf("%s\t", info->ut_line);
    printf("%s", timeStr);
    printf("(%s)\n", info->ut_host);
}

// my_who
void myWho(int fd) {
    struct utmp info;
    while(read(fd, &info, sizeof(info)) > 0) {
        if (info.ut_type == USER_PROCESS) {
            displayInfo(&info);
        }
    }
}


int main(int argc, char *argv[]) {
    int fd = open("/var/run/utmp", O_RDONLY);

    if (fd < 0) {
        perror("open utmp");
        return EXIT_FAILURE;
    }
    
    myWho(fd);

    close(fd);


    return EXIT_SUCCESS;
}
