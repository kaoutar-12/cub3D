/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:06:09 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/29 14:04:18 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *map[] = 
{
"1111111111111111111111111",
"1000000000000000000000001",
"1000000000000000000000001",
"1000000000000000000000001",
"1000000001010010000000001",
"1000P00000000000000000001",
"1111111111111111111111111"
};

void	get_player_position(t_player *player)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == 'P')
			{
				player->x = i * TILE_SIZE + TILE_SIZE / 2;
				player->y = j * TILE_SIZE + TILE_SIZE / 2;
				return ;
			}
			i++;
		}
		j++;
	}
}

int	is_wall(double x, double y)
{
	int	mapindex_x;
	int	mapindex_y;

	mapindex_x = floor(x / TILE_SIZE);
	mapindex_y = floor(y / TILE_SIZE);
	if (map[mapindex_y][mapindex_x] == '1')
		return (1);
	else
		return (0);
}

uint32_t	get_pixel_color(mlx_texture_t *ll, int x, int y)
{
	int index;
	uint32_t color;

	index = (y * ll->width + x) * ll->bytes_per_pixel;
	color = ft_rgba(ll->pixels[index],ll->pixels[index + 1],
			ll->pixels[index + 2],ll->pixels[index + 3]);

	return (color);
}

void	draw_textures(t_game *game, int i,
	double wall_strip_height, char *direction)
{
	double	init_x;
	double	init_y;
	double	tex_x;
	double	y;
	double	tex_y;

	if (game->ray->to_hit[i] == false)
		init_x = remainder(game->ray->wall_hit_x[i], TILE_SIZE);
	else
		init_x = remainder(game->ray->wall_hit_y[i], TILE_SIZE);

	tex_x = init_x * (game->no_texture->width / TILE_SIZE);
	init_y = (WIN_H / 2) - (wall_strip_height / 2);
	y = init_y;
	while (y < (WIN_H / 2) + (wall_strip_height / 2))
	{
		tex_y = (y - init_y) * (game->no_texture->height / wall_strip_height);
		mlx_put_pixel(game->img, i, y, get_pixel_color(game->no_texture, tex_x, tex_y));
		y++;
	}
	if (!ft_strcmp(direction, SOUTH))
		draw_rect(game, i * WALL_STRIP_WIDTH, 
			wall_strip_height, ft_rgba(0, 94, 97, 255));
	if (!ft_strcmp(direction, EAST)) 
		draw_rect(game, i * WALL_STRIP_WIDTH, 
			wall_strip_height, ft_rgba(97, 0, 9, 255));
	if (!ft_strcmp(direction, WEST))
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
	while (i < 7)
	{
		j = 0;
		while (j < 26)
		{
			x = j * TILE_SIZE;
			y = i * TILE_SIZE;
			if (map[i][j] == '1')
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
	while (i < 7)
	{
		j = 0;
		while (j < 25)
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
