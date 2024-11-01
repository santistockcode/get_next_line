/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saalarco <saalarco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:34:09 by saalarco          #+#    #+#             */
/*   Updated: 2024/10/25 19:36:52 by saalarco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// ft_strchr
char	*ft_strchr(const char *s, int c)
{
	char	paso;

	if (*s == '\0' && c == '\0')
		return ((char *)s);
	paso = (char)c;
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

// ft_strjoin
char	*ft_strjoin(char const *str1, char const *str2)
{
	char	*r_join;
	int		i;

	i = 0;
	if (str1 == NULL && str2 == NULL)
		return (NULL);
	r_join = (char *)malloc((ft_strlen(str1) + ft_strlen(str2) + 1)
			* sizeof(char));
	if (r_join == NULL)
		return (NULL);
	if (str1)
	{
		while (*str1)
			r_join[i++] = *str1++;
	}
	while (*str2)
		r_join[i++] = *str2++;
	r_join[i] = '\0';
	return (r_join);
}

// ft_strlen
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

// ft_memmove
// TODO: nombres de variables mejores
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;
	size_t	i;

	s = (char *)src;
	d = (char *)dst;
	i = 0;
	if (d > s)
	{
		while (len > 0)
		{
			d[len - 1] = s[len - 1];
			len--;
		}
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}

// MEMESET + CALLOC
void	*ft_calloc(size_t count, size_t size)
{
	void	*result;
	size_t	i;
	char	*mem;

	result = malloc(count * size);
	if (result == NULL)
		return (NULL);
	mem = result;
	i = 0;
	while (i < count * size)
	{
		mem[i] = '\0';
		i++;
	}
	return (result);
}
