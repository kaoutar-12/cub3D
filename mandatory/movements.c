/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:56:58 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/08 11:14:37 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wall_close(t_game *game, double x, double y)
{
	double	new_x;
	double	new_y;

	new_x = x - 5;
	while (new_x <= x + 5)
	{
		new_y = y - 5;
		while (new_y <= y + 5)
		{
			if (is_wall(game, new_x, new_y) == 1)
				return (1);
			new_y++;
		}
		new_x++;
	}
	return (0);
}

void	move_down(t_game *game, double move_step)
{
	double	new_player_x;
	double	new_player_y;

	game->player->walk = 1;
	new_player_x = game->player->x
		- cos(game->player->rotation_angle) * move_step;
	new_player_y = game->player->y
		- sin(game->player->rotation_angle) * move_step;
	if (wall_close(game, new_player_x, new_player_y) == 0)
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
	new_player_x = game->player->x
		+ cos(game->player->rotation_angle) * move_step;
	new_player_y = game->player->y
		+ sin(game->player->rotation_angle) * move_step;
	if (wall_close(game, new_player_x, new_player_y) == 0)
	{
		game->player->x = new_player_x;
		game->player->y = new_player_y;
	}
}

void	move_left(t_game *game, double move_step)
{
	double	new_player_x;
	double	new_player_y;

	game->player->walk = 1;
	new_player_x = game->player->x
		+ cos(game->player->rotation_angle - M_PI_2) * move_step;
	new_player_y = game->player->y
		+ sin(game->player->rotation_angle - M_PI_2) * move_step;
	if (wall_close(game, new_player_x, new_player_y) == 0)
	{
		game->player->x = new_player_x;
		game->player->y = new_player_y;
	}
}

void	move_right(t_game *game, double move_step)
{
	double	new_player_x;
	double	new_player_y;

	game->player->walk = 1;
	new_player_x = game->player->x
		+ cos(game->player->rotation_angle + M_PI_2) * move_step;
	new_player_y = game->player->y
		+ sin(game->player->rotation_angle + M_PI_2) * move_step;
	if (wall_close(game, new_player_x, new_player_y) == 0)
	{
		game->player->x = new_player_x;
		game->player->y = new_player_y;
	}
}
