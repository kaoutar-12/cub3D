/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:06:09 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/23 15:53:59 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *map[] = 
{
"1111111111111111111111111",
"10000001P0000000000000001",
"1000000000000010000000001",
"1000000010000000001000001",
"1111111111111111111111111"
};

void get_player_position(t_player *player)
{
    int i = 0;
    int j = 0;
    while(map[j])
    {
        i = 0;
        while(map[j][i])
        {
            if (map[j][i] == 'P')
            {
                player->x = i * TILE_SIZE + TILE_SIZE / 2;
                player->y = j * TILE_SIZE + TILE_SIZE / 2;
                return ;
            }
            i++;
        }
        j++;
    }
}

int isWall(double x, double y) 
{
    int mapGridIndexX = floor(x / TILE_SIZE);
    int mapGridIndexY = floor(y / TILE_SIZE);
    if (map[mapGridIndexY][mapGridIndexX] == '1')
        return (1);
    else
        return (0);
}

int draw_wall(t_game *game)
{
    int i = 0;
    int j = 0;
    while(map[j])
    {
        i = 0;
        while(map[j][i])
        {
            if (map[j][i] == '1') 
                draw_pixel(game, i * TILE_SIZE, j * TILE_SIZE, 0x808080);
            else
                draw_pixel(game, i * TILE_SIZE, j * TILE_SIZE, 0xFFFFFF);
            i++;
        }
        j++;
    }
    return (0);
}

void ft_game(t_game *game)
{
    game->mlx = mlx_init();
    game->mlx_win = mlx_new_window(game->mlx,strlen(map[0]) * TILE_SIZE, 5 * TILE_SIZE,"cub3d");
    game->data->img = mlx_new_image(game->mlx,strlen(map[0]) * TILE_SIZE, 5 * TILE_SIZE);
    game->data->addr = mlx_get_data_addr(game->data->img, &game->data->bits_per_pixel, &game->data->line_length, &game->data->endian);
    draw_wall(game);
    mlx_put_image_to_window(game->mlx, game->mlx_win, game->data->img, 0, 0);
    mlx_hook(game->mlx_win, 2, 0, key_press, game);
    mlx_hook(game->mlx_win,3,0,key_release,game);
    mlx_hook(game->mlx_win,17,0,close_win,game);
    mlx_loop_hook(game->mlx, draw, game);
    mlx_loop(game->mlx);
}