/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 10:41:37 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/11 13:08:15 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	close_win(t_game *game)
{
	mlx_close_window(game->mlx);
	free_game(game);
	exit(0);
}

void	error_msg(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

void	free_sprites(t_game *game)
{
	if (game->sprite)
	{
		if (game->sprite[KNIFE])
		{
			free(game->sprite[KNIFE]->pixels);
			free(game->sprite[KNIFE]);
		}
		if (game->sprite[GUN])
		{
			free(game->sprite[GUN]->pixels);
			free(game->sprite[GUN]);
		}
		if (game->sprite[KNIFE_A])
		{
			free(game->sprite[KNIFE_A]->pixels);
			free(game->sprite[KNIFE_A]);
		}
		if (game->sprite[GUN_A])
		{
			free(game->sprite[GUN_A]->pixels);
			free(game->sprite[GUN_A]);
		}
	}
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
	free_sprites(game);
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
	free(game->sprite);
	free(game->ray);
	free(game);
}
