/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:06:09 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/08 10:42:09 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_game *game, double x, double y)
{
	int	mapindex_x;
	int	mapindex_y;

	mapindex_x = floor(x / TILE_SIZE);
	mapindex_y = floor(y / TILE_SIZE);
	if (game->parse->map[mapindex_y][mapindex_x] == '1')
		return (1);
	else
		return (0);
}

uint32_t	get_pixel_color(mlx_texture_t *texture, uint32_t x, uint32_t y)
{
	int			index;
	uint32_t	color;

	if (x < texture->width || x >= 0 || y < texture->height || y >= 0)
	{
		index = (y * texture->width + x) * texture->bytes_per_pixel;
		color = ft_rgba(texture->pixels[index], texture->pixels[index + 1],
				texture->pixels[index + 2], texture->pixels[index + 3]);
	}
	else
		color = ft_rgba(0, 0, 0, 255);
	return (color);
}

void	draw_textures(t_game *game, int i,
	double wall_strip_height, int direction)
{
	double		init_x;
	double		init_y;
	double		y;
	uint32_t	texture_x;
	uint32_t	texture_y;

	if (direction == NORTH || direction == SOUTH)
		init_x = (int)game->ray->wall_hit_x[i] % TILE_SIZE;
	else
		init_x = (int)game->ray->wall_hit_y[i] % TILE_SIZE;
	texture_x = init_x * (game->textures[direction]->width / TILE_SIZE);
	init_y = (WIN_H / 2) - (wall_strip_height / 2);
	y = init_y;
	while (y < (WIN_H / 2) + (wall_strip_height / 2))
	{
		if (i >= 0 && i < WIN_W && y >= 0 && y < WIN_H)
		{
			texture_y = (y - init_y) * (game->textures[direction]->height
					/ wall_strip_height);
			mlx_put_pixel(game->img, i, y,
				get_pixel_color(game->textures[direction],
					texture_x, texture_y));
		}
		y++;
	}
}

void	projectd_wall(t_game *game)
{
	int		i;
	double	correct_wall_distance;
	double	distance_projection_plane;
	double	wall_strip_height;

	i = 0;
	while (i < game->ray->num_rays)
	{
		correct_wall_distance = game->ray->distances[i]
			* cos(game->ray->ray_angles[i] - game->player->rotation_angle);
		distance_projection_plane = (WIN_W / 2)
			/ tan(game->player->fov_angle / 2);
		wall_strip_height = (TILE_SIZE / correct_wall_distance)
			* distance_projection_plane;
		if (game->ray->is_ray_facing_up[i] && game->ray->to_hit[i] == false)
			draw_textures(game, i, wall_strip_height, NORTH);
		if (game->ray->is_ray_facing_down[i] && game->ray->to_hit[i] == false)
			draw_textures(game, i, wall_strip_height, SOUTH);
		if (game->ray->is_ray_facing_left[i] && game->ray->to_hit[i] == true)
			draw_textures(game, i, wall_strip_height, EAST);
		if (game->ray->is_ray_facing_right[i] && game->ray->to_hit[i] == true)
			draw_textures(game, i, wall_strip_height, WEST);
		i++;
	}
}
