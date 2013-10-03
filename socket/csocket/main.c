#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

int main (int argc, char **argv)
{
  char *hostname = "www.yahoo.com";
  char ip[100];
  struct hostent *he;
  struct in_addr **addr_list;
  int sock, i;
  struct sockaddr_in server;
  char *message, server_reply[2000];

  if ((he = gethostbyname (hostname)) == NULL)
    {
      perror("gethostbyname()");
      exit(EXIT_FAILURE);
    }

  addr_list = (struct in_addr **) he->h_addr_list;

  for( i = 0; addr_list[i] != NULL; ++i )
    {
      strcpy (ip, inet_ntoa (*addr_list[i]));
    }

  printf("%s resolved to : %s\n", hostname, ip);

  sock = socket (AF_INET, SOCK_STREAM, 0);

  if( sock < 0 )
    {
      perror ("socket()");
      exit (EXIT_FAILURE);
    }

  server.sin_addr.s_addr = inet_addr (ip);
  server.sin_family = AF_INET;
  server.sin_port = htons (80);

  if (connect (sock, (struct sockaddr *) &server, sizeof (server)) < 0)
    {
      perror ("connect()");
      exit (EXIT_FAILURE);
    }

  puts ("Connected");

  message = "GET / HTTP/1.1\r\n\r\n";
  if ( send (sock, message, strlen (message), 0) < 0)
    {
      perror ("send()");
      exit (EXIT_FAILURE);
    }

  puts("Data Send\n");

  if (recv (sock, server_reply, 2000, 0) < 0)
    {
      perror ("recv()");
      exit (EXIT_FAILURE);
    }

  puts ("Reply received\n");
  puts (server_reply);

  close (sock);
  return 0;
}
