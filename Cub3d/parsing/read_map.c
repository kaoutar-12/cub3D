/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:17:14 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/05 14:07:20 by mboukaiz         ###   ########.fr       */
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
		if (map[i] == 'N' || map[i] == 'S' || map[i] == 'W' || map[i] == 'E' || map[i] == 'P')
			j++;
		if (j > 1)
		{
			write(2, "Error\nMultiple players found in the map", 40);
			exit (1);
		}
		i++;
	}
	if (j == 0)
	{
		write(2, "Error\nNo player found in the map", 34);
		exit (1);
	}
}

void	check_map(char *map, int length)
{
	int i = 0;
	if (length < 9)
	{
		write(2, "Error\nInvalid map content\n", 13);
		exit (1);
	}
	while (map[i])
	{
		if (map[i] != '0' && map[i] != '1' && map[i] != 'P' && map[i] != 'N' && map[i] != 'S' && map[i] != 'W' && map[i] != 'E'
			&& map[i] != ' ' && map[i] != '\n')
		{
			write (2, "Error\nThe provided map contains an invalid character", 54);
			exit (1);
		}
		i++;
	}
	check_player (map);
}

char	*read_map(int fd, t_parse *vars)
{
	char	*map_vars;
	char	*map;
	char	*line;
	int		length;
	int		longest_line;

	longest_line = 0;
	map = ft_strdup("");
	map_vars = ft_strdup("");
	length = 0;
	line = get_next_line(fd);
	char *ptr;
	while (line)
	{
		ptr = ft_strtrim_fh(line, " \t\n");
		if (ptr[0])
		{
			if (length < 6)
			{
				ptr = ft_strtrim_fh(line, " \t");
				map_vars = ft_strjoin (map_vars, ptr);
			}
			else
			{
				map = ft_strjoin (map, line);
				if ((int)ft_strlen(line) > longest_line)
					longest_line = ft_strlen(line);
			}
			length++;
		}
		else if (line[0] == '\n' && length > 6)
		{
			write(2, "Invalid map content", 20);
			exit (1);
		}
		else if (line[0] != '\n' && !ptr[0])
		{
			write(2, "Invalid map content", 20);
			exit (1);
		}
		line = get_next_line(fd);
	}
	close(fd);
	check_map(map, length);
	vars->map = ft_split(map, '\n');
	set_map(vars->map, longest_line);
	set_map_size(vars, longest_line);
	return (map_vars);
}