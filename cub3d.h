/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:04:07 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/29 15:38:31 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "MLX42/include/MLX42/MLX42.h"
# include <ctype.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include <limits.h>

# define TILE_SIZE 32 
# define WINDOW_WIDTH 26 * TILE_SIZE
# define WINDOW_HEIGHT 7 * TILE_SIZE

# define WIN_W 1440
# define WIN_H 900
# define MINI_MAP 0.5

# define WALL_STRIP_WIDTH 1

# define NORTH 0
# define SOUTH 1
# define WEST  2
# define EAST  3

typedef struct s_player
{
	double	x;
	double	y;
	double	radius;
	int		turn;
	int		walk;
	double	rotation_angle;
	double	move_speed;
	double	rotation_speed;
	double	fov_angle;
}	t_player;

typedef struct s_ray
{
	double	num_rays;
	double	*wall_hit_x;
	double	*wall_hit_y;
	double	*ray_angles;
	double	*distances;
	bool	*is_ray_facing_down;
	bool	*is_ray_facing_up;
	bool	*is_ray_facing_right;
	bool	*is_ray_facing_left;
	double	ray_angle;
	double	h_x_intercept;
	double	h_y_intercept;
	double	v_x_intercept;
	double	v_y_intercept;
	double	x_check;
	double	y_check;
	double	x_step;
	double	y_step;
	double	h_wall_hit_x;
	double	h_wall_hit_y;
	double	v_wall_hit_x;
	double	v_wall_hit_y;
	bool	*found_h_wall_hit;
	bool	*found_v_wall_hit;
	bool	*to_hit;
}	t_ray;

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

typedef struct s_parse
{
	char	**map;
	int		map_h;
	int		map_w;
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	t_rgb	*rgb;
}	t_parse;

typedef struct s_game
{
	void			*mlx;
	void			*mlx_win;
	t_player		*player;
	t_ray			*ray;
	t_parse			*parse;
	mlx_texture_t	**textures;
	mlx_image_t		*img;
}	t_game;

// movements.c
void	move_down(t_game *game, double move_step);
void	move_up(t_game *game, double move_step);
void	move_left(t_game *game, double move_step);
void	move_right(t_game *game, double move_step);

// key_hooks.c
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);
void	ft_hook(void *param);

// cast_rays.c
void	get_direction(t_game *game, int i);
void	check_distance(t_game *game, double h_distance, 
			double v_distance, int i);
void	cast_v_h_rays(t_game *game, int i);
void	cast_rays(t_game *game);

// ft_draw.c
void	draw_sky(t_game *game);
void	draw_floor(t_game *game);
void	draw(void *param);


// cast_horizontal.c
void	calculate_horizontal_interception(t_game *game, int i);
void	next_horizontal_intercept(t_game *game, double next_h_xintercept,
			double next_h_yintercept, int i);
void	cast_horizontal_rays(t_game *game, int i);

// cast_verticl.c
void	calculate_vertical_interception(t_game *game, int i);
void	next_vertical_intercept(t_game *game, double next_v_xintercept,
			double next_v_yintercept, int i);
void	cast_vertical_rays(t_game *game, int i);

// helpers.c
int		ft_strcmp(char *s1, char *s2);
double	normalize_angle(double angle);
double	distance_between_points(double x1, double y1, double x2, double y2);
int32_t	ft_rgba(int32_t r, int32_t g, int32_t b, int32_t a);
void	draw_rect(t_game *game, int x, int height, int color);

// init.c
void	init_rays(t_ray *ray);
void	ft_game(t_game *game);
void	init_player(t_player *player);

int		draw_player(t_game *game);
void	draw_line(t_game *game, int x0, int y0, int x1, int y1, int color);
void	get_player_position(t_player *player);
int		is_wall(double x, double y);
void	draw_textures(t_game *game, int i, double wall_strip_height, int direction);
void	projectd_wall(t_game *game);
void	draw_square(t_game *game, int x, int y, int color);
void	draw_wall(t_game *game);
void	draw_map(t_game *game);
int		close_win(t_game *game);

#endif