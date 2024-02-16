#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int dev;
	char buff[1024];

	printf("Device driver test.\n");
	
	dev = open("/dev/test_device", O_RDWR);
	if(dev < 0)
	{
		printf("can't find /dev/driver");
		return -1;
	}
	
	printf("dev = %d\n", dev);
		
	write(dev,'1234',4);
	read(dev, buff, 4);
	printf("read from device: %s\n", buff);
	close(dev);

	exit(EXIT_SUCCESS);
}
