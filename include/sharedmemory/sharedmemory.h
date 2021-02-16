#ifndef __SHAREDMEMORY_H
#define __SHAREDMEMORY_H

typedef struct shm_t
{
  int id;
  void *shm;
}shm_t;

/**
 * @brief 
 * 
 * @param shm 
 * @param key 
 * @param dataSize 
 * @return int 
 */
int sharedMemoryInit(shm_t *shm, int key, int dataSize);

/**
 * @brief 
 * 
 * @param shm 
 * @param buff 
 * @param offset 
 * @param size 
 * @return int 
 */
int sharedMemoryWrite(shm_t *shm, void *buff, int offset, int size);

/**
 * @brief 
 * 
 * @param shm 
 * @param buff 
 * @param offset 
 * @param size 
 * @return int 
 */
int sharedMemoryRead(shm_t *shm, void *buff, int offset, int size);

/**
 * @brief 
 * 
 * @param shm 
 * @return int 
 */
int sharedMemoryDestroy(shm_t *shm);

#endif
