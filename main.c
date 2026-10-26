#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd = open("p.txt",O_RDONLY);
    char *buf = malloc(BUFFER_SIZE + 1);
    int bytes = read(fd,buf,BUFFER_SIZE);
    int count = 0 ;
    while(bytes > 0)
    {
        buf[bytes] = '\0';
        write(1,&buf[count],1);
        count++;
        bytes--;
        bytes = read(fd,buf,BUFFER_SIZE);
    }
    free(buf);
    close(fd);
}
