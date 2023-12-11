/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:17:14 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/10 15:06:50 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	invalid_map(int fd)
{
	write(2, "Error\nInvalid map content\n", 27);
	close(fd);
	custom_exit(1);
}

int	map_fill(int fd, char **map, char **map_vars, int *longest_line)
{
	char	*line;
	int		length;

	length = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strlen(ft_strtrim_fh(line, " \t\n")) > 0)
		{
			if (length < 6)
				*map_vars = ft_strjoin(*map_vars, ft_strtrim_fh(line, " \t"));
			else
			{
				*map = ft_strjoin(*map, line);
				if ((int)ft_strlen(line) > *longest_line)
					*longest_line = ft_strlen(line);
			}
			length++;
		}
		else if (line[0] == '\n' && length > 6)
			invalid_map(fd);
		free(line);
		line = get_next_line(fd);
	}
	return (length);
}

char	*read_map(int fd, t_parse *vars)
{
	char	*map_vars;
	char	*map;
	int		length;
	int		longest_line;

	longest_line = 0;
	map = ft_strdup("");
	map_vars = ft_strdup("");
	length = map_fill(fd, &map, &map_vars, &longest_line);
	close(fd);
	check_map(map, length);
	vars->map = ft_split(map, '\n');
	vars->actual_map = gc_malloc(sizeof(char *) * table_size(vars->map) + 1);
	set_map(vars, longest_line);
	set_map_size(vars, longest_line);
	find_player(vars);
	return (map_vars);
}
