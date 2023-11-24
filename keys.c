/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:07:16 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/24 13:00:13 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_hook(void* param)
{
	t_game *game = (t_game *)param;
    float move_step = game->player->walk * game->player->move_speed; 
    double newPlayerX;
    double newPlayerY;
    game->player->rotation_angle = normalize_angle(game->player->rotation_angle);

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		close_win(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP)) {
                game->player->walk = 1;
        newPlayerX = game->player->x + cos(game->player->rotation_angle) * move_step;
        newPlayerY = game->player->y + sin(game->player->rotation_angle) * move_step;
        if (isWall(newPlayerX, newPlayerY) == 0)
        {
            game->player->x = newPlayerX;
            game->player->y = newPlayerY;
        }
    }
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN)) {

                game->player->walk = -1;
        newPlayerX = game->player->x + cos(game->player->rotation_angle) * move_step;
        newPlayerY = game->player->y + sin(game->player->rotation_angle) * move_step;
        if (isWall(newPlayerX, newPlayerY) == 0)
        {
            game->player->x = newPlayerX;
            game->player->y = newPlayerY;
        }
    }
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT)) {
        game->player->turn = 1;
        game->player->rotation_angle += game->player->rotation_speed * game->player->turn;
        game->player->rotation_angle = normalize_angle(game->player->rotation_angle);
    }
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT)) {
        game->player->turn = -1;
        game->player->rotation_angle += game->player->rotation_speed * game->player->turn;
        game->player->rotation_angle = normalize_angle(game->player->rotation_angle);
    }
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
    mlx_close_window(game->mlx);
    exit(0);
}