#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include<unistd.h>
#include <time.h>

#define SHM_KEY  99

int main(void)
{
    int seg_id;
    char *mem_ptr;
    int count = 20;

    if((seg_id= shmget(SHM_KEY, 100, IPC_CREAT|0777))==-1)
    {
	perror("shmget");
	exit(1);
    }
    while (count-- > 0) {
    mem_ptr= shmat(seg_id, 0, SHM_RDONLY);
    if(mem_ptr==NULL)
    {
	perror("shmat");
	exit(1);
    }
    printf("The time from server is:%s\n",mem_ptr);
        sleep(1);
    }
    shmdt(mem_ptr);
    return 0;
}
