#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/msg.h>
#include <queue/queue.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>

void timer_handler(int signum)
{
    (void) signum;
}

int queue_init(int id)
{
  return msgget((key_t)id, 0666 | IPC_CREAT);
}

int queue_send(int queue_id, const queue_st *data, const int bSize)
{
  if(bSize <= 0)
    return -1;

  return msgsnd(queue_id, (void *)data, bSize, 0);
}

int queue_recv(int queue_id, queue_st *data, const int bSize, int timeout)
{
  struct sigaction sa;
  struct itimerval timer;

  if(!data || bSize  <= 0)
    return -1;

  if(timeout > 0)
  {
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &timer_handler;
    sigaction(SIGALRM, &sa, NULL);
    
    timer.it_value.tv_sec = timeout / 1000;
    timer.it_value.tv_usec = (timeout % 1000) * 1000;

    timer.it_interval.tv_sec = timeout / 1000;
    timer.it_interval.tv_usec = (timeout % 1000) * 1000;

    setitimer(ITIMER_REAL, &timer, NULL);
  }

  return msgrcv(queue_id, (void *)data, bSize, data->queueType, 0);
}

int queue_destroy(int queue_id)
{
  return msgctl(queue_id, IPC_RMID, 0);
}
