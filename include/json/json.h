#ifndef JSON_H_
#define JSON_H_

#include <stdbool.h>

#define getItems(x)(sizeof(x) / sizeof(x[0]))

typedef enum 
{
    eType_Int,
    eType_Double,
    eType_String,
    eType_Boolean,
    eType_Object
} eType;

/**
 * @brief 
 * 
 */
typedef struct
{
    const char *token;
    void *data;
    eType type;
    void *child;
    int size;
} IHandler;

/**
 * @brief Get the Json From File object
 * 
 * @param filename 
 * @param buffer 
 * @param b_size 
 * @return true 
 * @return false 
 */
bool JSON_GetFromFile(const char *filename, void *buffer, size_t b_size);

/**
 * @brief 
 * 
 * @param buffer 
 * @param ihandler_list 
 * @param ihandler_size 
 * @return true 
 * @return false 
 */
bool JSON_Process(void *buffer, const IHandler *ihandler_list, size_t ihandler_size);

#endif /* JSON_H_ */
