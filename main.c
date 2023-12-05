/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:05:03 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/05 14:33:07 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	// t_game		*game;
	// t_player	*player;
	// t_ray		*ray;
	t_parse		vars;

	if (ac == 2)
		map_operations(av[1], &vars);
	else
	{
		write(2, "Invalid Arguments\n", 18);
		return (1);
	}
	// while (1);
	// game = malloc(sizeof(t_game));
	// player = malloc(sizeof(t_player));
	// ray = malloc(sizeof(t_ray));
	// init_rays(ray);
	// init_player(player);
	// game->player = player;
	// game->ray = ray;
	// ft_game(game);
	system("leaks Cub3d");
}
