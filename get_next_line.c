#include "get_next_line.h"
char *get_next_line(int fd)
{
  if (BUFFER_SIZE <= 0 || fd < 0)
    return NULL;
 static char *temp;
 char *buffer = malloc(BUFFER_SIZE + 1);
 if (buffer == NULL)
  return NULL;
 int byte = read(fd,buffer,BUFFER_SIZE);
 if (byte == -1)
{
  free(buffer);
  return (NULL);
}
}
