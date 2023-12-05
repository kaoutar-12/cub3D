/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:02:20 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/05 16:10:55 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_2d(char **data)
{
	while (*data)
	{
		free(*data);
	}
	free(data);
}

int		ft_chrstr(char *s, int c)
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

int	is_surrounded(t_parse *vars, int i, int j)
{
	if (ft_chrstr("0SWNEP", vars->map[i][j]))
	{
		if (ft_chrstr("01SWNEP", vars->map[i][j + 1])
		&& ft_chrstr("01SWNEP", vars->map[i][j - 1])
		&& ft_chrstr("01SWNEP", vars->map[i + 1][j])
		&& ft_chrstr("01SWNEP", vars->map[i - 1][j]))
			return (1);
		else
			return (0);
	}
	return (1);
}

char	*allocate_space(int count, int size)
{
	char	*str;

	str = gc_malloc (size * count);
	ft_memset(str, ' ', size * count);
	return (str);
}

void	set_map(char **map, int longest)
{
	int		i;
	char	*tmp;

	i = 0;
	while (map[i])
	{
		tmp = allocate_space(sizeof(char), longest - 1);
		ft_strcpy(tmp, map[i]);
		map[i] = tmp;
		i++;
	}
}

int		check_map2(t_parse *vars)
{
	int i = 0;
	int j = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (!is_surrounded(vars, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	set_map_size(t_parse *vars, int y)
{
	int	x;

	x = 0;
	while(vars->map[x])
	{
		x++;
	}
	vars->map_h = x;
	vars->map_w = y;
}

int	detect_type(char *element)
{
	if (!ft_strncmp(element, "NO", -1))
		return (NO);
	else if (!ft_strncmp(element, "SO", -1))
		return (SO);
	else if (!ft_strncmp(element, "WE", -1))
		return (WE);
	else if (!ft_strncmp(element, "EA", -1))
		return (EA);
	else if (!ft_strncmp(element, "F", -1))
		return (F);
	else if (!ft_strncmp(element, "C", -1))
		return (C);
	return (-1);
}

void	check_path(t_parse *vars, char **path)
{
	t_it	it;

	it.i = 0;
	while (path[it.i])
		it.i++;
	if (it.i != 2)
	{
		write(2, "Invalid map content", 20);
		custom_exit(1);
	}
	// printf ("|%s|\n", path[1]);
	if (ft_strcmp(path[1] + strlen(path[1]) - 4, ".png"))
	{
		write(2, "Error\nInvalid path extention\n", 29);
		custom_exit(1);
	}
	if (access(path[1], R_OK))
	{
		perror("IMAGE");
		custom_exit(1);
	}
	else
	{
		// vars->ea = ft_strdup(path[1]);
		if (detect_type(path[0]) == NO)
			vars->no = ft_strdup(path[1]);
		else if (detect_type(path[0]) == SO)
			vars->so = ft_strdup(path[1]);
		else if (detect_type(path[0]) == WE)
			vars->we = ft_strdup(path[1]);
		else if (detect_type(path[0]) == EA)
			vars->ea = ft_strdup(path[1]);
	}
}

char	**set_color2(char *color)
{
	char	**rgb;

	rgb = ft_split (color, ',');
	return (rgb);
}

void	check_color(char **color, t_rgb_data *data)
{
	t_it	it;

	it.i = 0;
	it.j = 0;
	while (color[it.i])
		it.i++;
	if (it.i != 2)
	{
		write(2, "Invalid map content", 20);
		custom_exit(1);
	}
	it.i = 0;
	// printf ("%s\n", color[0]);
	while(color[1][it.i])
	{
		if (color[1][it.i] == ',')
			it.j++;
		if (it.j > 2)
		{
			printf ("More than 2 commas\n");
			custom_exit(1);
		}
		it.i++;
	}
	if (!ft_strcmp(color[0], "F"))
		data->rgb_f = set_color2(color[1]);
	if (!ft_strcmp(color[0], "C"))
		data->rgb_c = set_color2(color[1]);
	free(color[0]);
	free(color[1]);
	free(color);
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
			write(2, "Error:\nMap content must be in the format \"ddd, ddd, ddd,\" with each 'ddd' between 0 and 255\n", 93);
			custom_exit(1);
		}
		it.i++;
	}
	return (ft_atoi (color));
}

void	set_color3(t_parse *vars, t_rgb_data *rgb_data)
{
	t_it	it;

	it.i = 0;
	vars->c_rgb.red = ft_my_atoi(rgb_data->rgb_c[0]);
	vars->c_rgb.green = ft_my_atoi(rgb_data->rgb_c[1]);
	vars->c_rgb.blue = ft_my_atoi(rgb_data->rgb_c[2]);
	vars->f_rgb.red = ft_my_atoi(rgb_data->rgb_f[0]);
	vars->f_rgb.green = ft_my_atoi(rgb_data->rgb_f[1]);
	vars->f_rgb.blue = ft_my_atoi(rgb_data->rgb_f[2]);
	if (vars->c_rgb.red > 255 || vars->c_rgb.red < 0
		|| vars->c_rgb.blue > 255 || vars->c_rgb.blue < 0
		|| vars->c_rgb.green > 255 || vars->c_rgb.green < 0
		|| vars->f_rgb.red > 255 || vars->f_rgb.red < 0
		|| vars->f_rgb.blue > 255 || vars->f_rgb.blue < 0
		|| vars->f_rgb.green > 255 || vars->f_rgb.green < 0)
		{
			write(2, "Error\nvalue of rgb must be 0 to 255", 36);
			custom_exit(1);
		}
}

void	set_color(t_parse *vars, char **colors)
{
	t_it		it;
	t_rgb_data	rgb_data;
	char		**data_color;

	it.i = 0;
	while (colors[it.i])
	{
		data_color = ft_split(colors[it.i], ' ');
		check_color(data_color, &rgb_data);
		it.i++;
	}
	set_color3(vars, &rgb_data);
}


void	set_path(t_parse *vars, char **paths)
{
	char	**data_path;
	t_it	it;

	it.i = 0;
	while (paths[it.i])
	{
		data_path = ft_split (paths[it.i], ' ');
		check_path(vars, data_path);
		it.i++;
	}
}


void	check_calc(t_var_calc	*calc)
{
	if (calc->f != 1 || calc->c != 1
		|| calc->no != 1 || calc->so != 1
		|| calc->ea != 1 || calc->we != 1)
	{
		write(2, "Error\nInvalid map content", 26);
		custom_exit(1);
	}
}

void	check_array(char **array)
{
	t_it		it;
	t_var_calc	calc;

	it.i = 0;
	calc.f = 0;
	calc.c = 0;
	calc.no = 0;
	calc.so = 0;
	calc.we = 0;
	calc.ea = 0;
	while(array[it.i])
	{
		if (!ft_strncmp(array[it.i], "SO ", 3))
			calc.so++;
		if (!ft_strncmp(array[it.i], "NO ", 3))
			calc.no++;
		if (!ft_strncmp(array[it.i], "WE ", 3))
			calc.we++;
		if (!ft_strncmp(array[it.i], "EA ", 3))
			calc.ea++;
		if (!ft_strncmp(array[it.i], "F ", 2))
			calc.f++;
		if (!ft_strncmp(array[it.i], "C ", 2))
			calc.c++;
		it.i++;
	}
	check_calc(&calc);
}

void	set_data(t_parse *vars, char *arr)//
{
	char	**array;
	char	**paths;
	char	**colors;
	t_it	it;

	it.i = 0;
	it.j = 0;
	it.k = 0;
	paths = gc_malloc(sizeof(char *) * 5);
	colors = gc_malloc(sizeof(char *) * 3);
	colors[2] = NULL;
	paths[4] = NULL;
	array = ft_split (arr, '\n');
	check_array(array);
	while (array[it.i])
	{
		// printf ("%s\n", ft_strtrim(array[it.i], " "));
		if (!ft_strncmp(array[it.i], "NO ", 3)
		|| !ft_strncmp(array[it.i], "SO ", 3)
		|| !ft_strncmp(array[it.i], "WE ", 3)
		|| !ft_strncmp(array[it.i], "EA ", 3))
		{
			paths[it.j++] = ft_strtrim(array[it.i], " ");
			// printf ("|%s|\n", paths[it.j - 1]);
		}
		else if (!ft_strncmp(array[it.i], "F ", 2)
		|| !ft_strncmp(array[it.i], "C ", 2))
		{
			colors[it.k++] = ft_strtrim(array[it.i], " ");
			// printf ("|%s|\n", colors[it.k - 1]);
		}
		it.i++;
	}
	// printf ("more than 4 paths %d or more than 2 color sets %d\n", it.j, it.k);
	if (it.j != 4 || it.k != 2)
	{
		write(2, "Invalid map content", 20);
		custom_exit(1);
	}
	set_path(vars, paths);
	set_color(vars, colors);
}


void	map_operations(char *map_name, t_parse *vars)
{
	int		fd;
	char	*arr;

	fd = open (map_name, O_RDONLY);
	if (ft_strcmp(map_name + strlen(map_name) - 4, ".cub"))
	{
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
	if (check_map2(vars))
	{
		printf ("Valid Map\n");
		// printf("c_rgb.blue : %d\n", vars->c_rgb.blue);
		// printf("c_rgb.green : %d\n", vars->c_rgb.green);
		// printf("c_rgb.red : %d\n", vars->c_rgb.red);

		// printf("\nf_rgb.blue : %d\n", vars->f_rgb.blue);
		// printf("f_rgb.green : %d\n", vars->f_rgb.green);
		// printf("f_rgb.red : %d\n", vars->f_rgb.red);

		// printf("\npath NO %s\n", vars->no);
		// printf("path SO %s\n", vars->so);
		// printf("path WE %s\n", vars->we);
		// printf("path EA %s\n", vars->ea);

		// printf ("\n------------MAP-----------\n\n");
		// for (int i = 0; vars->map[i]; i++)
		// {
		// 	printf ("|%s|\n", vars->map[i]);
		// }
	}
	else
	{
		printf ("CHECK MAP AGAIN!\n");
	}
}