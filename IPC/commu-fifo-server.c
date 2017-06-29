#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char * argv[])
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
   if(mkfifo(argv[1], 0644)==-1)
   {
       perror("mkfifo");
       exit(1);
   }
   if((fd=open(argv[1], O_WRONLY))==-1)
   {
       perror("open");
       exit(1);
   }
   while(1)
   {
       time(&now);
       message = ctime(&now);
       if(write(fd,message,strlen(message))==-1)
       {
           perror("write");
           exit(1);
       }
       sleep(1);
   }

    return 0;
}
