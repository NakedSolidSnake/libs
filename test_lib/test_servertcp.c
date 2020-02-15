#include <server/server_tcp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{

  Server_t s = {
    .port = "3094"
  };

  Server_init(&s);

  Server_exec(&s);
}
