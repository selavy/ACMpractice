#include <stdio.h>
#include <stddef.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main ( int argc, char ** argv )
{
  int sock;
  struct sockaddr_in name;

  sock = socket (AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    {
      perror ("socket()");
      exit (EXIT_FAILURE);
    }


  return 0;
}
