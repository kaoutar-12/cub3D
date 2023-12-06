/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:05:03 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/30 09:56:12 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_game		*game;
	t_player	*player;
	t_ray		*ray;

	game = malloc(sizeof(t_game));
	player = malloc(sizeof(t_player));
	ray = malloc(sizeof(t_ray));
	init_rays(ray);
	init_player(player);
	game->player = player;
	game->ray = ray;
	ft_game(game);
}
