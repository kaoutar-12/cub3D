/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:46:13 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/10 13:50:21 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_chrstr(char *s, int c)
{
	int		i;
	char	find;

	find = (char)c;
	i = 0;
	if (!find)
		return (0);
	while (s[i])
	{
		if (s[i] == find)
			return (1);
		i++;
	}
	if (s[i] == find)
		return (1);
	return (0);
}

int	table_size(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
