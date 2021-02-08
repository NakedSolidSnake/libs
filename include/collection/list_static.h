#ifndef __LIST_STATIC_H
#define __LIST_STATIC_H


typedef struct list List;

List *List_create(int list_size, int object_size);
int List_add(List *list, void *object);
int List_remove(List *list, int pos);
int List_size(List *list);
int List_isEmpty(List *list);
int List_compare(List *list, int (*compare)(void *object_a, void *object_b));
int List_destroy(List *list);

#endif
