/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:36:09 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/09 20:11:35 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_sky(t_game *game)
{
	uint32_t	i;
	uint32_t	j;
	int			pixel_x;
	int			pixel_y;

	i = 0;
	while (i < game->img->width)
	{
		j = 0;
		while (j < game->img->height / 2)
		{
			pixel_x = i;
			pixel_y = j;
			mlx_put_pixel(game->img, pixel_x, pixel_y,
				ft_rgba(game->parse->c_rgb.red, game->parse->c_rgb.green,
					game->parse->c_rgb.blue, 255));
			j++;
		}
		i++;
	}
}

void	draw_floor(t_game *game)
{
	uint32_t	i;
	uint32_t	j;
	int			pixel_x;
	int			pixel_y;

	i = 0;
	while (i < game->img->width)
	{
		j = game->img->height / 2;
		while (j < game->img->height)
		{
			pixel_x = i;
			pixel_y = j;
			mlx_put_pixel(game->img, pixel_x, pixel_y,
				ft_rgba(game->parse->f_rgb.red, game->parse->f_rgb.green,
					game->parse->f_rgb.blue, 255));
			j++;
		}
		i++;
	}
}

void	draw_sprite(t_game *game)
{
	mlx_texture_t	*sprite;
	mlx_texture_t	*sprite2;

	sprite = mlx_load_png("/Users/kmouradi/Desktop/new/bonus/textures/sprite.png");
	sprite2 = mlx_load_png("/Users/kmouradi/Desktop/new/bonus/textures/sprite_shoooot.png");
	
	double win_x;
	double win_y;
	double i;
	double sprite_x;
	double sprite2_x;
	double sprite_y;
	double sprite2_y;
	
	win_y = WIN_H / 2 - 50;
	double j = win_y;
	win_x = (WIN_W / 2) - (sprite->width / 2);
	i = win_x;
	if (!game->shoot)
	{
		while(i < win_x + sprite->width)
		{
			j = win_y;
			sprite_x = (i - win_x) * sprite->width / 500;
			while(j < win_y + sprite->height)
			{
				sprite_y = (j - win_y) * sprite->height / 500;
				uint32_t color = get_pixel_color(sprite, sprite_x, sprite_y);
				if (color != 0)
					mlx_put_pixel(game->img, i, j, color);
				j++;
			}
			i++;
		}
	}
	else
	{
		while(i < win_x + sprite2->width)
		{
			j = win_y;
			sprite2_x = (i - win_x) * sprite2->width / 500;
			while(j < win_y + sprite2->height)
			{
				sprite2_y = (j - win_y) * sprite2->height / 500;
				uint32_t color = get_pixel_color(sprite2, sprite2_x, sprite2_y);
				if (color != 0)
					mlx_put_pixel(game->img, i, j, color);
				j++;
			}
			i++;
		}
	}
}

int draw_player(t_game *game)
{
    int y = -game->player->radius;

    while (y <= game->player->radius)
    {
        int x = -game->player->radius;
        while (x <= game->player->radius)
        {
            // Check if the pixel is inside the circular boundary
            if (x * x + y * y <= game->player->radius * game->player->radius)
            {	
                int drawX = WIN_W / 2 + x;  // Always draw at the center
                int drawY = WIN_H / 2 + y;  // Always draw at the center

                // Draw the pixel
                if (drawX >= 0 && drawX < WIN_W && drawY >= 0 && drawY < WIN_H)
                    mlx_put_pixel(game->img, drawX, drawY, ft_rgba(255, 0, 0, 255));
            }
            x++;
        }
        y++;
    }

    return (0);
}

void draw_wall(t_game *game)
{
    int i;
    int j;
    int x;
    int y;

    i = 0;
    while (i < game->parse->map_h)
    {
        j = 0;
        while (j < game->parse->map_w)
        {
            x = (WIN_W / 2) - game->player->x + (j * TILE_SIZE);
            y = (WIN_H / 2) - game->player->y + (i * TILE_SIZE);
            if (game->parse->actual_map[i][j] == '1')
                draw_square(game, x, y, ft_rgba(255, 255, 255, 255));
			else if (game->parse->actual_map[i][j] == '0' || game->parse->actual_map[i][j] == 'E'
				|| game->parse->actual_map[i][j] == 'W'
				|| game->parse->actual_map[i][j] == 'N'
				|| game->parse->actual_map[i][j] == 'S')
				draw_square(game, x, y, ft_rgba(0, 0, 0, 255));
            j++;
        }
        i++;
    }
    draw_player(game);
}

void draw_square(t_game *game, int x, int y, int color)
{
    int i;
    int j;
    int size;

    i = 0;
    size = TILE_SIZE;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            mlx_put_pixel(game->img, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void	draw(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	// draw_sky(game);
	// draw_floor(game);
	// projectd_wall(game);
	cast_rays(game);
	// draw_sprite(game);
	draw_wall(game);
}
