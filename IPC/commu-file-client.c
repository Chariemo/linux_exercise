#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

main(int argc, char *argv[])
{
   int fd,len;
   char buf[128];
   if(argc!=2)
   {
	printf("error usage!\nusage: client filename");
	exit(1);
   }
   if((fd=)==-1)
   {
	perror("open");
	exit(1);
   }
   while((len=)>0)
   {
	write(1,buf,len);
   }
   close(fd);
}
