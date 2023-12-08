/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 10:41:37 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/08 10:42:12 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_win(t_game *game)
{
	mlx_close_window(game->mlx);
	free_game(game);
	exit(0);
}

void	error_msg(void)
{
	write(2, "Error\n", 6);
	exit(1);
}
