#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <stddef.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

void	*ft_calloc(size_t count, size_t size);
char	*get_next_line(int fd);
void	ft_bzero(void *s, size_t n);

#endif
