/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:09:07 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/28 12:27:08 by kmouradi         ###   ########.fr       */
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

// void	cast_horizontal_rays(t_game *game, int i)
// {
// 	double	next_h_xintercept;
// 	double	next_h_yintercept;

// 	next_h_xintercept = 0;
// 	next_h_yintercept = 0;
// 	get_direction(game, i);
// 	next_h_xintercept = game->ray->h_x_intercept;
// 	next_h_yintercept = game->ray->h_y_intercept;
// 	while ((next_h_xintercept >= 0 && next_h_xintercept <= WINDOW_WIDTH)
// 		&& (next_h_yintercept >= 0 && next_h_yintercept <= WINDOW_HEIGHT))
// 	{
// 		game->ray->x_check = next_h_xintercept;
// 		game->ray->y_check = next_h_yintercept;
// 		if (game->ray->is_ray_facing_up[i])
// 			game->ray->y_check--;
// 		if (is_wall(game->ray->x_check, game->ray->y_check) == 1)
// 		{
// 			game->ray->found_h_wall_hit[i] = true;
// 			game->ray->h_wall_hit_x = --next_h_xintercept;
// 			game->ray->h_wall_hit_y = --next_h_yintercept;
// 			break ;
// 		}
// 		else
// 		{
// 			next_h_xintercept += game->ray->x_step;
// 			next_h_yintercept += game->ray->y_step;
// 		}
// 	}
// }

// void	cast_vertical_rays(t_game *game, int i)
// {
// 	double	next_v_xintercept;
// 	double	next_v_yintercept;

// 	next_v_xintercept = 0;
// 	next_v_yintercept = 0;
// 	get_direction(game, i);
// }

double	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
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

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	cast_rays(t_game *game)
{
	int	i;

	game->ray->ray_angle = normalize_angle(game->player->rotation_angle) 
		- (FOV_ANGLE / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		game->player->rotation_angle = 
			normalize_angle(game->player->rotation_angle);
		game->ray->ray_angles[i] = game->ray->ray_angle;
		game->ray->ray_angle = normalize_angle(game->ray->ray_angle);
		cast_v_h_rays(game, i);
		draw_line(game, game->player->x * MINI_MAP, game->player->y * MINI_MAP,
			game->ray->wall_hit_x[i] * MINI_MAP, game->ray->wall_hit_y[i] 
			* MINI_MAP, ft_pixel(255, 0, 0, 255));
		game->ray->ray_angle += FOV_ANGLE / NUM_RAYS;
		i++;
	}
}

void	draw_sky(t_game *game)
{
	uint32_t	i;
	uint32_t	j;
	int			pixel_x;
	int			pixel_y;

	i = 0;
	while (i < game->img->width)
	{
		j = 0;
		while (j < game->img->height / 2)
		{
			pixel_x = i;
			pixel_y = j;
			mlx_put_pixel(game->img, pixel_x, pixel_y,
				ft_pixel(47, 177, 255, 255));
			j++;
		}
		i++;
	}
}

void	draw_floor(t_game *game)
{
	uint32_t	i;
	uint32_t	j;
	int			pixel_x;
	int			pixel_y;

	i = 0;
	while (i < game->img->width)
	{
		j = game->img->height / 2;
		while (j < game->img->height)
		{
			pixel_x = i;
			pixel_y = j;
			mlx_put_pixel(game->img, pixel_x, pixel_y,
				ft_pixel(0, 147, 36, 255));
			j++;
		}
		i++;
	}
}

void	draw(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	draw_sky(game);
	draw_floor(game);
	projectd_wall(game);
	draw_map(game);
	draw_player(game);
	cast_rays(game);
	draw_wall(game);
}

void	draw_rect(t_game *game, int x, int y, int width, int height, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			mlx_put_pixel(game->img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

int	draw_player(t_game *game)
{
	int	y;
	int	x;
	int	draw_x;
	int	draw_y;

	y = -game->player->radius;
	while (y <= game->player->radius)
	{
		x = -game->player->radius;
		while (x <= game->player->radius)
		{
			if (x * x + y * y <= game->player->radius * game->player->radius)
			{
				draw_x = game->player->x;
				draw_y = game->player->y;
				mlx_put_pixel(game->img, draw_x * MINI_MAP,
					draw_y * MINI_MAP, ft_pixel(255, 0, 0, 255));
			}
			x++;
		}
		y++;
	}
	return (0);
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
