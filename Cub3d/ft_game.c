/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:06:09 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/05 18:55:16 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// char *map[] = 
// {
// "1111111111111111111111111",
// "1P00000000000000000000001",
// "1000000000000000000000001",
// "1000000000000000000000001",
// "1000000001010010000000001",
// "1000000000000000000000001",
// "1111111111011111111111111",
// "1111111111011111111111111",
// "1000000000000000000000001",
// "1000000000000000000000001",
// "1000000000000000000000001",
// "1000000001010010000000001",
// "1000000000000000000000001",
// "1111111111111111111111111",
// };

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

void draw_textures(t_game *game, int i, double wall_strip_height, char *direction)
{
    if (!ft_strcmp(direction, "NO"))
        draw_rect(game, i * WALL_STRIP_WIDTH,
			wall_strip_height, ft_rgba(0, 97, 51, 255));
    if (!ft_strcmp(direction, "SO"))
        draw_rect(game, i * WALL_STRIP_WIDTH,
			wall_strip_height, ft_rgba(0, 94, 97, 255));
    if (!ft_strcmp(direction, "EA")) 
        draw_rect(game, i * WALL_STRIP_WIDTH,
			wall_strip_height, ft_rgba(97, 0, 9, 255));
    if (!ft_strcmp(direction, "WE"))
        draw_rect(game, i * WALL_STRIP_WIDTH,
			wall_strip_height, ft_rgba(72, 0, 97, 255));
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
		correct_wall_distance = game->ray->distances[i] * 
			cos(game->ray->ray_angles[i] - game->player->rotation_angle);
		distance_projection_plane = (WIN_W / 2) / tan(game->player->fov_angle / 2);
		wall_strip_height = (TILE_SIZE / correct_wall_distance)
			* distance_projection_plane;
		if (wall_strip_height >= WIN_H)
			wall_strip_height = WIN_H;
		if (game->ray->is_ray_facing_up[i] && game->ray->to_hit[i] == false)
			draw_textures(game, i, wall_strip_height, "NO");
		if (game->ray->is_ray_facing_down[i] && game->ray->to_hit[i] == false)
			draw_textures(game, i, wall_strip_height, "SO");
		if (game->ray->is_ray_facing_left[i] && game->ray->to_hit[i] == true)
			draw_textures(game, i, wall_strip_height, "EA");
		if (game->ray->is_ray_facing_right[i] && game->ray->to_hit[i] == true)
			draw_textures(game, i, wall_strip_height, "WE");
		i++;
	}
}

void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = TILE_SIZE * MINI_MAP;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_put_pixel(game->img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

//TODO change 7 and 26 
void	draw_wall(t_game *game)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < game->parse->map_h)
	{
		j = 0;
		while (j < game->parse->map_w - 1)
		{
			x = j * TILE_SIZE;
			y = i * TILE_SIZE;
			if (game->parse->map[i][j] == '1')
				draw_square(game, x * MINI_MAP,
					y * MINI_MAP, ft_rgba(255, 255, 255, 255));
			j++;
		}
		i++;
	}
}

//TODO change 7 and 26 
void	draw_map(t_game *game)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < game->parse->map_h)
	{
		j = 0;
		while (j < game->parse->map_w - 1)
		{
			x = j * TILE_SIZE;
			y = i * TILE_SIZE;
			draw_square(game, x * MINI_MAP, y * MINI_MAP,
				ft_rgba(0, 0, 0, 255));
			j++;
		}
		i++;
	}
}
