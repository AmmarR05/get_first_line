#include "get_next_line.h"
char *get_next_line(int fd)
{
  if (BUFFER_SIZE <= 0 || fd < 0)
    return NULL;
  static char *temp;
  char  *old;
  char  *str;
  int i = 0;
  char *buffer = malloc(BUFFER_SIZE + 1);
  if (buffer == NULL)
    return NULL;
 int byte = read(fd,buffer,BUFFER_SIZE);
 if (byte == -1)
  {
    free(buffer);
    return (NULL);
  }
  buffer[byte] = '\0';
  while(byte > 0)
  {
    old = temp;
    temp = ft_strjoin(old, buffer);
    free(old);
    if(ft_strchr(temp ,'\n') != NULL)
      break;
    byte = read(fd,buffer,BUFFER_SIZE);
    if(byte != -1)
      buffer[byte] = '\0'; 
  }
  if (temp == NULL || temp[0] == '\0')
  {
    free(buffer);
    return (NULL);
  } 
  while(temp[i])
  {
    if(temp[i] == '\n')
  {
      i++;
      break;
  }
    i++;
  }
  str = malloc(i + 1);
  if(str == NULL)
  {
    free(buffer);
    return NULL;
  }
  str[i] = '\0';
  int len = i;
  while (i > 0)
  {
    i--;
    str[i] = temp[i];    
  }
  old = temp;
  if(temp != NULL)
      temp = ft_substr(old,len,ft_strlen(old) - len);
  free(old);
  if (temp != NULL && temp[0] == '\0')
  {
    free(temp);
    temp = NULL;
  }
  free(buffer);
  return str;
} 
// ammarrida\n