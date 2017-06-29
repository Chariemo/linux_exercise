#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
   int fd,len;
   char buf[128];
   if(argc!=2)
   {
	printf("error usage!\nusage: client filename");
	exit(1);
   }
   if((fd= open(argv[1], O_RDONLY))==-1)
   {
	perror("open");
	exit(1);
   }
   while((len= read(fd, buf, 128))>0)
   {
	write(1,buf,len);
   }
   close(fd);
    return 0;
}
