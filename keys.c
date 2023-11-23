/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:07:16 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/23 09:23:37 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int key_release(int keycode, t_game *game)
{
    if (keycode == 1 || keycode == 125)
        game->player->walk = 0;
    if (keycode == 13 || keycode == 126)
        game->player->walk = 0;
    if (keycode == 0 || keycode == 123)
        game->player->turn = 0;
    if (keycode == 2 || keycode == 124)
        game->player->turn = 0;
    return 0;
}

double normalize_angle(double angle)
{
    angle = remainder(angle, 2 * M_PI);
    if (angle < 0)
        angle = (2 * M_PI) + angle; 
    return (angle); 
}

int close_win(t_game *game)
{
    mlx_destroy_window(game->mlx, game->mlx_win);
    exit(0);
}

int key_press(int keycode, t_game *game)
{
    float move_step = game->player->walk * game->player->move_speed; 
    double newPlayerX;
    double newPlayerY;
    // game->player->rotation_angle = normalize_angle(game->player->rotation_angle);
    if (keycode == 53)
        close_win(game);
    if (keycode == 1 || keycode == 125)
    {
        game->player->walk = -1;
        newPlayerX = game->player->x + cos(game->player->rotation_angle) * move_step;
        newPlayerY = game->player->y + sin(game->player->rotation_angle) * move_step;
        if (isWall(newPlayerX, newPlayerY) == 0)
        {
            game->player->x = newPlayerX;
            game->player->y = newPlayerY;
        }
    }
    if (keycode == 13 || keycode == 126 )
    {
        game->player->walk = 1;
        newPlayerX = game->player->x + cos(game->player->rotation_angle) * move_step;
        newPlayerY = game->player->y + sin(game->player->rotation_angle) * move_step;
        if (isWall(newPlayerX, newPlayerY) == 0)
        {
            game->player->x = newPlayerX;
            game->player->y = newPlayerY;
        }
        
    }
    if (keycode == 0 || keycode == 123)
    {
        game->player->turn = 1;
        game->player->rotation_angle += game->player->rotation_speed * game->player->turn;
        game->player->rotation_angle = normalize_angle(game->player->rotation_angle);
    }
    if (keycode == 2 || keycode == 124)
    {
        game->player->turn = -1;
        game->player->rotation_angle += game->player->rotation_speed * game->player->turn;
        game->player->rotation_angle = normalize_angle(game->player->rotation_angle);
    }
    return 0;
}