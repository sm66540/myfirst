#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include<math.h>
#include<errno.h>
#include<signal.h>

#define SERV_PORT 5051
void sig_chld(int signo)
{
pid_t pid;
int stat;
while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
printf("child %d terminated\n", pid);
return;
}

int main(int argc, char **argv)
{ int listenfd, connfd;
pid_t childpid;
socklen_t clilen;
struct sockaddr_in cliaddr, servaddr;
void sig_chld(int);
listenfd = socket (AF_INET, SOCK_STREAM, 0);
bzero (&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(SERV_PORT);
bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
listen(listenfd,5);
signal (SIGCHLD, sig_chld); /* must call waitpid() */
for ( ; ; ) {
clilen = sizeof(cliaddr);
if ( (connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0) {
if (errno == EINTR)
continue; /* back to for() */
else
printf("accept error");
}
if ( (childpid = fork()) == 0) { /* child process */
close(listenfd); /* close listening socket */
exit(0);
}
close (connfd); /* parent closes connected socket */
}
}
