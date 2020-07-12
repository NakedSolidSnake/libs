#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/msg.h>
#include <queue/queue.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>


static int compare(struct timespec *start, struct timespec *end, struct timespec *offset);

int queue_init(int id)
{
  return msgget((key_t)id, 0666 | IPC_CREAT);
}

int queue_send(int queue_id, const queue_st *data, const int bSize)
{
  if (bSize <= 0)
    return -1;

  return msgsnd(queue_id, (void *)data, bSize, 0);
}

int queue_recv(int queue_id, queue_st *data, const int bSize, int timeout)
{
  struct timespec start, finish, offset; 
  int flags = 0;
  int ret = 0;

  if (!data || bSize <= 0)
    return -1;

  if (timeout > 0)
  {
 
    flags = IPC_NOWAIT;

    offset.tv_sec = (timeout / 1000000000) ;
    offset.tv_nsec = (timeout % 1000000000);

    clock_gettime(CLOCK_MONOTONIC, &start);
  }

  do
  {    
    ret = msgrcv(queue_id, (void *)data, bSize, data->queueType, flags);
    clock_gettime(CLOCK_MONOTONIC, &finish);
  } while (compare(&start, &finish, &offset) && (ret < 0));

  return ret;
}

int queue_destroy(int queue_id)
{
  return msgctl(queue_id, IPC_RMID, 0);
}

static int compare(struct timespec *start, struct timespec *end, struct timespec *offset)
{
  double _start = (double)start->tv_sec + (double)start->tv_nsec / (double)1000000000;
  double _end = (double)end->tv_sec + (double)end->tv_nsec / (double)1000000000;
  double _offset = (double)offset->tv_sec + (double)offset->tv_nsec / (double)1000000000;

  return ((_start + _offset) > _end);
}
