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

int n_position(char *b_aux) // isn't this just strchr + int return
{
	char *aux;
	int n_pos;

	n_pos = 0;
	aux = b_aux;
	while (n_pos < BUFFER_SIZE && (aux[n_pos] != '\n')) {
    	n_pos++;
	}
	if (aux[n_pos] == '\n')
		return ft_strlen(b_aux) - (BUFFER_SIZE - n_pos);
	return (-1);
}

char *move_bff(char *bff)
{
	int counter_calloc; 

	ft_memmove(bff, bff + n_position(bff) + 1, ft_strlen(bff) - n_position(bff) - 1);
	
	counter_calloc = ft_strlen(bff) - n_position(bff) - 1;
	while (counter_calloc < (int) ft_strlen(bff))
	{
		bff[counter_calloc] = '\0';
		counter_calloc++;
	}

	return (bff);
}

char *extract_line(char *from_this_bff)
{
	char *line;

	line = malloc(n_position(from_this_bff) + 1); 
	if (!line) {
		free (from_this_bff);
		return (free (line), NULL);
	}
	ft_memmove(line, from_this_bff, n_position(from_this_bff) + 1);
	return (line);
}

// void initialize_b_info(BufferInfo *b_info)
// {
// 	b_info->r_next_n = -1;
// 	b_info->m_many = 0;
// }

static char	*read_until_n(int fd, char *bff)
{
	int	bytes_read;
	//BufferInfo b_info;
	int 	r_next_n;
	char 	*paso;
	char *b_aux;
	char *aux;

	//si no existe laa estática, la reservo
	r_next_n = -1;
	if (!bff)
		paso = ft_calloc ( BUFFER_SIZE + 1, sizeof(char));
	if (paso == NULL)
		return (free (paso), NULL);
	b_aux = paso;
	if (*b_aux)
		r_next_n = n_position(b_aux);

	//b_info.m_many += 1;
	bytes_read = 0;
	
	while (r_next_n <= 0)
	{
		bytes_read = read(fd, b_aux + ft_strlen(b_aux), BUFFER_SIZE);
		if (bytes_read <= 0)
			return (free (b_aux), NULL);
		aux = b_aux + (int) ft_strlen(b_aux) - bytes_read;
		aux[ft_strlen(b_aux)] = '\0';
		r_next_n = n_position(b_aux);
		// pprint(r_next_n, b_aux);
	}
	
	paso = bff;
	free(paso);

	return b_aux;
	
}

/*
This function does...
*/

char *get_next_line(int fd)
{
	char *line;
	static char *j_bf;
	// need da info of the read -> BETTER NAMING FUNCTIONS, not read_until_n but read_line
	// TODO: no pillo como puede haber múltiples fd's
	
	if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    j_bf = read_until_n(fd, j_bf);
	if (!j_bf)
        return (NULL);
    line = extract_line(j_bf);
	j_bf = move_bff(j_bf);
	
	return (line);
}