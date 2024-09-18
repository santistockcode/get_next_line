# include "get_next_line.h"

// void	*ft_calloc(size_t count, size_t size)
// {
// 	unsigned char	*ptr;

// 	ptr = malloc(count * size);
// 	if (ptr == NULL)
// 		return (NULL);
// 	ft_bzero (ptr, count * size);
// 	return (ptr);
// }


// void	ft_bzero(void *s, size_t n)
// {
// 	size_t			cntr;
// 	unsigned char	*pntr;

// 	cntr = 0;
// 	pntr = s;
// 	if (n <= 0)
// 		return ;
// 	while (cntr < n)
// 	{
// 		pntr[cntr] = 0;
// 		cntr++;
// 	}
// }
void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*mem;

	mem = b;
	i = 0;
	while (i < len)
	{
		mem[i] = (char) c;
		i++;
	}
	return (b);
}
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = malloc(count * size);
	if (result == NULL)
		return (NULL);
	ft_bzero(result, count * size);
	return (result);
}

// strchr

// strcpy

// memmove

// strlen without \0? quizas el read ya se ocupa de eso.
