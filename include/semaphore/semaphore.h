#ifndef __SEMAPHORE_H
#define __SEMAPHORE_H

#define LOCKED      1
#define UNLOCKED    0

typedef struct sema 
{
  int id;
  int sema_count;
  int state;
}sema_t;

int semaphore_init(sema_t *s, int key);

int semaphore_lock(sema_t *s);

int semaphore_unlock(sema_t *s);

int semaphore_destroy(sema_t *s);

#endif
