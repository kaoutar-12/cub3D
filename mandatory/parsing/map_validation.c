/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:50:16 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/10 12:17:45 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_player(char *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		if (map[i] == 'N' || map[i] == 'S' || map[i] == 'W' || map[i] == 'E')
			j++;
		if (j > 1)
		{
			write(2, "Error\nMultiple players found in the map", 40);
			custom_exit(1);
		}
		i++;
	}
	if (j == 0)
	{
		write(2, "Error\nNo player found in the map\n", 34);
		custom_exit(1);
	}
}

int	check_map2(t_parse *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (vars->actual_map[i])
	{
		j = 0;
		while (vars->actual_map[i][j])
		{
			if (!is_surrounded(vars, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	check_map(char *map, int length)
{
	int	i;

	i = 0;
	if (length < 9)
	{
		write(2, "Error\nInvalid map content\n", 27);
		custom_exit(1);
	}
	while (map[i])
	{
		if (map[i] != '0' && map[i] != '1'
			&& map[i] != 'N' && map[i] != 'S'
			&& map[i] != 'W' && map[i] != 'E'
			&& map[i] != ' ' && map[i] != '\n')
		{
			write (2, "Error\nThe provided map "
				"contains an invalid character\n", 54);
			custom_exit(1);
		}
		i++;
	}
	check_player (map);
}
