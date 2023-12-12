/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:05:03 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/12 15:01:02 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	game->player->begin_x = (400 + game->player->x) * MINI_MAP - 400;
	game->player->end_x = (400 + game->player->x) * MINI_MAP + 70;
	game->player->begin_y = (400 + game->player->y) * MINI_MAP - 400;
	game->player->end_y = (400 + game->player->y) * MINI_MAP;
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
