#ifndef __FILE_H
#define __FILE_H

#include <stdio.h>

/**
 * @brief 
 * 
 * @param file 
 * @return int 
 */
int FILE_getSize(FILE *file);

/**
 * @brief 
 * 
 * @param filename 
 * @param mode 
 * @param buffer 
 * @return int 
 */
int FILE_getFileContent(const char *filename, const char *mode, char **buffer);

/**
 * @brief 
 * 
 * @param filename 
 * @param mode 
 * @param buffer 
 * @return int 
 */
int FILE_write(const char *filename, const char *mode, const char *buffer);

/**
 * @brief 
 * 
 * @param filename 
 * @return FILE* 
 */
FILE *openWrite(const char *filename);

/**
 * @brief 
 * 
 * @param filename 
 * @return FILE* 
 */
FILE *openRead(const char *filename);

/**
 * @brief Get the File Size object
 * 
 * @param file 
 * @return size_t 
 */
size_t getFileSize(FILE *file);

#endif
