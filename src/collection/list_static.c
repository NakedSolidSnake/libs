#include <collection/list_static.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct list
{  
  uint8_t *object_list;  
  int object_size;
  int list_size;
  int amount;
};

List *List_create(int list_size, int object_size)
{
    List *list = (List *)malloc(sizeof(List));
    if(!list)
      return NULL;

    memset(list, 0, sizeof(List));

    list->object_list = malloc(list_size * object_size);
    if(!list->object_list)
    {
      free(list);
      return NULL;
    }

    list->list_size = list_size;
    list->object_size = object_size;

    return list;
}

int List_add(List *list, void *object)
{
  if(list)
  {
    if(list->amount < list->list_size)
    {
      memcpy(&list->object_list[list->amount * list->object_size], object, list->object_size);
      list->amount++;
      return EXIT_SUCCESS;
    }
    else 
      return EXIT_FAILURE;
  }

  return EXIT_FAILURE;  
}

int List_remove(List *list, int pos)
{
  return EXIT_FAILURE;
}

int List_getObjectByIndex(List *list, int index, void *object)
{
  if(list && object)
  {
    if(index < list->amount)
    {
      memcpy(object, &list->object_list[index * list->object_size], list->object_size);
      return EXIT_SUCCESS;
    }
  }

  return EXIT_FAILURE;
}

int List_size(List *list)
{
  if(list)
    return list->amount;
  
  return -1;
}

int List_isEmpty(List *list)
{
  if(list)
    return list->amount == 0;
  
  return -1;
}

int List_clear(List *list)
{
  if(list)
  {
    memset(&list->object_list[0], 0, list->list_size * list->object_size);
    list->amount = 0;
    return EXIT_SUCCESS;
  }

  return -1;
}

int List_compare(List *list, int (*compare)(void *object_a, void *object_b))
{
  return EXIT_FAILURE;
}

int List_destroy(List *list)
{
  if(list)
  {
    if(list->object_list)
    {
      free(list->object_list);
    }

    free(list);
  }

  return EXIT_SUCCESS;
}
