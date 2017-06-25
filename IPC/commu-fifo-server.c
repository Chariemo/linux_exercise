#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

main(int argc, char * argv[])
{
   int fd;
   time_t now;
   char * message;
   if(argc!=2)
   {
	printf("errror usage!\nusage: server fifoname\n");
	exit(1);
   }
   unlink(argv[1]);
   if(==-1)
   {
	perror("mkfifo");
	exit(1);
   }
   if((fd=)==-1)
   {
	perror("open");
	exit(1);
   }
   while(1)
   {
	time(&now);
	
	if(write(fd,message,strlen(message))==-1)
	{
	   perror("write");
	   exit(1);
	}
	sleep(1);
   }
}
