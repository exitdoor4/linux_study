#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <poll.h>

#define FD_SIZE 3 
#define BUF_SIZE 128

int main(int argc, char *argv[]){
	char buf[BUF_SIZE];
	struct pollfd fdarr[FD_SIZE];
	int n, i , ret, end_count = 0;

	if(argc != 4){
		printf("usage : %s file1 file2 file3\n", argv[0]);
		return 0;
	}

	for( i= 0; i <FD_SIZE; i++)
	{
		int fd = open(argv[i+1],O_RDONLY);
		if (fd > 0)
		{
			fdarr[i].fd = fd;
			fdarr[i].events = POLLIN;
		}
	}

	while(1)
	{
		memset(buf, 0x00, BUF_SIZE);
		ret = poll(fdarr, FD_SIZE , -1);

		if (ret == -1)
		{
			perror("poll error");
			exit(0);
		}

		for(i = 0; i < FD_SIZE; i++)
		{
			if(fdarr[i].fd != -1 && fdarr[i].revents & POLLIN){
				while((n = read(fdarr[i].fd, buf, BUF_SIZE)) >0) {
					if (!strcmp(buf, "quit\n"))
					{
						close(fdarr[i].fd);
						fdarr[i].fd = -1;
						end_count ++;
						if(end_count == FD_SIZE)
							exit(0);
						continue;
					}
					printf("fd[%d] - %s", fdarr[i].fd , buf);
				}
			}
		}
	}
	return 0;
}
