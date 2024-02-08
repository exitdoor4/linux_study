//multiIO_select.c

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

#define FD_SIZE 3
#define BUF_SIZE 8

int main(int argc, char *argv[])
{
	int i, n , ret, fd_count, end_count = 0;
	int fds(FD_SIZE);
	char buf[BUF_SIZE] = {0,};
	struct timeval tv;

	fd_set retfds, readfds;

	if(argc !=4){
		printf("usage : %s file1 file2 file3\n",argv[0]);
		return 0;
	}

	FD_ZERO(&readfds);

	for(i=0; i< FD_SIZE; i++)
	{
		fds[i] = open(argv[i+1], O_RDONLY);
		if(fds[i] >=0)
		{
			FD_SET(fds[i], &readfds);
			fd_count = fds[i];
		}

	}

	while(1)
	{
		retfds = readfds;

		ret = select(fd_count + 1, &retfds, NULL,NULL,NULL);

		if(ret == -1)
		{
			perror("select error");
			exit(0);
		}

		for(i=0; i<FD_SIZE; i++)
		{
			if(FD_ISSET(fds[i], &retfds))
			{
				while(n=read(fds[i], buf, BUF_SIZE)) > 0
				{
					if(!strcmp(buf, "quit\n"))
					{
						FD_CLR(fds[i], &readfds);
						close(fds[i]);
						end_count++;

						if(end_count == FD_SIZE)
							exit(0);
						continue;
					}
					printf("fd[%d] - %s", fds[i], buf);
					memset(buf, 0x00, BUF_SIZE);
				}
			}
		}
	}
	return 0;
}



