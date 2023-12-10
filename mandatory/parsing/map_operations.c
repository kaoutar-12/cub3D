/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:02:20 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/08 18:14:31 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	surround_map(char **a_map, char **map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map[i])
	{
		a_map[i] = ft_strdup(map[i]);
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				map[i][j] = '1';
			j++;
		}
		i++;
	}
	a_map[i] = NULL;
}

void	set_map(t_parse *vars, int longest)
{
	int		i;
	char	*tmp;

	i = 0;
	while (vars->map[i])
	{
		tmp = allocate_space(longest - 1);
		ft_strcpy(tmp, vars->map[i]);
		vars->map[i] = tmp;
		i++;
	}
	printf ("%d\n", longest);
	surround_map(vars->actual_map, vars->map);
}

void	set_map_size(t_parse *vars, int y)
{
	int	x;

	x = 0;
	while (vars->map[x])
	{
		x++;
	}
	vars->map_h = x;
	vars->map_w = y;
}

int	ft_my_atoi(char *color)
{
	t_it	it;

	it.i = 0;
	while (color[it.i])
	{
		if (color[it.i] == '+')
			it.i++;
		if (!ft_isdigit(color[it.i]))
		{
			write(2, "Error:\nMap content must be in the format"
				"\"ddd, ddd, ddd,\" with each 'ddd' between 0 and 255\n", 92);
			custom_exit(1);
		}
		it.i++;
	}
	return (ft_atoi (color));
}

void	map_operations(char *map_name, t_parse *vars)
{
	int		fd;
	char	*arr;

	fd = open (map_name, O_RDONLY);
	if (ft_strcmp(map_name + strlen(map_name) - 4, ".cub"))
	{
		close (fd);
		write(2, "Error\nInvalid map extention\n", 29);
		custom_exit(1);
	}
	if (fd == -1)
	{
		perror("Error\nCub3d");
		custom_exit(1);
	}
	arr = read_map(fd, vars);
	set_data(vars, arr);
	if (!check_map2(vars))
	{
		write(2, "Error\nMap is not valid\n", 24);
		custom_exit(1);
	}
	printf("vars->a_map\n");
	for (int i = 0; vars->actual_map[i]; i++)
		printf("|%s|\n", vars->actual_map[i]);
	printf("vars->map\n");
	for (int i = 0; vars->map[i]; i++)
		printf("|%s|\n", vars->map[i]);

	printf("vars->c_rgb.red\n");
	printf("|%d|\n", vars->c_rgb.red);
	printf("vars->c_rgb.green\n");
	printf("|%d|\n", vars->c_rgb.green);
	printf("vars->c_rgb.blue\n");
	printf("|%d|\n", vars->c_rgb.blue);
	
	printf("vars->f_rgb.red\n");
	printf("|%d|\n", vars->f_rgb.red);
	printf("vars->f_rgb.green\n");
	printf("|%d|\n", vars->f_rgb.green);
	printf("vars->f_rgb.blue\n");
	printf("|%d|\n", vars->f_rgb.blue);

	printf("vars->ea\n");
	printf("|%s|\n", vars->ea);
	printf("vars->we\n");
	printf("|%s|\n", vars->we);
	printf("vars->so\n");
	printf("|%s|\n", vars->so);
	printf("vars->no\n");
	printf("|%s|\n", vars->no);

	printf("x |%d|\n", vars->player_x);
	printf("y |%d|\n", vars->player_y);

	printf("h |%d|\n", vars->map_h);
	printf("w |%d|\n", vars->map_w);
	custom_exit(0);
}
