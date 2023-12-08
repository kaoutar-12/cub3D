/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:07:16 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/08 10:43:30 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	ft_hook(void *param)
{
	t_game	*game;
	double	move_step;

	game = (t_game *)param;
	move_step = game->player->walk * game->player->move_speed;
	game->player->rotation_angle
		= normalize_angle(game->player->rotation_angle);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		close_win(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_up(game, move_step);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_down(game, move_step);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left(game, move_step);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_right(game, move_step);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_left(game);
}

void	free_textures(t_game *game)
{
	if (game->textures)
	{
		if (game->textures[NORTH])
		{
			free(game->textures[NORTH]->pixels);
			free(game->textures[NORTH]);
		}
		if (game->textures[SOUTH])
		{
			free(game->textures[SOUTH]->pixels);
			free(game->textures[SOUTH]);
		}
		if (game->textures[EAST])
		{
			free(game->textures[EAST]->pixels);
			free(game->textures[EAST]);
		}
		if (game->textures[WEST])
		{
			free(game->textures[WEST]->pixels);
			free(game->textures[WEST]);
		}
	}
}

void	free_game(t_game *game)
{
	free(game->player);
	free(game->ray->wall_hit_x);
	free(game->ray->wall_hit_y);
	free(game->ray->ray_angles);
	free(game->ray->distances);
	free(game->ray->is_ray_facing_down);
	free(game->ray->is_ray_facing_up);
	free(game->ray->is_ray_facing_right);
	free(game->ray->is_ray_facing_left);
	free(game->ray->found_h_wall_hit);
	free(game->ray->found_v_wall_hit);
	free(game->ray->to_hit);
	free_textures(game);
	free(game->textures);
	free(game->ray);
	free(game);
}
