#ifndef __SIGNAL_H
#define __SIGNAL_H
 
typedef void (*Signal)(int sig);

int signal_register(Signal sig, int sigNum);
int notify_process(int pid, int sig);

#endif
