#include <stdlib.h>
#include <string.h>
#include <file/file.h>

int FILE_getSize(FILE *file)
{
  size_t len = 0;
  if(!file)
    return -1;
  fseek(file, 0, SEEK_END);
  len = ftell(file);
  rewind(file);
  return len;
}

int FILE_getFileContent(const char *filename, const char *mode, char **buffer)
{
  FILE *file = fopen(filename, mode);
  if(file == NULL)
    return -1;

  size_t size = FILE_getSize(file);

  *buffer = (char *)malloc(sizeof(char) * size + 1);
  memset(*buffer, 0, size + 1);
  fread(*buffer, 1, size, file);
  fclose(file);
  return 0;
}

int FILE_write(const char *filename, const char *mode, const char *buffer)
{
  return -1;
}

FILE *openWrite(const char *filename)
{
  FILE *fd = fopen(filename, "w");
  return fd;
}

FILE *openRead(const char *filename)
{
  FILE *fd = fopen(filename, "r");
  return fd;
}

size_t getFileSize(FILE *file)
{
  size_t len = 0;
  if(!file)
    return -1;
  fseek(file, 0, SEEK_END);
  len = ftell(file);
  rewind(file);
  return len;
}
