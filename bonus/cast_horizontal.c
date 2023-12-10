/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_horizontal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:04:13 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/08 10:55:05 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	calculate_horizontal_interception(t_game *game, int i)
{
	game->ray->h_wall_hit_x = 0;
	game->ray->h_wall_hit_y = 0;
	game->ray->found_h_wall_hit[i] = false;
	game->ray->h_y_intercept = floor(game->player->y / TILE_SIZE) * TILE_SIZE;
	if (game->ray->is_ray_facing_down[i])
		game->ray->h_y_intercept += TILE_SIZE;
	else
		game->ray->h_y_intercept += 0;
	game->ray->h_x_intercept = game->player->x
		+ (game->ray->h_y_intercept - game->player->y)
		/ tan(game->ray->ray_angles[i]);
	game->ray->y_step = TILE_SIZE;
	if (game->ray->is_ray_facing_up[i])
		game->ray->y_step *= -1;
	else
		game->ray->y_step *= 1;
	game->ray->x_step = TILE_SIZE / tan(game->ray->ray_angles[i]);
	if (game->ray->is_ray_facing_left[i] && game->ray->x_step > 0)
		game->ray->x_step *= -1;
	else
		game->ray->x_step *= 1;
	if (game->ray->is_ray_facing_right[i] && game->ray->x_step < 0)
		game->ray->x_step *= -1;
	else
		game->ray->x_step *= 1;
}

void	next_horizontal_intercept(t_game *game, double next_h_xintercept,
	double next_h_yintercept, int i)
{
	next_h_xintercept = game->ray->h_x_intercept;
	next_h_yintercept = game->ray->h_y_intercept;
	while ((next_h_xintercept >= 0 && next_h_xintercept
			<= game->parse->map_w * TILE_SIZE)
		&& (next_h_yintercept >= 0 && next_h_yintercept
			<= game->parse->map_h * TILE_SIZE))
	{
		game->ray->x_check = next_h_xintercept;
		game->ray->y_check = next_h_yintercept;
		if (game->ray->is_ray_facing_up[i])
			game->ray->y_check--;
		if (is_wall(game, game->ray->x_check, game->ray->y_check) == 1)
		{
			game->ray->found_h_wall_hit[i] = true;
			game->ray->h_wall_hit_x = --next_h_xintercept;
			game->ray->h_wall_hit_y = --next_h_yintercept;
			break ;
		}
		else
		{
			next_h_xintercept += game->ray->x_step;
			next_h_yintercept += game->ray->y_step;
		}
	}
}

void	cast_horizontal_rays(t_game *game, int i)
{
	double	next_h_xintercept;
	double	next_h_yintercept;

	next_h_xintercept = 0;
	next_h_yintercept = 0;
	get_direction(game, i);
	calculate_horizontal_interception(game, i);
	next_horizontal_intercept(game, next_h_xintercept, next_h_yintercept, i);
}
