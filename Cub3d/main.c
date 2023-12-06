/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:05:03 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/06 16:17:21 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game		*game;
	t_player	*player;
	t_ray		*ray;
	t_parse		vars;

	if (ac == 2)
	{
		map_operations(av[1], &vars);
		for (int i = 0; vars.actual_map[i]; i++)
			printf ("|%s|\n", vars.actual_map[i]);
		// printf ("Player[%d][%d] and it's direction is %d equivalent to %c\n", vars.player_x, vars.player_y,
		// 		vars.player_direction, vars.map[vars.player_x][vars.player_y]);
	}
	else
	{
		write(2, "Invalid Arguments\n", 18);
		return (1);
	}
	// garbage_collector(NULL, 1);;
	game = malloc(sizeof(t_game));
	player = malloc(sizeof(t_player));
	ray = malloc(sizeof(t_ray));
	init_rays(ray);
	init_player(player);
	game->player = player;
	game->ray = ray;
	game->parse = &vars;
	printf("Player[%d][%d] and it's direction is %d equivalent to %c\n", game->parse->player_x, game->parse->player_y,
			game->parse->player_direction, game->parse->map[game->parse->player_x][game->parse->player_y]);
	game->player->y = game->parse->player_x * TILE_SIZE + TILE_SIZE / 2;
	game->player->x = game->parse->player_y * TILE_SIZE + TILE_SIZE / 2;

	// for (int i = 0; i < game->parse->map_h; i++) {
	// 	printf("%s\n", game->parse->map[i]);
	// }
	ft_game(game);
}
