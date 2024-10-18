# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "get_next_line.h"

int strlen_n(char *b_aux) // isn't this just strchr + int return
{
	char *aux;
	int n_pos;

	n_pos = 0;
	aux = b_aux;
	while ((aux[n_pos] != '\n')) {
    	n_pos++;
	}
	if (aux[n_pos] == '\n')
		return n_pos;
	return (-1);
}

// char *move_bff(char *bff)
// {
// 	int counter_calloc; 

// 	ft_memmove(bff, bff + n_position(bff) + 1, ft_strlen(bff) - n_position(bff) - 1);
	
// 	counter_calloc = ft_strlen(bff) - n_position(bff) - 1;
// 	while (counter_calloc < (int) ft_strlen(bff))
// 	{
// 		bff[counter_calloc] = '\0';
// 		counter_calloc++;
// 	}

// 	return (bff);
// }

/*
This function evaluates if buffer has '\n' or doesn't. 
Then act based on that info.
*/

// char *move_bff(char *bff)
// {
// 	int counter_calloc;
// 	int bff_length;
	
// 	bff_length = ft_strlen(bff);
// 	if (ft_strchr(bff, '\n'))
// 	{
// 		ft_memmove(bff, ft_strchr(bff, '\n') + 1, ft_strlen(bff) - ft_strlen(ft_strchr(bff, '\n')) - 1);
// 		counter_calloc = ft_strlen(bff) - ft_strlen(ft_strchr(bff, '\n'));
// 	}
// 	else 
// 	{
// 		counter_calloc = 0;
// 	}
// 	while (counter_calloc < (int) bff_length)
// 	{
// 		bff[counter_calloc] = '\0';
// 		counter_calloc++;
// 	}

// 	return (bff);

// }

char *update_buffer(char *bff)
{
	int fin_bff_length;
	// char *return_buffer;


	if (ft_strchr(bff, '\n'))
	{
		fin_bff_length = ft_strlen(ft_strchr(bff, '\n'));
		ft_memmove(bff, ft_strchr(bff, '\n') + 1, fin_bff_length);
		bff[fin_bff_length] = 0;
	}
	else
	{
		*bff = 0;
	}

	return (bff);
}
	

/*
This functions evaluates if buffer is empty, has '\n' or doesn't and
move a line based on those evalutaions
*/

// TODO: asegurarme de que devuelve NULL en caso de error


char *extract_line(char *buffer)
{
	char *line;
	

	if (!buffer)
	{
		return (NULL);
	}
	if (ft_strchr(buffer, '\n'))
	{
		line = malloc(strlen_n(buffer) + 2);
		if (!line) {
			free (buffer);
			return (free (line), NULL);
		}
		ft_memmove(line, buffer, strlen_n(buffer) + 1);
		line[strlen_n(buffer) + 1] = 0;
	}
	else
	{
		line = malloc(ft_strlen(buffer) + 1);
		ft_memmove(line, buffer, ft_strlen(buffer) + 1);
	}
	return (line);

}

// char *extract_line(char *bfr)
// {
// 	char *line;
// 	char *classy;
// 	int flag;

// 	line = malloc(ft_strlen(ft_strchr(bfr, '\n')) + 1);
// 	flag = 0;
// 	if (!line)
// 	{
// 		bfr = NULL;
// 		free (bfr);
// 		return (free (line), NULL);
// 	}
// 	if (ft_strchr(bfr, '\n'))
// 	{
// 		classy = ft_strchr(bfr, '\n');
// 		*classy = '\0';
// 		flag = 1;
// 	}
// 	ft_memmove(line, bfr, ft_strlen(bfr) + 1);
	
// 	if (flag)
// 	{
// 		line[ft_strlen(bfr)] = '\n';
// 		*classy = '\n';
// 	}
// 	return (line);
// }

// void initialize_b_info(BufferInfo *b_info)
// {
// 	b_info->r_next_n = -1;
// 	b_info->m_many = 0;
// }

/*
This function checks if static is already
allocated and allocates memory if not. Then reads
again and again from fd into that static variable 
until finding n character. Then returns a pointer 
to the start of the static variable.  
Returns NULL in case of error
*/

// TODO: resulta que vuelve a leer aunque ya había un '\n' ¿is this my problem?
// TODO: asegurarme de que devuelve NULL en caso de error
// TODO: p[0] = '\0' tiene sentido tras un calloc?

static char	*read_one_line(int fd, char *left)
{
	int	bytes_read;
	char *p;
	char *temp;

	p = ft_calloc ( BUFFER_SIZE + 1, sizeof(char));
	if (!p)
		return (free (p), NULL);
	//p[0] = '\0';
	bytes_read = BUFFER_SIZE;
	while (!ft_strchr(p, '\n')&& bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, p, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free (p), NULL);
		p[bytes_read] = 0;
		temp = ft_strjoin(left, p);
		free(left);
		left = temp;
	}
	free(p);
	p = NULL;
	return temp;
}


/*
This get_next_line function reads the next line from a given file descriptor fd. 
It maintains a static array buffers to keep track of residual data for each file descriptor, 
allowing it to handle multiple file descriptors simultaneously.
*/

char *get_next_line(int fd)
{
	char *line;
	static char *buffers[MAX_FDS];
	
	if (fd < 0 || fd >= MAX_FDS || BUFFER_SIZE <= 0)
        return (NULL);
    buffers[fd] = read_one_line(fd, buffers[fd]);
	if (!(buffers[fd]) || *(buffers[fd]) == '\0')
	{
		free(buffers[fd]);
		buffers[fd] = NULL;
        return (NULL);
	}
    line = extract_line(buffers[fd]);
	if (!line || *line == '\0')
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	else
		buffers[fd] = update_buffer(buffers[fd]);
	
	return (line);
}
