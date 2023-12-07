/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:09:57 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/05 14:08:18 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char **strs, char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		if (strs)
			strs[count] = ft_substr(s, 0, i);
		if (strs && strs[count] == NULL)
			return (-1);
		count++;
		while (s[i] && s[i] == c)
			i++;
		s = s + i;
		i = 0;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**strs;

	if (!s)
		return (NULL);
	while (*s && *s == c)
		s++;
	strs = ft_calloc(ft_count(NULL, s, c) + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	if (ft_count(strs, s, c) == -1)
	{
		i = 0;
		return (NULL);
	}
	return (strs);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*result;
	unsigned int	size;

	size = ft_strlen(s);
	if (!s)
		return (NULL);
	if (size < start)
		len = 0;
	if (size - start < len)
		len = size - start;
	result = (char *)gc_malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	result = ft_memmove(result, s + start, len);
	return (result);
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
