#ifndef FT_PRINTF_H
# define FT_PRINTF_H
#define BUFFER_SIZE 5
#include <unistd.h>
#include <stdlib.h>
char    *get_next_line(int fd);
int ft_strlen(const char *str);
char    *ft_strjoin(char const *s1, char const *s2);
char    *ft_strchr(const char *s, int c);
char    *ft_substr(char const *s, unsigned int start, size_t len);
#endif