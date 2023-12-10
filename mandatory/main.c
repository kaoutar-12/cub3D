/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:05:03 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/08 10:40:07 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_direction_pos(t_game *game)
{
	game->player->y = game->parse->player_x * TILE_SIZE + TILE_SIZE / 2;
	game->player->x = game->parse->player_y * TILE_SIZE + TILE_SIZE / 2;
	if (game->parse->player_direction == NORTH)
		game->player->rotation_angle = M_PI * 1.5;
	else if (game->parse->player_direction == SOUTH)
		game->player->rotation_angle = M_PI / 2;
	else if (game->parse->player_direction == EAST)
		game->player->rotation_angle = 0;
	else if (game->parse->player_direction == WEST)
		game->player->rotation_angle = M_PI;
}

int	main(int ac, char **av)
{
	t_game		*game;
	t_player	*player;
	t_ray		*ray;
	t_parse		parse;

	if (ac == 2)
	{
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
		set_player_direction_pos(game);
		ft_game(game);
		free_game(game);
	}
	else
		error_msg();
}
