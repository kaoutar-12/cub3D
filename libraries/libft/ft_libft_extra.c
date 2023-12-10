/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:09:57 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/10 13:56:43 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s2 && s1)
		return (ft_strdup(s1));
	if (!s1 && !s2)
		return (NULL);
	res = gc_malloc((sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

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

char	**ft_split2(char *s, char c)
{
	int		i;
	char	**strs;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] == c)
		i++;
	strs = ft_calloc2(ft_count(NULL, s + i, c) + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	if (ft_count(strs, s + i, c) == -1)
	{
		i = 0;
		return (NULL);
	}
	return (strs);
}

char	**ft_split(char *s, char c)
{
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
