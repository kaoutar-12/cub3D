/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:01:31 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/08 15:41:06 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	find;

	find = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == find)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == find)
		return ((char *)s + i);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*destination;
	unsigned char	*source;
	int				i;

	i = 0;
	destination = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (!src && !dst)
		return (NULL);
	while (n--)
	{
		destination[i] = source[i];
		i++;
	}
	return ((void *)dst);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*destination;
	char	*source;

	destination = (char *)dest;
	source = (char *)src;
	if (!src && !dest)
	{
		return (NULL);
	}
	if (destination >= source)
	{
		while (len)
		{
			len--;
			destination[len] = source[len];
		}
	}
	else
		ft_memcpy(destination, source, len);
	return ((void *)destination);
}
