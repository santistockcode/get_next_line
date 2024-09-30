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
    int r_next_n; // position next \n
    int m_many; // how many allocations are there
} BufferInfo;


void	*ft_calloc(size_t count, size_t size);
char	*get_next_line(int fd);
void	ft_bzero(void *s, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
size_t	ft_strlen(const char *s);

#endif
