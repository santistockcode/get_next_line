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
    char *buffer;     // Pointer to the buffer where data is read into
    ssize_t bytes_read;  // Number of bytes read by the read function
    int contains_null;  // Indicates if the buffer contains '\0'
    int contains_newline;  // Indicates if the buffer contains '\n'
    int read_successful;  // Indicates if the read operation was successful
    unsigned int next_nl;
    unsigned int buffer_len;
} ReadInfo;


void	*ft_calloc(size_t count, size_t size);
char	*get_next_line(int fd);
void	ft_bzero(void *s, size_t n);

#endif
