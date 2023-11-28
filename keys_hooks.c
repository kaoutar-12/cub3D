/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:07:16 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/28 12:55:45 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_game *game)
{
	game->player->turn = -1;
	game->player->rotation_angle += 
		game->player->rotation_speed * game->player->turn;
	game->player->rotation_angle = 
		normalize_angle(game->player->rotation_angle);
}

void	rotate_right(t_game *game)
{
	game->player->turn = 1;
	game->player->rotation_angle += 
		game->player->rotation_speed * game->player->turn;
	game->player->rotation_angle = 
		normalize_angle(game->player->rotation_angle);
}

void	ft_hook(void *param)
{
	t_game	*game;
	double	move_step;

	game = (t_game *)param;
	move_step = game->player->walk * game->player->move_speed; 
	game->player->rotation_angle = 
		normalize_angle(game->player->rotation_angle);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		close_win(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W)) 
		move_up(game, move_step);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S)) 
		move_down(game, move_step);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_left(game, move_step);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_right(game, move_step);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT)) 
		rotate_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT)) 
		rotate_left(game);
}

int	close_win(t_game *game)
{
	mlx_close_window(game->mlx);
	exit(0);
}
