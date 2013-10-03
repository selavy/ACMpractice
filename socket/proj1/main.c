#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#define MAXHOSTNAME 256

int main( int argc, char ** argv )
{
  struct sockaddr_in socket_addr;
  char sys_host[MAXHOSTNAME+1];
  struct hostNamePtr *hPtr;
  int portNumber = 8080;
  int socket_hndl;
  if((socket_hndl = socket( AF_INET, SOCK_STREAM, IPPROTO_IP)) < 0)
    {
      fputs(stderr, "unable to open socket\n");
      exit(EXIT_FAILURE);
    }
  return 0;
}
