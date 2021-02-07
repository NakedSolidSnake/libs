#ifndef __FILE_H
#define __FILE_H

#include <stdio.h>

int FILE_getSize(FILE *file);
int FILE_getFileContent(const char *filename, const char *mode, char **buffer);
int FILE_write(const char *filename, const char *mode, const char *buffer);

FILE *openWrite(const char *filename);
FILE *openRead(const char *filename);
size_t getFileSize(FILE *file);

#endif
