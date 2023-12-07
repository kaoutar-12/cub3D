/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:00:28 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/07 09:48:39 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player)
{
	player->fov_angle = 90 * (M_PI / 360);
	player->radius = 4;
	player->turn = 0;
	player->walk = 0;
	player->rotation_angle = M_PI / 2;
	player->move_speed = 2.0;
	if (player->move_speed > WIN_H || player->move_speed > WIN_W)
		player->move_speed = 2.0;
	player->rotation_speed = 3 * (M_PI / 180);
	get_player_position(player);
}

void	init_textures(t_game *game)
{
	game->textures = malloc(sizeof(mlx_texture_t) * 4);
	game->textures[NORTH] = mlx_load_png("mandatory/textures/north.png");
	game->textures[SOUTH] = mlx_load_png("mandatory/textures/north.png");
	game->textures[WEST] = mlx_load_png("mandatory/textures/north.png");
	game->textures[EAST] = mlx_load_png("mandatory/textures/north.png");
	if (!game->textures[NORTH] || !game->textures[SOUTH] ||
		!game->textures[WEST] || !game->textures[EAST])
	{
		write(2, "Error\n", 6);
		exit(1);
	}
}

void	ft_game(t_game *game)
{
	game->mlx = mlx_init(WIN_W, WIN_H, "Cub3d", false);
	if (!game->mlx)
		write(2, "Error\n", 6); 
	game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	init_textures(game);
	mlx_loop_hook(game->mlx, draw, game);
	mlx_loop_hook(game->mlx, ft_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}

void	init_rays(t_ray *ray)
{
	ray->num_rays = WIN_W / WALL_STRIP_WIDTH;
	ray->wall_hit_x = malloc(sizeof(double) * ray->num_rays);
	ray->wall_hit_y = malloc(sizeof(double) * ray->num_rays);
	ray->ray_angles = malloc(sizeof(double) * ray->num_rays);
	ray->distances = malloc(sizeof(double) * ray->num_rays);
	ray->is_ray_facing_down = malloc(sizeof(double) * ray->num_rays);
	ray->is_ray_facing_up = malloc(sizeof(double) * ray->num_rays);
	ray->is_ray_facing_right = malloc(sizeof(double) * ray->num_rays);
	ray->is_ray_facing_left = malloc(sizeof(double) * ray->num_rays);
	ray->found_h_wall_hit = malloc(sizeof(bool) * ray->num_rays);
	ray->found_v_wall_hit = malloc(sizeof(bool) * ray->num_rays);
	ray->to_hit = malloc(sizeof(bool) * ray->num_rays);
	ray->ray_angle = 0;
}
