/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:06:09 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/25 18:07:29 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *map[] = 
{
"1111111111111111111111111",
"1000000000000000000000001",
"10000000P0000010000000001",
"1000000010000001001000001",
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

// int draw_wall(t_game *game)
// {
//     int i = 0;
//     int j = 0;
//     while(map[j])
//     {
//         i = 0;
//         while(map[j][i])
//         {
//             if (map[j][i] == '1') 
//                 draw_pixel(game, i * TILE_SIZE * 0.2 , j * TILE_SIZE * 0.2, 0x808080);
//             else
//                 draw_pixel(game, i * TILE_SIZE * 0.2, j * TILE_SIZE * 0.2, 0xFFFFFF);
//             i++;
//         }
//         j++;
//     }
//     return (0);
// }

void projectd_wall(t_game *game)
{
    uint32_t color = ft_pixel(255, 0, 0, 255);
    int i = 0;
    while(i < NUM_RAYS)
    {
        double correct_wall_distance = game->ray->distances[i] * cos(game->ray->ray_angles[i] - game->player->rotation_angle);
        double distance_projection_plane = (WIN_W * tan(FOV_ANGLE / 2)) / 2;
        double wall_strip_height = (TILE_SIZE / correct_wall_distance) * distance_projection_plane;
        if (wall_strip_height >= WIN_H)
            wall_strip_height = WIN_H;
        draw_rect(game, i * WALL_STRIP_WIDTH , (WIN_H / 2) - (wall_strip_height / 2), WALL_STRIP_WIDTH, wall_strip_height, color);
        i++;
    }
}

void draw_wall(t_game *game, int x, int y, int size, int color)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int pixel_x = x + i;
            int pixel_y = y + j;

            // mlx_pixel_put(game->mlx, game->img, pixel_x, pixel_y, color);
            mlx_put_pixel(game->img, pixel_x, pixel_y, color);
        }
    }
}

void draw_wall2(t_game *game)
{
    int i = 0;
    int j ;
    while(i < 5)
    {
        j = 0;
        while(j < 26)
        {
            int x = j * TILE_SIZE;
            int y = i * TILE_SIZE;
            if (map[i][j] == '1')
                draw_wall(game,x * MINI_MAP, y* MINI_MAP,TILE_SIZE* MINI_MAP,ft_pixel(255,255,255,255));
            j++;
        }
        i++;
    }
}

void draw_map(t_game *game)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            int x = j * TILE_SIZE;
            int y = i * TILE_SIZE;

                // Draw an empty space or floor
                draw_wall(game, x * MINI_MAP, y * MINI_MAP, TILE_SIZE * MINI_MAP, ft_pixel(0,0,0,255));
        }
    }
}

void ft_game(t_game *game)
{
    game->mlx = mlx_init(WIN_W, WIN_H, "Cub3d", false);
    // game->mlx_win = mlx_new_window(game->mlx,900, 900,"cub3d");
    game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
    
    mlx_image_to_window(game->mlx, game->img, 0, 0);
    // mlx_hook(game->mlx_win, 2, 0, key_press, game);
    // mlx_hook(game->mlx_win,3,0,key_release,game);
    // mlx_hook(game->mlx_win,17,0,close_win,game);
    mlx_loop_hook(game->mlx, draw, game);
    mlx_loop_hook(game->mlx, ft_hook, game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
}