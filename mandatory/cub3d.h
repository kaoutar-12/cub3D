/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:04:07 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/08 18:06:09 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "../libraries/MLX42/include/MLX42/MLX42.h"
# include <ctype.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include <limits.h>
# include "../libraries/libft/libft.h"
# include "../libraries/gnl/get_next_line.h"

# define TILE_SIZE 64 
# define WINDOW_WIDTH 33 * TILE_SIZE
# define WINDOW_HEIGHT 14 * TILE_SIZE

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

typedef struct s_rgb_f
{
	int	red;
	int	green;
	int	blue;
}	t_rgb_f;

typedef struct s_rgb_c
{
	int	red;
	int	green;
	int	blue;
}	t_rgb_c;

typedef struct s_parse
{
	char	**map;
	char	**actual_map;
	int		player_x;
	int		player_y;
	int		player_direction;
	int		map_h;
	int		map_w;
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	t_rgb_f	f_rgb;
	t_rgb_c	c_rgb;
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

typedef	struct	s_it
{
	int	i;
	int	j;
	int	k;
} t_it;

typedef	struct	s_rgb_data
{
	char	**rgb_f;
	char	**rgb_c;
} t_rgb_data;

typedef struct s_var_calc
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
} t_var_calc;


enum				e_directions
{
	NO,
	SO,
	WE,
	EA
};

enum				e_colors
{
	F = 5,
	C
};

void fun();

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
int		is_wall(t_game *game, double x, double y);
void	draw_textures(t_game *game, int i, double wall_strip_height, int direction);
void	projectd_wall(t_game *game);
void	draw_square(t_game *game, int x, int y, int color);
void	draw_wall(t_game *game);
void	draw_map(t_game *game);
int		close_win(t_game *game);
void	error_msg(void);
void	set_color3(t_parse *vars, t_rgb_data *rgb_data);


void	set_path(t_parse *vars, char **paths, t_it it);
void	map_operations(char *map_name, t_parse *vars);
void	set_map(t_parse *vars, int longest);
int		is_surrounded(t_parse *vars, int i, int j);
void	set_color(t_parse *vars, char **colors);
void	check_path(t_parse *vars, char **path);
void	surround_map(char **a_map, char **map);
void	set_data(t_parse *vars, char *arr);
void	set_map_size(t_parse *vars, int y);
void	check_calc(t_var_calc	*calc);
int		detect_type(char *element);
char	**set_color2(char *color);
char	*allocate_space(int size);
void	check_color(char **color);
void	check_array(char **array);
int		check_map2(t_parse *vars);
int		ft_chrstr(char *s, int c);
void	set_map2(t_parse *vars);
int		ft_my_atoi(char *color);
void	free_2d(char **data);
int		table_size(char **map);
void	*gc_malloc(int size);
void	garbage_collector(void	*ptr, int del);
void	custom_exit(int status);
void	check_player(char *map);
char	*read_map(int fd, t_parse *vars);
void	check_map(char *map, int length);

#endif