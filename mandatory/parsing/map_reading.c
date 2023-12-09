/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:17:14 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/08 18:01:54 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_direction(char c, t_parse *vars)
{
	if (c == 'N')
		vars->player_direction = NORTH;
	else if (c == 'S')
		vars->player_direction = SOUTH;
	else if (c == 'W')
		vars->player_direction = WEST;
	else if (c == 'E')
		vars->player_direction = EAST;
	else
	{
		write(2, "Error\nPlayer is nowhere to be found", 36);
		custom_exit(1);
	}
}

void	find_player(t_parse *vars)
{
	t_it	it;

	it.i = 0;
	it.j = 0;
	while (vars->map[it.i])
	{
		it.j = 0;
		while (vars->map[it.i][it.j])
		{
			if (vars->map[it.i][it.j] == 'N'
			|| vars->map[it.i][it.j] == 'S'
			|| vars->map[it.i][it.j] == 'W'
			|| vars->map[it.i][it.j] == 'E')
			{
				vars->player_x = it.i;
				vars->player_y = it.j;
				set_direction(vars->map[it.i][it.j], vars);
			}
			it.j++;
		}
		it.i++;
	}
}

char	*join_map(char *map, char *line)
{
	char	*str;

	if (!map)
	{
		map = ft_strdup(line);
		return (map);
	}
	else
		str = ft_strjoin_gnl(map, line);
	return (str);
}

char	*read_map(int fd, t_parse *vars)
{
	char	*map_vars;
	char	*map;
	char	*line;
	int		length;
	int		longest_line;
	char	*ptr;

	length = 0;
	longest_line = 0;
	map = ft_strdup("");
	map_vars = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		ptr = ft_strtrim_fh(line, " \t\n");
		if (ptr[0])
		{
			if (length < 6)
			{
				ptr = ft_strtrim_fh(line, " \t");
				map_vars = ft_strjoin(map_vars, ptr);
			}
			else
			{
				map = ft_strjoin(map, line);
				if ((int)ft_strlen(line) > longest_line)
					longest_line = ft_strlen(line);
			}
			length++;
		}
		else if (line[0] == '\n' && length > 6)
		{
			write(2, "Error\nInvalid map content\n", 27);
			close(fd);
			custom_exit(1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	check_map(map, length);
	vars->map = ft_split(map, '\n');
	vars->actual_map = ft_split(map, '\n');
	set_map(vars, longest_line);
	set_map_size(vars, longest_line);
	find_player(vars);
	return (map_vars);
}

int	table_size(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
