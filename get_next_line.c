# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "get_next_line.h"



//¿where is the valid data? 
//¿how long is the buffer?


void    print_newline_helper(char *buffer)
{

    while (*buffer &&  *buffer != '\0')
    {
        if (*buffer == '\n') 
        {
            *buffer= 'N';
        }
        printf("%c",*buffer);
        buffer++;
    }
}

// printf for da bufa
void pprint(BufferInfo *info)
{
	printf("\n\n");
	printf("The buffer says	:");
	print_newline_helper(info->buffer);
	printf("\n");
	printf("Next n at pos	: %d\n", info->next_n);
	printf("Buffer length	: %d\n", info->buffer_len);
}

void find_n(BufferInfo *info)
{
	int n_pos = 0;
	while (n_pos < BUFFER_SIZE && ((*info).b_position)[n_pos] != '\n') {
    	n_pos++;
	}
	if ((info->b_position)[n_pos] == '\n')
		info->next_n = info->buffer_len - (BUFFER_SIZE - n_pos);
	// problema 1: 0 es que el archivo empieza en \n? necesito -1
	// problema 2: resulta que esto va a un bloque infinito  
}


// void update_b_info(BufferInfo *info, char *buffer, unsigned int buffer_len) {
//     info->buffer = buffer;
//     info->bytes_read = 0;
//     info->read_successful = 0;
// 	info->buffer_len = buffer_len;
// 	find_n(buffer, &info);
// }



static char	*read_from_file(int fd)
{
	int	bytes_read;
	static char	*s_buffer;
	static int count = 1;
	BufferInfo b_info;
	char *line;
	int counter_calloc; 

	b_info.next_n = 0;
	b_info.buffer_len = 0;
	printf("ft_calloc[%d]---", count++);
	s_buffer = ft_calloc ( BUFFER_SIZE + 1, sizeof(char));
	if (s_buffer == NULL)
		return (NULL);
	b_info.buffer = s_buffer;
	if (b_info.buffer_len > 0)
		find_n(&b_info);
	while (b_info.next_n == 0)
	{
		// problema 3: si reservo memoria para una estática, hay que manejarla
		bytes_read = read(fd, s_buffer + b_info.buffer_len, BUFFER_SIZE);
		if (bytes_read == 0)
			return (free (s_buffer), NULL);
		b_info.buffer_len += bytes_read;
		b_info.b_position = b_info.buffer + b_info.buffer_len - bytes_read;
		s_buffer[b_info.buffer_len] = '\0';
		find_n(&b_info);
		pprint(&b_info);
	}
	// GREAT: i found some n

	// now take da line 
	// problema 4: ¿he llegado al EOF? ¿si el EOF está a 3 caracteres y next_n ni siquiera está qué hacemos? 
	line = malloc(b_info.next_n + 1); 
	if (!line) {
		free (s_buffer);
		return (free (line), NULL);
	}
	memmove(line, s_buffer, b_info.next_n + 1);

	// now reordenate the buffa
	memmove(s_buffer, b_info.b_position + 1, b_info.buffer_len - b_info.next_n - 1);
	
	// put 0 in all the rest of the bufffa
	counter_calloc = b_info.buffer_len - b_info.next_n - 1;
	while (counter_calloc < b_info.buffer_len)
	{
		s_buffer[counter_calloc] = '\0';
		counter_calloc++;
	}

	// new length of the buffer
	b_info.buffer_len -= (b_info.next_n + 1);
	
	// if I know everything about my_buffer can I manage it? (sacar una línea etc)

	// qué pasa con mi buffer si me pasan otro fd { BONUS }
	// qué pasa con mi buffer la segunda vez que se llama al read etc
	free(s_buffer);
	return (line);
}


char *get_next_line(int fd)
{
	char *line;
	line = read_from_file(fd);
	return (line);
}

// If you reach EOF without finding a \n, return the remaining data as the last line.
