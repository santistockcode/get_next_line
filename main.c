#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>


// TODO: 

int main(void)
{
  int    fd;
  char  *next_line;
  int  count;

    count = 0;
    fd = open("example.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening da thing");
        return (1);
    }
    while (1)
    {
        next_line = get_next_line(fd);
        if (next_line == NULL)
            break ;
        count++;
        printf("[%d]:%s\n\n", count, next_line); 
        free(next_line);
        next_line = NULL;
    }
    close(fd);
    return (0);
}
