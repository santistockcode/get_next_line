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
    char *buffer;     
    int next_n;
    int buffer_len;
    int chorri;
    int fdescriptor;
    int much_read;
} BufferInfo;


void	*ft_calloc(size_t count, size_t size);
char	*get_next_line(int fd);
void	ft_bzero(void *s, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);

#endif
