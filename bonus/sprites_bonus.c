/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:18:48 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/10 14:02:50 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_idle_sprite(t_game *game, double win_y, double j, uint32_t color)
{
	mlx_texture_t	*sprite;
	double			win_x;
	double			i;
	double			sprite_x;
	double			sprite_y;

	sprite = mlx_load_png("bonus/textures/sprite.png");
	win_x = (WIN_W / 2) - (sprite->width / 2);
	i = win_x;
	while (i < win_x + sprite->width)
	{
		j = win_y;
		sprite_x = (i - win_x) * sprite->width / 500;
		while (j < win_y + sprite->height)
		{
			sprite_y = (j - win_y) * sprite->height / 500;
			color = get_pixel_color(sprite, sprite_x, sprite_y);
			if (color != 0)
				mlx_put_pixel(game->img, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_shoot_sprite(t_game *game, double win_y, double j, uint32_t color)
{
	mlx_texture_t	*sprite;
	double			win_x;
	double			i;
	double			sprite_x;
	double			sprite_y;

	sprite = mlx_load_png("bonus/textures/sprite_shot.png");
	win_x = (WIN_W / 2) - (sprite->width / 2);
	i = win_x;
	while (i < win_x + sprite->width)
	{
		j = win_y;
		sprite_x = (i - win_x) * sprite->width / 500;
		while (j < win_y + sprite->height)
		{
			sprite_y = (j - win_y) * sprite->height / 500;
			color = get_pixel_color(sprite, sprite_x, sprite_y);
			if (color != 0)
				mlx_put_pixel(game->img, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_sprite(t_game *game)
{
	double			j;
	double			win_y;
	uint32_t		color;

	win_y = WIN_H / 2 - 50;
	j = win_y;
	color = 0;
	if (!game->shoot)
		draw_idle_sprite(game, win_y, j, color);
	else
		draw_shoot_sprite(game, win_y, j, color);
}
