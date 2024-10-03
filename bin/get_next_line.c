# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "get_next_line.h"

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


void pprint(BufferInfo *info)
{
	printf("\n\n");
	printf("The buffer says	:");
	print_newline_helper(info->buffer);
	printf("\n");
	printf("Next n at pos	: %d\n", info->next_n);
	printf("Buffer length	: %d\n", info->buffer_len);
	printf("Allocations		: %d\n", info->chorri);

}

void find_n(BufferInfo *info)
{
	int n_pos = 0;
	while (n_pos < BUFFER_SIZE && ((*info).b_position)[n_pos] != '\n') {
    	n_pos++;
	}
	if ((info->b_position)[n_pos] == '\n')
		info->next_n = info->buffer_len - (BUFFER_SIZE - n_pos);
}


static char	*read_from_file(int fd)
{
	int	bytes_read;
	// static char	*s_buffer;
	static BufferInfo b_info;
	char *line;
	int counter_calloc; 
	char *read_position;

	b_info.next_n = 0;
	b_info.buffer_len = 0;

	
	read_position = ft_calloc ( BUFFER_SIZE + 1, sizeof(char));
	b_info.buffer = read_position;
	//b_info.b_position = b_info.buffer;
	//b_info.next_n = -1;
	b_info.chorri += 1;

	b_info.fdescriptor = fd;
	b_info.much_read = 0;
	
	//pprint(&b_info);


	if (b_info.buffer == NULL)
		return (NULL);
	if (b_info.buffer_len > 0)
		find_n(&b_info);
	while (b_info.next_n <= 0)
	{
		// problema 3: how is that RESERVO MEMORIA pero luego LE METO mazo de cosas prefiero hacer cambio de variable
		bytes_read = read(fd, b_info.buffer + b_info.buffer_len, BUFFER_SIZE);
		if (bytes_read == 0)
			return (free (b_info.buffer), NULL);
		b_info.buffer_len += bytes_read;
		b_info.b_position = b_info.buffer + b_info.buffer_len - bytes_read;
		b_info.buffer[b_info.buffer_len] = '\0';
		find_n(&b_info);
		pprint(&b_info);
	}
	// GREAT: i found some n

	// now take da line 
	// problema 4: ¿he llegado al EOF? ¿si el EOF está a 3 caracteres y next_n ni siquiera está qué hacemos?

	line = malloc(b_info.next_n + 1); 
	b_info.chorri += 1;
	if (!line) {
		free (b_info.buffer);
		return (free (line), NULL);
	}
	memmove(line, b_info.buffer, b_info.next_n + 1);

	// now reordenate the buffa
	memmove(b_info.buffer, b_info.b_position + 1, b_info.buffer_len - b_info.next_n - 1);
	
	// put 0 in all the rest of the bufffa
	counter_calloc = b_info.buffer_len - b_info.next_n - 1;
	while (counter_calloc < b_info.buffer_len)
	{
		b_info.buffer[counter_calloc] = '\0';
		counter_calloc++;
	}

	// new length of the buffer
	b_info.buffer_len -= (b_info.next_n + 1);
	
	// if I know everything about my_buffer can I manage it? (sacar una línea etc)

	// qué pasa con mi buffer si me pasan otro fd { BONUS }
	// qué pasa con mi buffer la segunda vez que se llama al read etc
	free(b_info.buffer);
	b_info.chorri -= 1;
	return (line);
}


char *get_next_line(int fd)
{
	char *line;
	line = read_from_file(fd);
	return (line);
}

// If you reach EOF without finding a \n, return the remaining data as the last line.
