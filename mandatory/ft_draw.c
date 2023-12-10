/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:36:09 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/07 13:28:28 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_sky(t_game *game)
{
	uint32_t	i;
	uint32_t	j;
	int			pixel_x;
	int			pixel_y;

	i = 0;
	while (i < game->img->width)
	{
		j = 0;
		while (j < game->img->height / 2)
		{
			pixel_x = i;
			pixel_y = j;
			mlx_put_pixel(game->img, pixel_x, pixel_y,
				ft_rgba(game->parse->c_rgb.red, game->parse->c_rgb.green,
					game->parse->c_rgb.blue, 255));
			j++;
		}
		i++;
	}
}

void	draw_floor(t_game *game)
{
	uint32_t	i;
	uint32_t	j;
	int			pixel_x;
	int			pixel_y;

	i = 0;
	while (i < game->img->width)
	{
		j = game->img->height / 2;
		while (j < game->img->height)
		{
			pixel_x = i;
			pixel_y = j;
			mlx_put_pixel(game->img, pixel_x, pixel_y,
				ft_rgba(game->parse->f_rgb.red, game->parse->f_rgb.green,
					game->parse->f_rgb.blue, 255));
			j++;
		}
		i++;
	}
}

void	draw(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	draw_sky(game);
	draw_floor(game);
	projectd_wall(game);
	cast_rays(game);
}
