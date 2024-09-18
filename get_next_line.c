# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "get_next_line.h"



//¿where is the valid data? 
//¿how long is the buffer?


// printf for da bufa
void super_printer(ReadInfo *info)
{
	printf("Bytes read: %ld\n", info->bytes_read);
    printf("Contains null: %d\n", info->contains_null);
    // printf("Contains newline: %d\n", (info->contains_newline != 0) ? "Yes" : "No");
	printf("Contains newline: %d\n", info->contains_newline);
	printf("The buffer says: %s\n", info->buffer);
	printf("The buffer length: %u\n", info->buffer_len);
	printf("The next barraene: %d\n", info->next_nl);
}

unsigned int custom_strchr(char *buffer, unsigned int buffer_len)
{
	unsigned int newline_pos = 0;
	while (newline_pos < buffer_len && buffer[newline_pos] != '\n') {
    	newline_pos++;
	}

	return newline_pos;
	// problema 1: 0 es que el archivo empieza en \n? necesito -1
	// problema 2: resulta que esto va a un bloque infinito  
}


void init_read_info(ReadInfo *info, char *buffer, unsigned int buffer_len) {
    info->buffer = buffer;
    info->bytes_read = 0;
    info->contains_null = 0;
    info->contains_newline = 0;
    info->read_successful = 0;
	info->buffer_len = buffer_len;
	info->next_nl = custom_strchr(buffer, info->buffer_len);
}

void analyze_buffer(ReadInfo *info) {
    // Check for special characters in the buffer
    for (size_t i = 0; i < info->bytes_read; i++) {
        if (info->buffer[i] == '\0') {
            info->contains_null += 1;
        }
        if (info->buffer[i] == '\n') {
            info->contains_newline += 1;
        }
    }
}

static char	*read_from_file(int fd)
{
	int	bytes_read;
	static char	*cup_buffer;
	static int count = 1;
	ReadInfo read_info;
	char *line;
	unsigned int buffer_len;

	buffer_len = 0;
	init_read_info(&read_info, cup_buffer, 0);
	while (read_info.next_nl == 0)
	{
		cup_buffer = ft_calloc ( BUFFER_SIZE + 1, sizeof(char));
		if (cup_buffer == NULL)
			return (NULL);
		// problema 3: si reservo memoria para una estática, hay que manejarla
		bytes_read = read(fd, cup_buffer + read_info.buffer_len, BUFFER_SIZE);
		if (bytes_read == 0)
			return (free (cup_buffer), NULL);
		read_info.buffer_len += bytes_read;
		init_read_info(&read_info, cup_buffer, buffer_len);
	}
	printf("ft_calloc[%d]---", count++);
	cup_buffer = ft_calloc ( BUFFER_SIZE + 1, sizeof(char));
	if (cup_buffer == NULL)
		return (NULL);
	bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
	cup_buffer[BUFFER_SIZE] = '\0';  // Null-terminate the buffer
	read_info.buffer = cup_buffer;
	read_info.bytes_read = bytes_read;
	read_info.read_successful = 1;
	

    // Analyze the buffer content
    analyze_buffer(&read_info);
	if (bytes_read <= 0)
	{
		return (free (cup_buffer), NULL);
	}

	// if I know everything about my_buffer can I manage it? (sacar una línea etc)

	// qué pasa con mi buffer si me pasan otro fd { BONUS }

	super_printer(&read_info);
	
	return (cup_buffer);
}


char *get_next_line(int fd)
{
	char *barrenio;

	barrenio = read_from_file(fd);
	return (barrenio);
}

// If you reach EOF without finding a \n, return the remaining data as the last line.
