/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:09:07 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/05 18:09:45 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_direction(t_game *game, int i)
{
	if (game->ray->ray_angles[i] > 0 && game->ray->ray_angles[i] < M_PI)
		game->ray->is_ray_facing_down[i] = true;
	else
		game->ray->is_ray_facing_down[i] = false;
	game->ray->is_ray_facing_up[i] = !game->ray->is_ray_facing_down[i];
	if (game->ray->ray_angles[i] < 0.5 * M_PI 
		|| game->ray->ray_angles[i] > 1.5 * M_PI)
		game->ray->is_ray_facing_right[i] = true;
	else
		game->ray->is_ray_facing_right[i] = false;
	game->ray->is_ray_facing_left[i] = !game->ray->is_ray_facing_right[i];
}

void	check_distance(t_game *game, double h_distance,
		double v_distance, int i)
{
	if (h_distance <= v_distance)
	{
		game->ray->wall_hit_x[i] = game->ray->h_wall_hit_x;
		game->ray->wall_hit_y[i] = game->ray->h_wall_hit_y;
		game->ray->distances[i] = h_distance;
	}
	else
	{
		game->ray->wall_hit_x[i] = game->ray->v_wall_hit_x;
		game->ray->wall_hit_y[i] = game->ray->v_wall_hit_y;
		game->ray->distances[i] = v_distance;
	}
	if (v_distance < h_distance)
		game->ray->to_hit[i] = true;
	else
		game->ray->to_hit[i] = false;
}

void	cast_v_h_rays(t_game *game, int i)
{
	double	h_distance;
	double	v_distance;

	cast_vertical_rays(game, i);
	cast_horizontal_rays(game, i);
	h_distance = 0;
	v_distance = 0;
	if (game->ray->found_h_wall_hit[i])
		h_distance = distance_between_points(game->player->x, game->player->y,
				game->ray->h_wall_hit_x, game->ray->h_wall_hit_y);
	else
		h_distance = INT_MAX;
	if (game->ray->found_v_wall_hit[i])
		v_distance = distance_between_points(game->player->x, game->player->y,
				game->ray->v_wall_hit_x, game->ray->v_wall_hit_y);
	else
		v_distance = INT_MAX;
	check_distance(game, h_distance, v_distance, i);
}

void	cast_rays(t_game *game)
{
	int	i;

	game->ray->ray_angle = normalize_angle(game->player->rotation_angle) 
		- (game->player->fov_angle / 2);
	i = 0;
	while (i < game->ray->num_rays)
	{
		game->player->rotation_angle = 
			normalize_angle(game->player->rotation_angle);
		game->ray->ray_angles[i] = game->ray->ray_angle;
		game->ray->ray_angle = normalize_angle(game->ray->ray_angle);
		cast_v_h_rays(game, i);
		draw_line(game, game->player->x * MINI_MAP, game->player->y * MINI_MAP,
			game->ray->wall_hit_x[i] * MINI_MAP, game->ray->wall_hit_y[i] 
			* MINI_MAP, ft_rgba(255, 0, 0, 255));
		game->ray->ray_angle += game->player->fov_angle / game->ray->num_rays;
		i++;
	}
}

//! REMOVE
void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		// mlx_pixel_put(game->mlx, game->mlx_win, x0, y0, color);
		mlx_put_pixel(game->img, x0, y0, color);

		if (x0 == x1 && y0 == y1)
			break;

		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}
