/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saalarco <saalarco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:29:53 by saalarco          #+#    #+#             */
/*   Updated: 2024/10/25 19:51:11 by saalarco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// TODO: puedo explicar ese retorno de -1? qué pasa si lo quito y devuelvo 0?

int	strlen_n(char *b_aux)
{
	char	*aux;
	int		n_pos;

	n_pos = 0;
	aux = b_aux;
	while ((aux[n_pos] != '\n'))
	{
		n_pos++;
	}
	if (aux[n_pos] == '\n')
		return (n_pos);
	return (-1);
}

/*
This function evaluates if buffer has '\n' or doesn't.
Then act based on that info.
*/
// TODO: tiene más sentido return NULL? ¿por qué igualo *bff a 0?

char	*update_buffer(char *bff)
{
	int	fin_bff_length;

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

char	*extract_line(char *buffer)
{
	char	*line;

	if (!buffer)
	{
		return (NULL);
	}
	if (ft_strchr(buffer, '\n'))
	{
		line = malloc(strlen_n(buffer) + 2);
		if (!line)
		{
			free(buffer);
			return (free(line), NULL);
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

static char	*read_one_line(int fd, char *left)
{
	int		bytes_read;
	char	*p;
	char	*temp;

	p = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!p)
		return (free (p), NULL);
	bytes_read = BUFFER_SIZE;
	while (!ft_strchr(p, '\n') && bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, p, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(p);
			free(left);
			return (NULL);
		}
		p[bytes_read] = 0;
		temp = ft_strjoin(left, p);
		free(left);
		left = temp;
	}
	free(p);
	p = NULL;
	return (temp);
}

/*
This get_next_line function reads the next line from a given file descriptor fd.
It maintains a static array buffers to keep track of residual 
data for each file descriptor, allowing it to handle 
multiple file descriptors simultaneously.
*/

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffers[MAX_FDS];

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
