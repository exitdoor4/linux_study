#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int fd, ret;
	char buffer[32];

	if(argc != 2)
	{
		printf("usage : %s file \n", argv[0]);
		exit(0);
	}

	fd = open(argv[1], O_WRONLY|O_APPEND);

	if (fd < 0)
	{
		perror("file error");
		exit(0);
	}

	while(1)
	{
		fgets(buffer, sizeof(buffer), stdin);

		ret = write(fd, buffer, strlen(buffer));

		if (ret < 0)
		{
			perror("write error");
			exit(0);

		}

		if(!strcmp(buffer, "quit\n")) break;
	}

	close(fd);
	return 0;
}
