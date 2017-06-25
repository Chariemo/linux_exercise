#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include<sys/types.h>
#include <time.h>
#include <string.h>

#define SHM_KEY 99

main()
{
    int seg_id;
    char *mem_ptr;
    time_t now;
    int i=30;
    
    seg_id=shmget(SHM_KEY,100,IPC_CREAT|0777);
    if(seg_id==-1)
    {
	perror("shmget");
	exit(1);
    }
    mem_ptr= shmat(seg_id, 0, SHM_EXEC);
    if(mem_ptr==NULL)
    {
	perror("shmat");
	exit(1);
    }
    while(i>0)
    {
	time(&now);
	strcpy(mem_ptr,ctime(&now));
	sleep(1);
	i--;
    }
    shmctl(seg_id, IPC_RMID, 0);
}
