/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:04:22 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/07 13:27:30 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_vertical_interception(t_game *game, int i)
{
	game->ray->v_wall_hit_x = 0;
	game->ray->v_wall_hit_y = 0;
	game->ray->found_v_wall_hit[i] = false;
	game->ray->v_x_intercept = floor(game->player->x / TILE_SIZE) * TILE_SIZE;
	if (game->ray->is_ray_facing_right[i])
		game->ray->v_x_intercept += TILE_SIZE;
	else
		game->ray->v_x_intercept += 0;
	game->ray->v_y_intercept = game->player->y
		+ (game->ray->v_x_intercept - game->player->x)
		* tan(game->ray->ray_angles[i]);
	game->ray->x_step = TILE_SIZE;
	if (game->ray->is_ray_facing_left[i])
		game->ray->x_step *= -1;
	else
		game->ray->x_step *= 1;
	game->ray->y_step = TILE_SIZE * tan(game->ray->ray_angles[i]);
	if (game->ray->is_ray_facing_up[i] && game->ray->y_step > 0)
		game->ray->y_step *= -1;
	else
		game->ray->y_step *= 1;
	if (game->ray->is_ray_facing_down[i] && game->ray->y_step < 0)
		game->ray->y_step *= -1;
	else
		game->ray->y_step *= 1;
}

void	next_vertical_intercept(t_game *game, double next_v_xintercept,
	double next_v_yintercept, int i)
{
	next_v_xintercept = game->ray->v_x_intercept;
	next_v_yintercept = game->ray->v_y_intercept;
	while ((next_v_xintercept >= 0 && next_v_xintercept
			<= game->parse->map_w * TILE_SIZE)
		&& (next_v_yintercept >= 0 && next_v_yintercept
			<= game->parse->map_h * TILE_SIZE))
	{
		game->ray->x_check = next_v_xintercept;
		game->ray->y_check = next_v_yintercept;
		if (game->ray->is_ray_facing_left[i])
			game->ray->x_check--;
		if (is_wall(game, game->ray->x_check, game->ray->y_check) == 1)
		{
			game->ray->found_v_wall_hit[i] = true;
			game->ray->v_wall_hit_x = --next_v_xintercept;
			game->ray->v_wall_hit_y = --next_v_yintercept;
			break ;
		}
		else
		{
			next_v_xintercept += game->ray->x_step;
			next_v_yintercept += game->ray->y_step;
		}
	}
}

void	cast_vertical_rays(t_game *game, int i)
{
	double	next_v_xintercept;
	double	next_v_yintercept;

	next_v_xintercept = 0;
	next_v_yintercept = 0;
	get_direction(game, i);
	calculate_vertical_interception(game, i);
	next_vertical_intercept(game, next_v_xintercept, next_v_yintercept, i);
}
