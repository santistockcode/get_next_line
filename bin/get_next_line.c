# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "get_next_line.h"


//PRINT FUNCTIONS 	********************************************************************************
// void    print_newline_helper(char *buffer)
// {
//     while (*buffer &&  *buffer != '\0')
//     {
//         if (*buffer == '\n') 
//         {
//             *buffer= 'N';
//         }
//         printf("%c",*buffer);
//         buffer++;
//     }
// }
void pprint(int r_next_n, char *buffer)
{
	printf("\n");
	printf("BUFFER	: %s \n", buffer);
	//print_newline_helper(buffer);
	printf("\n");
	printf("Next n at pos	: %d\n", r_next_n);
}

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

char *move_bff(char *bff)
{
	int counter_calloc;
	int bff_length;
	
	bff_length = ft_strlen(bff);
	if (ft_strchr(bff, '\n'))
	{
		ft_memmove(bff, ft_strchr(bff, '\n') + 1, ft_strlen(bff) - ft_strlen(ft_strchr(bff, '\n')) - 1);
		counter_calloc = ft_strlen(bff) - ft_strlen(ft_strchr(bff, '\n'));
	}
	else 
	{
		counter_calloc = 0;
	}
	while (counter_calloc < (int) bff_length)
	{
		bff[counter_calloc] = '\0';
		counter_calloc++;
	}

	return (bff);

}


// char *extract_line(char *from_this_bff)
// {
// 	char *line;

// 	line = malloc(n_position(from_this_bff) + 1); 
// 	if (!line) {
// 		free (from_this_bff);
// 		return (free (line), NULL);
// 	}
// 	ft_memmove(line, from_this_bff, n_position(from_this_bff) + 1);
// 	return (line);
// }

/*
This functions evaluates if buffer is empty, has '\n' or doesn't and
move a line based on those evalutaions
*/

char *extract_line(char *buffer)
{
	char *line;
	

	if (!buffer)
	{
		return (NULL);
	}
	if (ft_strchr(buffer, '\n'))
	{
		line = malloc(strlen_n(buffer) + 1);
		if (!line) {
			free (buffer);
			return (free (line), NULL);
		}
		ft_memmove(line, buffer, strlen_n(buffer) + 1);
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
*/

static char	*read_one_line(int fd, char *sttc)
{
	int	bytes_read;
	char *p;
	size_t real_len;

	// TODO: 
	if (!sttc)
		sttc = ft_calloc ( BUFFER_SIZE + 1, sizeof(char));
	if (sttc == NULL)
		return (free (sttc), NULL);
	p = sttc;
	bytes_read = BUFFER_SIZE;
	while (!ft_strchr(sttc, '\n')&& bytes_read == BUFFER_SIZE)
	{
		real_len = ft_strlen(sttc);
		bytes_read = read(fd, sttc + real_len, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free (sttc), NULL);
		sttc[real_len + bytes_read] = '\0';
	}
	return p;
}

// v2
// static char	*read_one_line(int fd, char *sttc)
// {
// 	int	bytes_read;
// 	//char *p;
// 	size_t real_len;
// 	char temp[BUFFER_SIZE];
// 	int total_b;

// 	// TODO: 
// 	temp[0] = '\0';
// 	total_b = 0;
// 	bytes_read = BUFFER_SIZE;
// 	while (!ft_strchr(temp, '\n')&& bytes_read == BUFFER_SIZE)
// 	{
// 		real_len = ft_strlen(temp);
// 		bytes_read = read(fd, temp + real_len, BUFFER_SIZE);
// 		if (bytes_read < 0)
// 			return (free (sttc), NULL);
// 		temp[real_len + bytes_read] = '\0';
// 		total_b += bytes_read;
// 	}
// 	if (!sttc)
// 		sttc = ft_calloc ( total_b + 1, sizeof(char));
// 	ft_memmove(sttc, temp, total_b);
// 	if (sttc == NULL)
// 		return (free (sttc), NULL);
// 	return sttc;
// }

/*
This function does...
*/

char *get_next_line(int fd)
{
	char *line;
	static char *buffers[MAX_FDS];
	// need da info of the read -> BETTER NAMING FUNCTIONS, not read_until_n but read_line
	// TODO: no pillo como puede haber múltiples fd's
	
	if (fd < 0 || fd >= MAX_FDS || BUFFER_SIZE <= 0)
        return (NULL);
    buffers[fd] = read_one_line(fd, buffers[fd]);
	if (*(buffers[fd]) == '\0')
	{
		free(buffers[fd]);
        return (NULL);
	}
    line = extract_line(buffers[fd]);
	if (*line == '\0')
	{
		free(line);
		return (NULL);
	}
	
	// if (!ft_strchr(line, '\n'))
	// {
	// 	buffers[fd] = NULL;
	// 	free(buffers[fd]);
	// }
	else
		buffers[fd] = move_bff(buffers[fd]);
	
	return (line);
}