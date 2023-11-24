/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:06:09 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/24 19:51:23 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *map[] = 
{
"1111111111111111111111111",
"10000000P0000000000000001",
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
    int i = 0;
    double distence_proj_plane = (1280 * tan(FOV_ANGLE / 2)) / 4 ;
    double ray_dist;
    double wall_strip_height;
    double correct_wall_dist;
    while(i < NUM_RAYS)
    {
        ray_dist = game->ray->distances[i];
        printf("ray_dist: %f\n", ray_dist);
        
        // calcule the distence to the projection plane
        
        correct_wall_dist = ray_dist * cos(game->ray->ray_angles[i] - game->player->rotation_angle);
        // projected wall height
        wall_strip_height = (TILE_SIZE * correct_wall_dist) / game->ray->distances[i];

        printf("wall_strip_height Screen: %f\n", (720 / 2) - (wall_strip_height / 2));
        printf("wall_strip_height: %f\n",wall_strip_height);
        // printf("distence_proj_plane: %f\n", distence_proj_plane);
        // printf("First x: %d\n", i * WALL_STRIP_WIDTH);
        // printf("ray_dist: %f\n", ray_dist);
        
        draw_rect(game, i * WALL_STRIP_WIDTH, (720 / 2) - (wall_strip_height / 2), WALL_STRIP_WIDTH, wall_strip_height, 0x3600E1);
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

            // mlx_pixel_put(game->mlx, game->data->img, pixel_x, pixel_y, color);
            mlx_put_pixel(game->data->img, pixel_x, pixel_y, color);
        }
    }
}

void draw_map(t_game *game)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            int x = j * TILE_SIZE;
            int y = i * TILE_SIZE;

            if (map[i][j] == '1')
            {
                // Draw a wall
                draw_wall(game, x, y, TILE_SIZE, 0x808080);
            }
            else
            {
                // Draw an empty space or floor
                draw_wall(game, x, y, TILE_SIZE, 0xFFFFFF);
            }
        }
    }
}

void ft_game(t_game *game)
{
    game->mlx = mlx_init(1280, 720, "Cub3d", false);
    // game->mlx_win = mlx_new_window(game->mlx,900, 900,"cub3d");
    game->data->img = mlx_new_image(game->mlx, 1280, 720);
    
    mlx_image_to_window(game->mlx, game->data->img, 0, 0);

    // int map[5][5] = {
    //     {1, 1, 1, 1, 1},
    //     {1, 0, 0, 0, 1},
    //     {1, 0, 1, 0, 1},
    //     {1, 0, 0, 0, 1},
    //     {1, 1, 1, 1, 1}
    // };

    // game->data->addr = mlx_get_data_addr(game->data->img, &game->data->bits_per_pixel, &game->data->line_length , &game->data->endian);
    // draw_wall(game);
    // mlx_put_image_to_window(game->mlx, game->mlx_win, game->data->img, 0, 0);
    // mlx_hook(game->mlx_win, 2, 0, key_press, game);
    // mlx_hook(game->mlx_win,3,0,key_release,game);
    // mlx_hook(game->mlx_win,17,0,close_win,game);
    mlx_loop_hook(game->mlx, draw, game);
    mlx_loop_hook(game->mlx, ft_hook, game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
}