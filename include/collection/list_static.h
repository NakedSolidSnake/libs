#ifndef __LIST_STATIC_H
#define __LIST_STATIC_H

/**
 * @brief 
 * 
 */
typedef struct list List;

/**
 * @brief 
 * 
 * @param list_size 
 * @param object_size 
 * @return List* 
 */
List *List_create(int list_size, int object_size);

/**
 * @brief 
 * 
 * @param list 
 * @param object 
 * @return int 
 */
int List_add(List *list, void *object);

/**
 * @brief 
 * 
 * @param list 
 * @param pos 
 * @return int 
 */
int List_remove(List *list, int pos);

/**
 * @brief 
 * 
 * @param list 
 * @param index 
 * @param object 
 * @return int 
 */
int List_getObjectByIndex(List *list, int index, void *object);

/**
 * @brief 
 * 
 * @param list 
 * @return int 
 */
int List_size(List *list);

/**
 * @brief 
 * 
 * @param list 
 * @return int 
 */
int List_isEmpty(List *list);

/**
 * @brief Remove all elements from the list
 * 
 * @param list instance which contains the current list 
 * @return int 
 */
int List_clear(List *list);

/**
 * @brief 
 * 
 * @param list 
 * @param compare 
 * @return int 
 */
int List_compare(List *list, int (*compare)(void *object_a, void *object_b));

/**
 * @brief 
 * 
 * @param list 
 * @return int 
 */
int List_destroy(List *list);

#endif
