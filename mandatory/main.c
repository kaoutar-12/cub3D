/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:05:03 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/08 10:21:12 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_msg(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

void	set_player_direction(t_game *game)
{
	if (game->parse->player_direction == NORTH)
		game->player->rotation_angle = M_PI * 1.5;
	else if (game->parse->player_direction == SOUTH)
		game->player->rotation_angle = M_PI / 2;
	else if (game->parse->player_direction == EAST)
		game->player->rotation_angle = 0;
	else if (game->parse->player_direction == WEST)
		game->player->rotation_angle = M_PI;
}

void	fun()
{
	system("leaks Cub3d");
}

int	main(int ac, char **av)
{
	t_game		*game;
	t_player	*player;
	t_ray		*ray;
	t_parse		parse;


	if (ac == 2)
	{
		atexit(fun);
		map_operations(av[1], &parse);
		game = malloc(sizeof(t_game));
		player = malloc(sizeof(t_player));
		ray = malloc(sizeof(t_ray));
		if (!game || !player || !ray)
			error_msg();
		init_rays(ray);
		init_player(player);
		game->player = player;
		game->ray = ray;
		game->parse = &parse;
		game->player->y = game->parse->player_x * TILE_SIZE + TILE_SIZE / 2;
		game->player->x = game->parse->player_y * TILE_SIZE + TILE_SIZE / 2;
		set_player_direction(game);
		ft_game(game);
		free_game(game);
	}
	else
		error_msg();
}
