/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:44:40 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/08 11:58:27 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	path_or_color(char *variable)
{
	if (!ft_strncmp(variable, "NO ", 3)
		|| !ft_strncmp(variable, "SO ", 3)
		|| !ft_strncmp(variable, "WE ", 3)
		|| !ft_strncmp(variable, "EA ", 3))
		return (1);
	else if (!ft_strncmp(variable, "F ", 2)
		|| !ft_strncmp(variable, "C ", 2))
		return (2);
	return (0);
}

void	initialise_colors(t_parse *vars, t_rgb_data *rgb_data)
{
	if (!rgb_data->rgb_c[0] || !rgb_data->rgb_c[1]
		|| !rgb_data->rgb_c[2] || !rgb_data->rgb_f[0]
		|| !rgb_data->rgb_c[1] || !rgb_data->rgb_f[2])
	{
		free (rgb_data->rgb_c);
		free (rgb_data->rgb_f);
		write(2, "Error:\nMap content must be in the format \"ddd, ddd, ddd,\" with each 'ddd' between 0 and 255\n", 93);
		custom_exit(1);
	}
	vars->c_rgb.red = ft_my_atoi(rgb_data->rgb_c[0]);
	vars->c_rgb.green = ft_my_atoi(rgb_data->rgb_c[1]);
	vars->c_rgb.blue = ft_my_atoi(rgb_data->rgb_c[2]);
	vars->f_rgb.red = ft_my_atoi(rgb_data->rgb_f[0]);
	vars->f_rgb.green = ft_my_atoi(rgb_data->rgb_f[1]);
	vars->f_rgb.blue = ft_my_atoi(rgb_data->rgb_f[2]);
}

void	set_color3(t_parse *vars, t_rgb_data *rgb_data)
{
	t_it	it;

	it.i = 0;
	if (!rgb_data->rgb_c || !rgb_data->rgb_f)
	{
		write(2, "Error\n", 6);
		custom_exit(1);
	}
	initialise_colors(vars, rgb_data);
	if (vars->c_rgb.red > 255 || vars->c_rgb.red < 0
		|| vars->c_rgb.blue > 255 || vars->c_rgb.blue < 0
		|| vars->c_rgb.green > 255 || vars->c_rgb.green < 0
		|| vars->f_rgb.red > 255 || vars->f_rgb.red < 0
		|| vars->f_rgb.blue > 255 || vars->f_rgb.blue < 0
		|| vars->f_rgb.green > 255 || vars->f_rgb.green < 0)
	{
		free (rgb_data->rgb_c);
		free (rgb_data->rgb_f);
		write(2, "Error\nvalue of rgb must be 0 to 255", 36);
		custom_exit(1);
	}
	free (rgb_data->rgb_c);
	free (rgb_data->rgb_f);
}

void	set_data(t_parse *vars, char *arr)
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
		if (path_or_color(array[it.i]) == 1)
			paths[it.j++] = ft_strtrim(array[it.i], " ");
		else if (path_or_color(array[it.i]) == 2)
			colors[it.k++] = ft_strtrim(array[it.i], " ");
		it.i++;
	}
	free(array);
	set_path(vars, paths, it);
	set_color(vars, colors);
}

void	set_path(t_parse *vars, char **paths, t_it it)
{
	char	**data_path;

	if (it.j != 4 || it.k != 2)
	{
		write(2, "Error\nPaths or colors are invalid", 34);
		custom_exit(1);
	}
	it.i = 0;
	while (paths[it.i])
	{
		data_path = ft_split2(paths[it.i], ' ');
		check_path(vars, data_path);
		it.i++;
	}
}
