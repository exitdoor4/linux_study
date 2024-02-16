#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <syslog.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void daemonize(const char *cmd)
{
	int i, fd0, fd1, fd2;
	pid_t pid;
	struct rlimit rl;
	struct sigaction sa;

	umask(0);
	
	// getrlimit -> check resource limit
	// RLIMIT_NOFILE = maximun file number
	// <sys/resource.h>  
	if(getrlimit(RLIMIT_NOFILE, &rl) < 0)
	{
		printf("%s: can't get file limit\n", cmd);
		exit(0);
	}

	if((pid=fork()) <0)
	{
		printf("%s: can't fork\n", cmd);
		exit(0);
	}
	else if(pid !=0)
		exit(0);

	// create session
	setsid();

	sa.sa_handler=SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags=0;
	if(sigaction(SIGHUP, &sa, NULL) < 0)
	{
		printf("%s: can't ignore SIGHUB\n", cmd);
		exit(0);
	}
	if((pid=fork())<0)
		exit(0);

	// change root dir 
	if(chdir("/") <0)
	{
		printf("%s: can't change directory to /\n", cmd);
		exit(0);
	}
	// close opend file
	if(rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max == 1024;
	for(i=0;i<rl.rlim_max; i++)
			close(i);

	// fd will return to 0 and all them move  /dev/null
	// <unistd.h>
	// dup copy paramiter
	fd0=open("/dev/null", O_RDWR);
	fd1=dup(0);
	fd2=dup(0);

	openlog(cmd,LOG_CONS,LOG_DAEMON);
	if(fd0 != 0 || fd1 != 1 || fd2 != 2)
	{
		syslog(LOG_LOCAL0," unexpected fd : %d %d %d " ,fd0,fd1,fd2);
		exit(1);
	}

	syslog(LOG_LOCAL0, "helloworld! [%s] start", cmd);
}

int main(int argc, char* argv[])
{
	daemonize(argv[0]);

	// after 100 seconds, exit daemon
	sleep(100);
}
