/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:05:03 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/24 19:12:49 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// # include "MLX42/include/MLX42/MLX42_Int.h"

void init_player(t_player *player) {
	player->radius = 4;
	player->turn = 0;
	player->walk = 0;
	player->rotation_angle = M_PI / 2;
	player->move_speed = 4.0;
	player->rotation_speed = 3 * (M_PI / 180);
    get_player_position(player);
}

void init_rays(t_ray *ray)
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

int main()
{
    t_game *game;
    t_player *player;
    t_data *data;
    t_ray *ray;
    game = malloc(sizeof(t_game));
    player = malloc(sizeof(t_player));
    data = malloc(sizeof(t_data));
    ray = malloc(sizeof(t_ray));
    init_rays(ray);
    init_player(player);
    game->player = player;
    game->data = data;
    game->ray = ray;
    ft_game(game);
}