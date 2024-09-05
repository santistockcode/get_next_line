# include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero (ptr, count * size);
	return (ptr);
}


void	ft_bzero(void *s, size_t n)
{
	size_t			cntr;
	unsigned char	*pntr;

	cntr = 0;
	pntr = s;
	if (n <= 0)
		return ;
	while (cntr < n)
	{
		pntr[cntr] = 0;
		cntr++;
	}
}
