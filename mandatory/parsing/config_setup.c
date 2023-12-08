/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:41:43 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/08 11:55:54 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_color(t_parse *vars, char **colors)
{
	t_it		it;
	t_rgb_data	rgb_data;
	char		**data_color;

	it.i = 0;
	it.j = 0;
	it.k = 0;
	while (colors[it.i])
	{
		data_color = ft_split2(colors[it.i], ' ');
		check_color(data_color);
		if (!ft_strcmp("F", data_color[0]))
			rgb_data.rgb_f = ft_split(data_color[1], ',');
		else if (!ft_strcmp("C", data_color[0]))
			rgb_data.rgb_c = ft_split(data_color[1], ',');
		it.i++;
	}
	set_color3(vars, &rgb_data);
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

int	path_is_valid(char **path)
{
	t_it	it;

	it.i = 0;
	while (path[it.i])
		it.i++;
	if (it.i != 2)
	{
		write(2, "Error\nInvalid map content, please ensure path name doesn't contain spaces\n", 75);
		exit (1);
	}
	if (ft_strcmp(path[1] + strlen(path[1]) - 4, ".png")
		&& ft_strcmp(path[1] + strlen(path[1]) - 4, ".PNG"))
	{
		write(2, "Error\nInvalid path extention\n", 29);
		exit (1);
	}
	if (access(path[1], R_OK))
	{
		perror("Error\nPath");
		exit (1);
	}
	return (1);
}

void	check_path(t_parse *vars, char **path)
{
	if (path_is_valid(path))
	{
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
