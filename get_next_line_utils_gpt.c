# include "get_next_line_gpt.h"

static void	move_right(unsigned char *b, unsigned char *o, size_t l)
{
	while (l > 0)
	{
		b[l - 1] = o[l - 1];
		l--;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	c;

	c = 0;
	while (*s++ != '\0')
		c++;
	return (c);
}


void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*bufer;
	unsigned char	*origen;
	int				c;

	bufer = (unsigned char *) dst;
	origen = (unsigned char *) src;
	c = 0;
	if (!dst && !src)
		return (0);
	if (dst <= src)
	{
		while (c < (int) len)
		{
			bufer[c] = origen[c];
			c++;
		}
	}
	else if (dst > src)
	{
		move_right(bufer, origen, len);
	}
	return (dst);
}

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
