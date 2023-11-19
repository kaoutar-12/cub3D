/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 10:46:55 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/19 11:27:06 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>
# include <fcntl.h>
# include <mlx.h>
# define PI 3.14159265358979323846


typedef struct s_data{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;



typedef struct s_player
{
	double x ;//= game->width / 2;
	double y ;//= game->height / 2;
	double radius ;//= 3;
	int turn ;//= 0;
	int walk ;//= 0;
	double rotation_angle ;//= PI / 2;
	double move_speed ;//= 2.0;
	double rotation_speed ;//= 2 * (PI / 180);
} t_player;

typedef struct s_game
{
    void *mlx;
    void *mlx_win;
    t_data *data;
    t_player *player;
} t_game;


#endif