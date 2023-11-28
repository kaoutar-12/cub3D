/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:39:15 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/28 13:02:46 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//TODO change 7 and 26 
// void	draw_wall(t_game *game)
// {
// 	int	i;
// 	int	j;
// 	int	x;
// 	int	y;

// 	i = 0;
// 	while (i < 7)
// 	{
// 		j = 0;
// 		while (j < 26)
// 		{
// 			x = j * TILE_SIZE;
// 			y = i * TILE_SIZE;
// 			if (map[i][j] == '1')
// 				draw_square(game, x * MINI_MAP,
// 					y * MINI_MAP, ft_rgba(255, 255, 255, 255));
// 			j++;
// 		}
// 		i++;
// 	}
// }

// //TODO change 7 and 26 
// void	draw_map(t_game *game)
// {
// 	int	i;
// 	int	j;
// 	int	x;
// 	int	y;

// 	i = 0;
// 	while (i < 7)
// 	{
// 		j = 0;
// 		while (j < 25)
// 		{
// 			x = j * TILE_SIZE;
// 			y = i * TILE_SIZE;
// 			draw_square(game, x * MINI_MAP, y * MINI_MAP,
// 				ft_rgba(0, 0, 0, 255));
// 			j++;
// 		}
// 		i++;
// 	}
// }

int	draw_player(t_game *game)
{
	int	y;
	int	x;
	int	draw_x;
	int	draw_y;

	y = game->player->radius;
	while (y <= game->player->radius)
	{
		x = game->player->radius;
		while (x <= game->player->radius)
		{
			if (x * x + y * y <= game->player->radius * game->player->radius)
			{
				draw_x = game->player->x;
				draw_y = game->player->y;
				mlx_put_pixel(game->img, draw_x * MINI_MAP,
					draw_y * MINI_MAP, ft_rgba(255, 0, 0, 255));
			}
			x++;
		}
		y++;
	}
	return (0);
}
