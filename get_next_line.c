# include <unistd.h>
# include <stdio.h>
# include "get_next_line.h"


// TODO: Suddenly I was confused with on how many new line characters it counted. 1 or two? Anyway, I have this little helper function

// ESTRUCTURAS
static char	*read_from_file(int fd)
{
	int	bytes_read;
	char	*cup_buffer;
	static int count = 1;

	printf("ft_calloc[%d]---", count++);
	cup_buffer = ft_calloc ( BUFFER_SIZE + 1, sizeof(char));
	if (cup_buffer == NULL)
		return (NULL);
	bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		return (free (cup_buffer), NULL);
	}
	return (cup_buffer);
}


char *get_next_line(int fd)
{
	char *barrenio;

	barrenio = read_from_file(fd);
	return (barrenio);
}
