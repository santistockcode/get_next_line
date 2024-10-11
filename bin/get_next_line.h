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

#   define MAX_FDS 1024 // chequear si esto es así

void	*ft_calloc(size_t count, size_t size);
char	*get_next_line(int fd);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);


#endif
