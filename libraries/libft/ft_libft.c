/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:09:57 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/08 15:41:38 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc2(size_t count, size_t size)
{
	char	*str;

	str = gc_malloc(count * size);
	if (!str)
		return (0);
	ft_bzero(str, count * size);
	return (str);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;

	str = gc_malloc(count * size);
	if (!str)
		return (0);
	ft_bzero(str, count * size);
	return (str);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		i;

	i = ft_strlen(s1);
	dup = (char *)gc_malloc((sizeof(char) * i + 1));
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
