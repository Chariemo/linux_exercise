/*************************************************************************
	> File Name: my_pwd.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2017年03月20日 星期一 23时09分10秒
	> Description:
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    printf("%s\n", getcwd(NULL, 0));

    return EXIT_SUCCESS;
}
