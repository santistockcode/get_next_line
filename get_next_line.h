#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <stddef.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
#include <stdbool.h>


typedef struct {
    char *b_position;
    char *buffer;     // Where's the buffer
    //size_t bytes_read;  // Number of bytes read by the read function
    int next_n;
    int buffer_len;
} BufferInfo;


void	*ft_calloc(size_t count, size_t size);
char	*get_next_line(int fd);
void	ft_bzero(void *s, size_t n);

#endif
