/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:35:01 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/11/30 11:03:35 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_in_set(char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	a;
	size_t	z;
	char	*ptr;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	a = 0;
	z = ft_strlen(s1);
	while (is_in_set(s1[a], set))
		a++;
	while (is_in_set(s1[z - 1], set))
		z--;
	ptr = ft_substr(s1, a, z - a);
	return (ptr);
}

char	*ft_strtrim_fh(char const *s1, char const *set)
{
	int	i;
	int	j;

	if (s1 == NULL || set == NULL)
		return (0);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	if (!s1[i])
		return (ft_substr(s1, i, 0));
	// while (s1[j] && ft_strchr(set, s1[j]))
	// 	j--;
	// if (j == -1)
	// 	return (ft_substr(s1, i, 0));
	return (ft_substr(s1, i, (j - i + 1)));
}
