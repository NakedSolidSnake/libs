#include <signal/signal.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int signal_register(Signal sig, int sigNum)
{
  struct sigaction s;
  int ret;

  if(!sig)
    return -1;

  s.sa_handler = sig;

  ret = sigfillset(&s.sa_mask);
  if(ret < 0){
    return -1;
  }

  s.sa_flags = 0;

  ret = sigaction(sigNum, &s, 0); 
  if(ret < 0){
    return -1;
  }

  return 0;
}


int notify_process(int pid, int sig)
{
  return kill((pid_t) pid, sig);
}
