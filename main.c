/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:05:03 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/23 09:05:35 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player(t_player *player) {
	player->radius = 2;
	player->turn = 0;
	player->walk = 0;
	player->rotation_angle = M_PI / 2;
	player->move_speed = 2.0;
	player->rotation_speed = 2 * (M_PI / 180);
    get_player_position(player);
}

int main()
{
    t_game *game;
    t_player *player;
    t_data *data;
    game = malloc(sizeof(t_game));
    player = malloc(sizeof(t_player));
    data = malloc(sizeof(t_data));
    init_player(player);
    game->player = player;
    game->data = data;
    ft_game(game);
}