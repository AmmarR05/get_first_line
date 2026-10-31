#include "get_next_line.h"
#include "stdio.h"
#include <fcntl.h>
int main()
{
  int fd = open("p.txt", O_RDONLY);
  char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}

}
