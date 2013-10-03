#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#define MAXHOSTNAME 256
using namespace std;

int main()
{
  struct sockaddr_in socketInfo;
  char sysHost[MAXHOSTNAME+1];
  struct hostent *hPtr;
  int socketHandle;
  int portNumber = 8080;

  bzero(&socketInfo, sizeof(sockaddr_in));

  gethostname(sysHost, MAXHOSTNAME);
  if((hPtr = gethostbyname(sysHost)) == NULL )
    {
      cerr << "System hostname misconfigured."<< endl;
      exit(EXIT_FAILURE);
    }

  if((socketHandle = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      close(socketHandle);
      exit(EXIT_FAILURE);
    }

  socketInfo.sin_family = AF_INET;
  socketInfo.sin_addr.s_addr = htonl(INADDR_ANY);
  socketInfo.sin_port = htons(portNumber);

  if( bind(socketHandle, (struct sockaddr *) &socketInfo, sizeof(socketInfo)) < 0)
    {
      close(socketHandle);
      perror("bind");
      exit(EXIT_FAILURE);
    }

  listen(socketHandle, 1);

  int socketConnection;
  if( (socketConnection = accept(socketHandle, NULL, NULL)) < 0)
    {
      exit(EXIT_FAILURE);
    }
  close(socketHandle);

  int rc = 0;
  char buf[512];

  rc = recv(socketConnection, buf, 512, 0);
  buf[rc] = (char) NULL;

  cout << "Number of bytes read: " << rc << endl;
  cout << "Received: " << buf << endl;
  return 0;
}
