/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 10:45:10 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/20 11:22:33 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

#define TILE_SIZE 64

char *map[] = 
{
"1111111111111111111111111",
"1000000000000000000000001",
"1000000000000010000000001",
"10000000000000000000000P1",
"1111111111111111111111111"
};

int draw_player(t_game *game)
{
    
    int i = 0;
    int j = 0;
    while (j < 10)
    {
        i = 0;
        while (i < 10)
        {
             mlx_pixel_put(game->mlx, game->mlx_win, game->player->x + i, game->player->y + j, 0x00FF0000);
            i++;
        }
        j++;
    }
    return (0);
}

void draw_pixel(t_game *game, int x, int y, int color)
{
    for (int j = 0; j < TILE_SIZE; j++)
    {
        for (int i = 0; i < TILE_SIZE; i++)
        {
            int pixel_index = (y + j) * game->data->line_length + (x + i) * (game->data->bits_per_pixel / 8);

            game->data->addr[pixel_index] = (color >> 16) & 0xFF;   
            game->data->addr[pixel_index + 1] = (color >> 8) & 0xFF; 
            game->data->addr[pixel_index + 2] = color & 0xFF;        
        }
    }
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

int draw(t_game *game) {
    mlx_clear_window(game->mlx, game->mlx_win);
    draw_wall(game);
        mlx_put_image_to_window(game->mlx, game->mlx_win, game->data->img, 0, 0);
    draw_player(game);
    return 0;
}

int close_win(t_game *game)
{
    mlx_destroy_window(game->mlx, game->mlx_win);
    exit(0);
}

int key_press(int keycode, t_game *game)
{
    if (keycode == 53)
        close_win(game);
    if (keycode == 1 || keycode == 125)
    {
        game->player->x += cos(game->player->rotation_angle) * game->player->move_speed;
        game->player->y += sin(game->player->rotation_angle) * game->player->move_speed;
    }
    if (keycode == 13 || keycode == 126)
    {
        game->player->x -= cos(game->player->rotation_angle) * game->player->move_speed;
        game->player->y -= sin(game->player->rotation_angle) * game->player->move_speed;
        
    }
    if (keycode == 0 || keycode == 123)
    {
         
    }
    return 0;
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
    mlx_hook(game->mlx_win,17,0,close_win,game);
    mlx_loop_hook(game->mlx, draw, game);
    mlx_loop(game->mlx);
}

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



void init_player(t_player *player) {
	player->radius = 3;
	player->turn = 0;
	player->walk = 0;
	player->rotation_angle = PI / 2;
	player->move_speed = 2.0;
	player->rotation_speed = 2 * (PI / 180);
    get_player_position(player);
}


int main()
{
    t_game *game;
    t_player *player;
    t_data *data;
    game = malloc(sizeof(t_game));
    player = malloc(sizeof(t_player));
    data = malloc(sizeof(t_data));
    init_player(player);
    game->player = player;
    game->data = data;
    ft_game(game);
}