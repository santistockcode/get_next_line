# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "get_next_line_gpt.h"

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

void pprint(BufferInfo *info, char *buffer)
{
	printf("\n\n");
	printf("The buffer says	:");
	print_newline_helper(buffer);
	printf("\n");
	printf("Next n at pos	: %d\n", info->r_next_n);
	printf("Allocations	: %d\n", info->m_many);
}

int find_n(char *b_aux)
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
	return 0;
}

char *mmmove_bfff(char *bff)
{
	int counter_calloc; 

	ft_memmove(bff, bff + find_n(bff) + 1, ft_strlen(bff) - find_n(bff) - 1);
	
	counter_calloc = ft_strlen(bff) - find_n(bff) - 1;
	while (counter_calloc < ft_strlen(bff))
	{
		bff[counter_calloc] = '\0';
		counter_calloc++;
	}

	return (bff);
}

char *extract_line(char *from_this_bff)
{
	BufferInfo b_info;
	char *line;

	line = malloc(find_n(from_this_bff) + 1); 
	if (!line) {
		free (from_this_bff);
		return (free (line), NULL);
	}
	ft_memmove(line, from_this_bff, find_n(from_this_bff) + 1);
	return (line);
}

static char	*read_until_n(int fd, char *bff)
{
	int	bytes_read;
	char *line;
	BufferInfo b_info;
	char *b_aux;
	char *aux;


	b_aux = ft_calloc ( BUFFER_SIZE + 1, sizeof(char));
	if (b_aux == NULL)
		return (free (b_aux), NULL);
	b_aux = bff;
	if (b_aux)
		b_info.r_next_n = find_n(b_aux);

	b_info.m_many += 1;
	bytes_read = 1;

	while (b_info.r_next_n <= 0)
	{
		bytes_read = read(fd, b_aux + ft_strlen(b_aux), BUFFER_SIZE);
		if (bytes_read == 0)
			return (free (b_aux), NULL);
		aux = b_aux + ft_strlen(b_aux) - bytes_read;
		aux[ft_strlen(b_aux)] = '\0';
		b_info.r_next_n = find_n(b_aux);
		pprint(&b_info, b_aux);
	}

	return b_aux;
	
}

char *get_next_line(int fd)
{
	char *line;
	static char *j_bf = {0};
	
	if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    j_bf = read_until_n(fd, j_bf);
	if (!j_bf)
        return (NULL);
    line = extract_line(j_bf);
	j_bf = mmmove_bfff(j_bf);
	
	return (line);
}
