# include "get_next_line.h"

//ft_strchr			********************************************************************************
char	*ft_strchr(const char *s, int c)
{
	char	paso;

	if (*s == '\0' && c == '\0')
		return ((char *)s);
	paso = (char) c;
	while (*s != paso && *s)
	{
		s++;
	}
	if (*s == paso)
	{
		return ((char *)s);
	}
	else
	{
		return (NULL);
	}
}
//ft_strjoin		********************************************************************************
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	lens;
	size_t	count;

	lens = (size_t) ft_strlen(src);
	if (dstsize == 0)
		return (lens);
	count = 0;
	while (count + 1 < dstsize && *src)
	{
		*dst++ = *src++;
		count++;
	}
	if (*dst)
	{
		*dst = '\0';
	}
	
	return (lens);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char				*resstr;
	unsigned int		s1len;
	unsigned int		s2len;

	s1len = 0;
	s2len = 0;
	if (s1)
		s1len = ft_strlen(s1);
	if (s2)
		s2len = ft_strlen(s2);
	resstr = (char *)malloc((s1len + s2len + 1) * sizeof(char));
	if (resstr != NULL)
	{
		ft_strlcpy(resstr, s1, s1len + 1);
		ft_strlcat(resstr, s2, s1len + s2len + 1);
	}
	else
		return (NULL);
	return (resstr);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srcl;
	size_t	dstlen;
	size_t	count;

	dstlen = 0;
	if (dst)
		dstlen = ft_strlen (dst);
	srcl = ft_strlen (src);
	count = dstlen;
	if (dstsize <= dstlen)
		return (dstsize + srcl);
	while ((count < (dstsize - 1)) && (*src))
	{
		*(dst + count) = *src;
		count++;
		src++;
	}
	*(dst + count) = '\0';
	return (dstlen + srcl);
}
//ft_substr			********************************************************************************

//ft_strdup			********************************************************************************

// ft_strlen		********************************************************************************
size_t	ft_strlen(const char *s)
{
	size_t	c;

	c = 0;
	if (!s)
		return (0);
	while (*s++ != '\0')
		c++;
	return (c);
}

// ft_memmove		********************************************************************************
static void	move_right(unsigned char *b, unsigned char *o, size_t l)
{
	while (l > 0)
	{
		b[l - 1] = o[l - 1];
		l--;
	}
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

// MEMESET + CALLOC	********************************************************************************
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
// void	ft_bzero(void *s, size_t n)
// {
// 	ft_memset(s, '\0', n);
// }
void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = malloc(count * size);
	if (result == NULL)
		return (NULL);
	ft_memset(result, '\0', count * size);
	//ft_bzero(result, count * size);
	return (result);
}

