systemcall

- poll
int poll(struct pollfd *fds, nfds_t nfds, int timeout);

struct pollfd {
   int   fd;         /* file descriptor */
   short events;     /* requested events */
   short revents;    /* returned events */
};

nfds -> fds size 

- select 
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct tiemval *timeout)

nfds -> file total number
fd_set -> 1024 bit array 


