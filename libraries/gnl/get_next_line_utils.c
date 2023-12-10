/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:51:17 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/10 15:04:20 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(1, (str + i++), 1);
	return (0);
}

size_t	ft_strlen_gnl(char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup_gnl(char *s1)
{
	char	*dup;
	int		i;

	if (!s1)
		return (NULL);
	i = ft_strlen_gnl(s1);
	dup = (char *)malloc((sizeof(char) * i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	if (!s1 && s2)
		return (ft_strdup_gnl(s2));
	if (!s2 && s1)
		return (ft_strdup_gnl(s1));
	if (!s1 && !s2)
		return (NULL);
	res = malloc((sizeof(char) * (ft_strlen_gnl(s1) + ft_strlen_gnl(s2)) + 1));
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
	free(s1);
	return (res);
}

char	*ft_strchr_gnl(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen_gnl(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}
