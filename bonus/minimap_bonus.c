/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:47:56 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/10 13:48:59 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void draw_square_around_player(t_game *game)
{
    int x;
    int y;
	
	y = game->player->begin_y;
    while (y < game->player->end_y)
    {
		x = game->player->begin_x;
        while (x < game->player->end_x)
        {
            if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
            {
                mlx_put_pixel(game->img, x, y, ft_rgba(0, 0, 0, 100)); 
            }
			x++;
        }
		y++;
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
            if (x * x + y * y <= game->player->radius * game->player->radius)
            {	
                double drawX = (400 + x) * MINI_MAP;
                double drawY = (400 + y) * MINI_MAP; 
                if (drawX >= 0 && drawX < WIN_W && drawY >= 0 && drawY < WIN_H)
                    mlx_put_pixel(game->img, drawX, drawY, ft_rgba(255, 0, 0, 255));
            }
            x++;
        }
        y++;
    }

    return (0);
}

void draw_minimap_square(t_game *game, int x, int y, int color)
{
    int i;
    int j;
    int size;

    i = 0;
    size = 400;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            mlx_put_pixel(game->img, (x + j) * MINI_MAP, (y + i) * MINI_MAP, color);
            j++;
        }
        i++;
    }
}

void draw_wall(t_game *game)
{
    int i;
    int j;
    int x;
    int y;

    i = 0;		
    while (i < 70)
    {
        j = 0;
        while (j < 70)
        {
            x = (400 - game->player->x + (j * TILE_SIZE));
            y = (400 - game->player->y + (i * TILE_SIZE));
            if (game->parse->actual_map[i][j] == '1')
                draw_square(game, x, y, ft_rgba(255, 255, 255, 255));
			else if ((game->parse->actual_map[i][j] == '0' || game->parse->actual_map[i][j] == 'E'
				|| game->parse->actual_map[i][j] == 'W'
				|| game->parse->actual_map[i][j] == 'N'
				|| game->parse->actual_map[i][j] == 'S'))
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
			double draw_x = (x + j) * MINI_MAP;
			double draw_y = (y + i) * MINI_MAP;
			if ((draw_x >= game->player->begin_x && draw_x <= game->player->end_x && draw_y >= game->player->begin_y && draw_y <= game->player->end_y)
				&& (draw_x > 0 && draw_x < WIN_W && draw_y > 0 && draw_y < WIN_H))
            	mlx_put_pixel(game->img, draw_x, draw_y, color);
            j++;
        }
        i++;
    }
}