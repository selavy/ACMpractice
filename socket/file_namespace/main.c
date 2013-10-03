#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>

int make_named_socket( const char *filename )
{
  struct sockaddr_un name;
  int sock;
  size_t size;

  sock = socket( PF_UNIX, SOCK_DGRAM, 0);
  if( sock < 0 ) /* -1 => error */
    {
      perror ("socket");
      exit (EXIT_FAILURE);
    }

  name.sun_family = AF_FILE;
  strcpy (name.sun_path, filename);

  size = (offsetof (struct sockaddr_un, sun_path)
	  + strlen (name.sun_path) + 1);

  if (bind (sock, (struct sockaddr *) &name, size) < 0)
    {
      perror ("bind");
      exit(EXIT_FAILURE);
    }

  return sock;
}

int main( int argc, char ** argv )
