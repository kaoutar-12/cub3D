/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:47:36 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/08 17:00:21 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initialise_variables(t_it *it, t_var_calc *calc)
{
	it->i = 0;
	calc->f = 0;
	calc->c = 0;
	calc->no = 0;
	calc->so = 0;
	calc->we = 0;
	calc->ea = 0;
}

int	is_surrounded(t_parse *vars, int i, int j)
{
	if (ft_chrstr("0SWNEP", vars->actual_map[i][j]))
	{
		if (i == table_size(vars->actual_map) - 1
		|| i == 0 || j == 0
		|| j == ft_strlen(vars->actual_map[i]))
			return (0);
		if (ft_chrstr("01SWNEP", vars->actual_map[i][j + 1])
		&& ft_chrstr("01SWNEP", vars->actual_map[i][j - 1])
		&& ft_chrstr("01SWNEP", vars->actual_map[i + 1][j])
		&& ft_chrstr("01SWNEP", vars->actual_map[i - 1][j]))
			return (1);
		else
			return (0);
	}
	return (1);
}

void	check_color(char **color)
{
	t_it	it;

	it.i = 0;
	it.j = 0;
	while (color[it.i])
		it.i++;
	if (it.i != 2)
	{
		write(2, "Error\nInvalid map content\n", 27);
		custom_exit (1);
	}
	it.i = 0;
	while (color[1][it.i])
	{
		if (color[1][it.i] == ',')
			it.j++;
		if (it.j > 2)
		{
			write(2, "Error\nMore than 2 commas\n", 26);
			custom_exit(1);
		}
		it.i++;
	}
}

void	check_calc(t_var_calc	*calc)
{
	if (calc->f != 1 || calc->c != 1
		|| calc->no != 1 || calc->so != 1
		|| calc->ea != 1 || calc->we != 1)
	{
		write(2, "Error\nProvided Map is invalid\n", 31);
		exit (1);
	}
}

void	check_array(char **array)
{
	t_it		it;
	t_var_calc	calc;

	initialise_variables(&it, &calc);
	while (array[it.i])
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
