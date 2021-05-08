#include <server/tcp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define ISVALIDSOCKET(s) ((s) >= 0)

int Server_init(Server_t *server)
{
  struct addrinfo hints;

  if (!server)
    return -1;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  struct addrinfo *bind_address;
  getaddrinfo(0, server->port, &hints, &bind_address);

  server->socket = socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);
  if (!ISVALIDSOCKET(server->socket))
  {
    fprintf(stderr, "socket() failed. (%d)\n", errno);
    return 1;
  }

  int yes = 1;
  if (setsockopt(server->socket, SOL_SOCKET, SO_REUSEADDR, (void *)&yes, sizeof(yes)) < 0)
  {
    fprintf(stderr, "setsockopt() failed. (%d)\n", errno);
  }

  if (bind(server->socket, bind_address->ai_addr, bind_address->ai_addrlen))
  {
    fprintf(stderr, "bind() failed. (%d)\n", errno);
    return 1;
  }
  freeaddrinfo(bind_address);

  if (listen(server->socket, LISTEN_AMOUNT) < 0)
  {
    fprintf(stderr, "listen() failed. (%d)\n", errno);
    return 1;
  }

  FD_ZERO(&server->master);
  FD_SET(server->socket, &server->master);
  server->max_socket = server->socket;

  return 0;
}

int Server_exec(Server_t *server)
{ 
  int ret;

  struct timeval timeout;
  timeout.tv_sec = (server->timeout / 1000000) ;
  timeout.tv_usec = (server->timeout % 1000000);

  if (!ISVALIDSOCKET(server->socket))
  {
    fprintf(stderr, "socket() failed. (%d)\n", errno);
    return 1;
  }

  while (1)
  {
    fd_set reads;
    reads = server->master;
    ret = select(server->max_socket + 1, &reads, 0, 0, &timeout);
    if (ret == -1)
    {       
      break;
    }

    else if (ret == 0){
      break;
    }    

    int i;
    for (i = 1; i <= server->max_socket; ++i)
    {
      if (FD_ISSET(i, &reads))
      {

        if (i == server->socket)
        {
          struct sockaddr_storage client_address;
          socklen_t client_len = sizeof(client_address);
          int socket_client = accept(server->socket, (struct sockaddr *)&client_address, &client_len);
          if (!ISVALIDSOCKET(socket_client))
          {
            fprintf(stderr, "accept() failed. (%d)\n",
                    errno);
            return 1;
          }

          FD_SET(socket_client, &server->master);
          if (socket_client > server->max_socket)
            server->max_socket = socket_client;

          char address_buffer[100];
          getnameinfo((struct sockaddr *)&client_address, client_len, address_buffer, sizeof(address_buffer), 0, 0,
                      NI_NUMERICHOST);
          break;
        }
        else
        {
          char buffer[MAX_BUFFER_SEND_RECV] = {0};
          int bytes_received = recv(i, buffer, 1024, 0);
          if (bytes_received < 1)
          {
            FD_CLR(i, &server->master);
            close(i);
            continue;
          }

          //Server process
          server->cb.recv(buffer, bytes_received);

          if (server->cb.send)
          {
            server->cb.send(buffer, &bytes_received);
            send(i, buffer, bytes_received, 0);
          }
        }

      } //if FD_ISSET
    }   //for i to max_socket
  }     //while(1)  
  return 0;
}

int Server_close(Server_t *server)
{
  if (!ISVALIDSOCKET(server->socket))
  {
    fprintf(stderr, "socket() failed. (%d)\n", errno);
    return 1;
  }

  return close(server->socket);  
}
