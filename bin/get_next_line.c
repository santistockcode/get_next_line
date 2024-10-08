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

static char	*read_one_line(int fd, char *sttc)
{
	int	bytes_read;
	char *b_aux;
	//char *aux;
	size_t real_len;

	if (!sttc)
		sttc = ft_calloc ( BUFFER_SIZE + 1, sizeof(char));
	if (sttc == NULL)
		return (free (sttc), NULL);
	b_aux = sttc;
	bytes_read = 0;
	while (!ft_strchr(sttc, '\n'))
	{
		real_len = ft_strlen(sttc);
		// y si llego a 21 y el buffer es 21 y me devuelve 0 quiero esa línea
		bytes_read = read(fd, sttc + real_len, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free (sttc), NULL);
		sttc[real_len + bytes_read] = '\0';
		//aux = sttc + (int) ft_strlen(sttc) - bytes_read;
	//	aux[bytes_read] = '\0';
	}
	return b_aux;
}

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
	if (!buffers[fd])
        return (NULL);
    line = extract_line(buffers[fd]);
	buffers[fd] = move_bff(buffers[fd]);
	
	return (line);
}