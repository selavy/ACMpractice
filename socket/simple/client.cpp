#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <strings.h>
#include <stdlib.h>
#define MAXHOSTNAME 256
using namespace std;

int main()
{
  struct sockaddr_in remoteSocketInfo;
  struct hostent *hPtr;
  int socketHandle;
  char *remoteHost = "localhost";
  int portNumber = 8080;

  bzero(&remoteSocketInfo, sizeof(sockaddr_in));

  if((hPtr = gethostbyname(remoteHost)) == NULL)
    {
      cerr << "System DNS name resolution not configured properly." << endl;
      cerr << "Error number: "<< ECONNREFUSED << endl;
      exit(EXIT_FAILURE);
    }

  if((socketHandle = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      close(socketHandle);
      exit(EXIT_FAILURE);
    }

  memcpy((char*)&remoteSocketInfo.sin_addr, hPtr->h_addr, hPtr->h_length);
  remoteSocketInfo.sin_family = AF_INET;
  remoteSocketInfo.sin_port = htons((u_short)portNumber);

  if(connect(socketHandle, (struct sockaddr *)&remoteSocketInfo, sizeof(sockaddr_in)) < 0)
    {
      close(socketHandle);
      exit(EXIT_FAILURE);
    }

  int rc = 0;
  char buf[512];

  strcpy(buf, "Message to send");
  send(socketHandle, buf, strlen(buf)+1, 0);
  return 0;
}
