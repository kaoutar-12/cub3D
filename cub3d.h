/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:04:07 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/27 13:04:53 by kmouradi         ###   ########.fr       */
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
#include <stdbool.h>
#include <math.h>
#include <limits.h>

#define TILE_SIZE 32 
#define WINDOW_WIDTH 26 * TILE_SIZE
#define WINDOW_HEIGHT 7 * TILE_SIZE

#define WIN_W 1920
#define WIN_H 1080
#define MINI_MAP 0.5

#define FOV_ANGLE (60 * (M_PI / 360))
// #define NUM_RAYS 500
#define WALL_STRIP_WIDTH 1
#define NUM_RAYS WIN_W / WALL_STRIP_WIDTH

// /Users/kmouradi/homebrew

#define NORTH "NO"
#define SOUTH "SO"
#define WEST  "WE"
#define EAST  "EA"

typedef struct s_player
{
	double x ;
	double y ;
	double radius ;//= 3;

	int turn ;//= 0;// ig ankhedm biha f left o right 
	// -1 if left , +1 if right
	int walk ;//= 0;// ohadi fl qedam ola lor 
	// -1 if back , +1 if front
	
	double rotation_angle ;//= PI / 2; 
	// the angle that the player is looking at
	
	double move_speed ;//= 2.0; 
	// how fast or slow the player move
	
	double rotation_speed ;//= 2 * (PI / 180);
	// how fast or slow the player rotate

} t_player;

typedef struct s_ray
{
    double  *wall_hit_x;
    double  *wall_hit_y;
    double  *ray_angles;
    double  *distances;
    bool    *is_ray_facing_down;
    bool    *is_ray_facing_up;
    bool    *is_ray_facing_right;
    bool    *is_ray_facing_left;
    double  ray_angle;
    double  h_x_intercept;
    double  h_y_intercept;
    double  v_x_intercept;
    double  v_y_intercept;
    double  x_check;
    double  y_check;
    double  x_step;
    double  y_step;
    double  h_wall_hit_x;
    double  h_wall_hit_y;
    double  v_wall_hit_x;
    double  v_wall_hit_y;
    bool    *found_h_wall_hit;
    bool    *found_v_wall_hit;
    bool    *to_hit;
    bool    flag;
    
}t_ray;

typedef struct s_game
{
    void *mlx;
    void *mlx_win;
    t_player *player;
    t_ray *ray;
    mlx_image_t	*img;
} t_game;

void    get_direction(t_game *game, int i);
void    cast_horizontal_rays(t_game *game, int i);
void    cast_vertical_rays(t_game *game, int i);
double  distance_between_points(double x1, double y1, double x2, double y2);
void    cast_v_h_rays(t_game *game, int i);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void    cast_rays(t_game *game);
void    draw_sky(t_game *game);
void    draw_floor(t_game *game);
void    draw(void *param);
void    draw_rect(t_game *game, int x, int y, int width, int height, int color);
int     draw_player(t_game *game);
void    draw_line(t_game *game, int x0, int y0, int x1, int y1, int color);
void    get_player_position(t_player *player);
int     isWall(double x, double y) ;
void    draw_textures(t_game *game, int i, double wall_strip_height, char *direction);
void    projectd_wall(t_game *game);
void    draw_wall(t_game *game, int x, int y, int size, int color);
void    draw_wall2(t_game *game);
void    draw_map(t_game *game);
void    ft_game(t_game *game);
int     ft_strcmp(char *s1, char *s2);
void    ft_hook(void* param);
double  normalize_angle(double angle);
int     close_win(t_game *game);
void    init_player(t_player *player);
void    init_rays(t_ray *ray);


#endif