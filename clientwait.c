#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include<math.h>
#include<errno.h>
#include<signal.h>

int main (int argc, char **argv)
{
int i, sockfd[5];
struct sockaddr_in servaddr;
if (argc != 2)
perror("sds");
for (i = 0; i < 5; i++) {
sockfd[i] = socket (AF_INET, SOCK_STREAM, 0);
bzero (&servaddr, sizeof (servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons (5051);
inet_pton (AF_INET, argv[1], &servaddr.sin_addr);
connect (sockfd[i], (struct sockaddr *) &servaddr, sizeof (servaddr));
}
//str_cli (stdin, sockfd[0]); /* do it all */
exit(0);
}

