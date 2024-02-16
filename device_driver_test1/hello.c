#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	char *msg = "hello\r\n";
	char buffer[128]= {0,};

	int fd=open("/dev/driver", O_RDWR|O_NDELAY);
	if(fd <0)
	{
		printf("david open fail \n");
		return -1;
	}

	write(fd,msg,strlen(msg));
	read(fd,buffer,128);
	printf("read:%s\r\n",buffer);

	close(fd);

	return 0;
}
