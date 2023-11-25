/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:04:07 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/25 10:31:12 by kmouradi         ###   ########.fr       */
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

#define TILE_SIZE 64 
#define WINDOW_WIDTH 26 * TILE_SIZE
#define WINDOW_HEIGHT 5 * TILE_SIZE

#define WIN_W 1920
#define WIN_H 1080
#define MINI_MAP 0.4

#define FOV_ANGLE (60 * (M_PI / 360))
// #define NUM_RAYS 500
#define WALL_STRIP_WIDTH 1
#define NUM_RAYS WIN_W / WALL_STRIP_WIDTH

// /Users/kmouradi/homebrew

typedef struct s_data{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

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
    double *wall_hit_x;
    double *wall_hit_y;
    double *ray_angles;
    double *distances;
    bool *is_ray_facing_down;
    bool *is_ray_facing_up;
    bool *is_ray_facing_right;
    bool *is_ray_facing_left;
    double ray_angle;
    double h_x_intercept;
    double h_y_intercept;
    double v_x_intercept;
    double v_y_intercept;
    double x_step;
    double y_step;
    double h_wall_hit_x;
    double h_wall_hit_y;
    double v_wall_hit_x;
    double v_wall_hit_y;
    bool *found_h_wall_hit;
    bool *found_v_wall_hit;
    bool *to_hit;
    bool flag;
    
}t_ray;

typedef struct s_game
{
    void *mlx;
    void *mlx_win;
    t_data *data;
    t_player *player;
    t_ray *ray;
} t_game;



// game fuctions

void ft_game(t_game *game);


// // keys functions

void ft_hook(void* param);
// int key_release(int keycode, t_game *game);
// int key_press(int keycode, t_game *game);
int close_win(t_game *game);

// // draw functions
void draw_map(t_game *game);

void draw(void *param);
// int draw_wall(t_game *game);
// void draw_pixel(t_game *game, int x, int y, int color);
int draw_player(t_game *game);
void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color);
void draw_rect(t_game *game, int x, int y, int width, int height, int color);

// // helper functions
int isWall(double x, double y);
void get_player_position(t_player *player);
double normalize_angle(double angle);
void projectd_wall(t_game *game);

#endif