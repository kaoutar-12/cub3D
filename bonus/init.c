/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:00:28 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/10 13:20:08 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_player(t_player *player)
{
	player->fov_angle = 90 * (M_PI / 360);
	player->radius = 4;
	player->turn = 0;
	player->walk = 0;
	player->move_speed = 4.0;
	if (player->move_speed > WIN_H || player->move_speed > WIN_W)
		player->move_speed = 2.0;
	player->rotation_speed = 2 * (M_PI / 180);
}

void	init_textures(t_game *game)
{
	game->textures = malloc(sizeof(mlx_texture_t) * 4);
	game->textures[NORTH] = mlx_load_png(game->parse->no);
	game->textures[SOUTH] = mlx_load_png(game->parse->so);
	game->textures[WEST] = mlx_load_png(game->parse->we);
	game->textures[EAST] = mlx_load_png(game->parse->ea);
	if (!game->textures[NORTH] || !game->textures[SOUTH]
		|| !game->textures[WEST] || !game->textures[EAST])
		error_msg();
	game->shoot = false;
}

void	ft_game(t_game *game)
{
	game->mlx = mlx_init(WIN_W, WIN_H, "Cub3d", false);
	if (!game->mlx)
		error_msg();
	game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->img)
	{
		mlx_close_window(game->mlx);
		error_msg();
	}
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		error_msg();
	}
	init_textures(game);
	mlx_loop_hook(game->mlx, draw, game);
	mlx_loop_hook(game->mlx, ft_hook, game);
	mlx_cursor_hook(game->mlx, mouse_hook, game);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
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
