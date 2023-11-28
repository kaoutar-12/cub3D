/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:05:03 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/28 12:58:33 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player)
{
	player->radius = 4;
	player->turn = 0;
	player->walk = 0;
	player->rotation_angle = M_PI / 2;
	player->move_speed = 2.0;
	player->rotation_speed = 3 * (M_PI / 180);
	get_player_position(player);
}

void	ft_game(t_game *game)
{
	game->mlx = mlx_init(WIN_W, WIN_H, "Cub3d", false);
	if (!game->mlx)
		write(2, "Error\n", 6); 
	game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_loop_hook(game->mlx, draw, game);
	mlx_loop_hook(game->mlx, ft_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}

void	init_rays(t_ray *ray)
{
	ray->wall_hit_x = malloc(sizeof(double) * NUM_RAYS);
	ray->wall_hit_y = malloc(sizeof(double) * NUM_RAYS);
	ray->ray_angles = malloc(sizeof(double) * NUM_RAYS);
	ray->distances = malloc(sizeof(double) * NUM_RAYS);
	ray->is_ray_facing_down = malloc(sizeof(double) * NUM_RAYS);
	ray->is_ray_facing_up = malloc(sizeof(double) * NUM_RAYS);
	ray->is_ray_facing_right = malloc(sizeof(double) * NUM_RAYS);
	ray->is_ray_facing_left = malloc(sizeof(double) * NUM_RAYS);
	ray->found_h_wall_hit = malloc(sizeof(bool) * NUM_RAYS);
	ray->found_v_wall_hit = malloc(sizeof(bool) * NUM_RAYS);
	ray->to_hit = malloc(sizeof(bool) * NUM_RAYS);
	ray->ray_angle = 0;
}

int	main(void)
{
	t_game		*game;
	t_player	*player;
	t_ray		*ray;

	game = malloc(sizeof(t_game));
	player = malloc(sizeof(t_player));
	ray = malloc(sizeof(t_ray));
	init_rays(ray);
	init_player(player);
	game->player = player;
	game->ray = ray;
	ft_game(game);
}
