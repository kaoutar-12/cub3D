/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:56:58 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/30 09:44:36 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_down(t_game *game, double move_step)
{
	double	new_player_x;
	double	new_player_y;

	game->player->walk = -1;
	new_player_x = game->player->x + 
		cos(game->player->rotation_angle) * move_step;
	new_player_y = game->player->y + 
		sin(game->player->rotation_angle) * move_step;
	if (is_wall(new_player_x, new_player_y) == 0)
	{
		game->player->x = new_player_x;
		game->player->y = new_player_y;
	}
}

void	move_up(t_game *game, double move_step)
{
	double	new_player_x;
	double	new_player_y;

	game->player->walk = 1;
	new_player_x = game->player->x + 
		cos(game->player->rotation_angle) * move_step;
	new_player_y = game->player->y + 
		sin(game->player->rotation_angle) * move_step;
	if (is_wall(new_player_x, new_player_y) == 0)
	{
		game->player->x = new_player_x;
		game->player->y = new_player_y;
	}
}

void	move_left(t_game *game, double move_step)
{
	double	new_player_x;
	double	new_player_y;

	game->player->walk = -1;
	new_player_x = game->player->x + 
		cos(game->player->rotation_angle - M_PI_2) * move_step;
	new_player_y = game->player->y + 
		sin(game->player->rotation_angle - M_PI_2) * move_step;
	if (is_wall(new_player_x, new_player_y) == 0)
	{
		game->player->x = new_player_x;
		game->player->y = new_player_y;
	}
}

void	move_right(t_game *game, double move_step)
{
	double	new_player_x;
	double	new_player_y;

	game->player->walk = -1;
	new_player_x = game->player->x + 
		cos(game->player->rotation_angle + M_PI_2) * move_step;
	new_player_y = game->player->y + 
		sin(game->player->rotation_angle + M_PI_2) * move_step;
	if (is_wall(new_player_x, new_player_y) == 0)
	{
		game->player->x = new_player_x;
		game->player->y = new_player_y;
	}
}
