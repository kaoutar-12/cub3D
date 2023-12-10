/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:07:16 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/10 15:52:59 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	mouse_hook(double xpos, double ypos, void *param)
{
	t_game			*game;
	int				diff;
	double			sens;
	static double	last = -1.0;

	sens = 0.0075;
	game = (t_game *)param;
	if (xpos > 0 && xpos < WIN_W && ypos > 0 && ypos < WIN_H)
	{
		if (last != -1)
		{
			diff = xpos - last;
			game->player->rotation_angle += diff * sens;
		}
		last = xpos;
	}
	else
		last = -1;
}

void	rotate_left(t_game *game)
{
	game->player->turn = -1;
	game->player->rotation_angle
		+= game->player->rotation_speed * game->player->turn;
	game->player->rotation_angle
		= normalize_angle(game->player->rotation_angle);
}

void	rotate_right(t_game *game)
{
	game->player->turn = 1;
	game->player->rotation_angle
		+= game->player->rotation_speed * game->player->turn;
	game->player->rotation_angle
		= normalize_angle(game->player->rotation_angle);
}

void	mouse_clicks(t_game *game)
{
	if (mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
		game->shoot = true;
	else
		game->shoot = false;
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		game->change = KNIFE;
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		game->change = GUN;
}

void	ft_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->player->rotation_angle
		= normalize_angle(game->player->rotation_angle);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		close_win(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_up(game, game->player->walk * game->player->move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_down(game, game->player->walk * game->player->move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left(game, game->player->walk * game->player->move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_right(game, game->player->walk * game->player->move_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_left(game);
	mouse_clicks(game);
}
