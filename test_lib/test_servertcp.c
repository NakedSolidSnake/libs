#include <server/server_tcp.h>
#include <stdio.h>
#include <stdlib.h>

static int receive(char *buffer, int size);

int main()
{

  Server_t s = {
    .socket = -1,
    .port = "3404",
    .cb.recv = receive,
    .cb.send = NULL
  };

  Server_init(&s);
  Server_exec(&s);
}

static int receive(char *buffer, int size)
{
  printf("%s\n", buffer);
  return 0;
}
