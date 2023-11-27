/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:09:07 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/27 10:55:16 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void get_direction(t_game *game, int i)
{
    if(game->ray->ray_angles[i] > 0 && game->ray->ray_angles[i] < M_PI)
        game->ray->is_ray_facing_down[i] = true;
    else
        game->ray->is_ray_facing_down[i] = false;
    game->ray->is_ray_facing_up[i] = !game->ray->is_ray_facing_down[i];

    if (game->ray->ray_angles[i] < 0.5 * M_PI || game->ray->ray_angles[i] > 1.5 * M_PI)
        game->ray->is_ray_facing_right[i] = true;
    else
        game->ray->is_ray_facing_right[i] = false;
    game->ray->is_ray_facing_left[i] = !game->ray->is_ray_facing_right[i];
}

void cast_horizontal_rays(t_game *game, int i)
{
    double next_h_xintercept;
    double next_h_yintercept;

    next_h_xintercept = 0;
    next_h_yintercept = 0;
    
    get_direction(game, i);
    game->ray->h_wall_hit_x = 0;
    game->ray->h_wall_hit_y = 0;
    game->ray->found_h_wall_hit[i] = false;
    game->ray->h_y_intercept = floor(game->player->y / TILE_SIZE) * TILE_SIZE;
    
    if (game->ray->is_ray_facing_down[i])
        game->ray->h_y_intercept += TILE_SIZE;
    else
        game->ray->h_y_intercept += 0;
    
    game->ray->h_x_intercept = game->player->x + (game->ray->h_y_intercept - game->player->y) / tan(game->ray->ray_angles[i]);
    game->ray->y_step = TILE_SIZE;
    
    if (game->ray->is_ray_facing_up[i])
        game->ray->y_step *= -1;
    else
        game->ray->y_step *= 1;
        game->ray->x_step = TILE_SIZE / tan(game->ray->ray_angles[i]);
    if (game->ray->is_ray_facing_left[i] && game->ray->x_step > 0)
        game->ray->x_step *= -1;
    else
        game->ray->x_step *= 1;
    
    if (game->ray->is_ray_facing_right[i] && game->ray->x_step < 0)
        game->ray->x_step *= -1;
    else
        game->ray->x_step *= 1;

    next_h_xintercept = game->ray->h_x_intercept;
    next_h_yintercept = game->ray->h_y_intercept;
    
    while((next_h_xintercept >= 0 && next_h_xintercept <= WINDOW_WIDTH)
        && (next_h_yintercept >= 0 && next_h_yintercept <= WINDOW_HEIGHT))
    {
        game->ray->x_check = next_h_xintercept;
        game->ray->y_check = next_h_yintercept;
        if (game->ray->is_ray_facing_up[i])
            game->ray->y_check--;
        if (isWall(game->ray->x_check, game->ray->y_check) == 1)
        {
            game->ray->found_h_wall_hit[i] = true;
            game->ray->h_wall_hit_x = --next_h_xintercept;
            game->ray->h_wall_hit_y = --next_h_yintercept;
            // printf("X---> %f\n", game->ray->h_wall_hit_x);
            // printf("Y---> %f\n", game->ray->h_wall_hit_y);
            // draw_line(game, game->player->x * MINI_MAP, game->player->y * MINI_MAP, game->ray->h_wall_hit_x * MINI_MAP, game->ray->h_wall_hit_y * MINI_MAP, ft_pixel(255, 0, 0, 255));
            break;
        }
        else
        {
            next_h_xintercept += game->ray->x_step;
            next_h_yintercept += game->ray->y_step;
        }
    }

}

void cast_vertical_rays(t_game *game, int i)
{
    double next_v_xintercept;
    double next_v_yintercept;
    
    next_v_xintercept = 0;
    next_v_yintercept = 0;

    get_direction(game, i);
    game->ray->v_wall_hit_x = 0;
    game->ray->v_wall_hit_y = 0;
    game->ray->found_v_wall_hit[i] = false;
    game->ray->v_x_intercept = floor(game->player->x / TILE_SIZE) * TILE_SIZE;

    if(game->ray->is_ray_facing_right[i])
        game->ray->v_x_intercept += TILE_SIZE;
    else
        game->ray->v_x_intercept += 0;
    
    game->ray->v_y_intercept = game->player->y + (game->ray->v_x_intercept - game->player->x) * tan(game->ray->ray_angles[i]);
    game->ray->x_step = TILE_SIZE;
    // printf("X---> %f\n", game->player->x);
    // printf("Y---> %f\n", game->player->y);

    if (game->ray->is_ray_facing_left[i])
        game->ray->x_step *= -1;
    else
        game->ray->x_step *= 1;
    
    game->ray->y_step = TILE_SIZE * tan(game->ray->ray_angles[i]);
    
    if (game->ray->is_ray_facing_up[i] && game->ray->y_step > 0)
        game->ray->y_step *= -1;
    else
        game->ray->y_step *= 1;

    if (game->ray->is_ray_facing_down[i] && game->ray->y_step < 0)
        game->ray->y_step *= -1;
    else
        game->ray->y_step *= 1;
    
    next_v_xintercept = game->ray->v_x_intercept;
    next_v_yintercept = game->ray->v_y_intercept;


    while((next_v_xintercept >= 0 && next_v_xintercept <= WINDOW_WIDTH) 
        && (next_v_yintercept >= 0 && next_v_yintercept <= WINDOW_HEIGHT))
    {
        game->ray->x_check = next_v_xintercept;
        game->ray->y_check = next_v_yintercept;
        if (game->ray->is_ray_facing_left[i])
            game->ray->x_check--;
        if(isWall(game->ray->x_check, game->ray->y_check) == 1 )
        {
            game->ray->found_v_wall_hit[i] = true;
            game->ray->v_wall_hit_x = --next_v_xintercept;
            game->ray->v_wall_hit_y = --next_v_yintercept;
            // printf("X---> %f\n", game->ray->v_wall_hit_x);
            // printf("Y---> %f\n", game->ray->v_wall_hit_y);
            // draw_line(game, game->player->x * MINI_MAP, game->player->y * MINI_MAP, game->ray->v_wall_hit_x * MINI_MAP, game->ray->v_wall_hit_y * MINI_MAP, ft_pixel(255, 0, 0, 255));
            break;
        }
        else
        {
            next_v_xintercept += game->ray->x_step;
            next_v_yintercept += game->ray->y_step;
        }
    }
}

double distance_between_points(double x1, double y1, double x2, double y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void cast_v_h_rays(t_game *game, int i)
{
    // cast horizontal rays
    cast_vertical_rays(game, i);
    cast_horizontal_rays(game, i);
    // cast vertical rays
    // calculate the distance

    double h_distance = 0;
    double v_distance = 0;

    if(game->ray->found_h_wall_hit[i])
        h_distance = distance_between_points(game->player->x, game->player->y, game->ray->h_wall_hit_x, game->ray->h_wall_hit_y);
    else
        h_distance = INT_MAX;

    if(game->ray->found_v_wall_hit[i])
        v_distance = distance_between_points(game->player->x, game->player->y, game->ray->v_wall_hit_x, game->ray->v_wall_hit_y);
    else
        v_distance = INT_MAX;
    
    if(h_distance <= v_distance)
    {
        game->ray->wall_hit_x[i] = game->ray->h_wall_hit_x;
        game->ray->wall_hit_y[i] = game->ray->h_wall_hit_y;
        game->ray->distances[i] = h_distance;
    }
    else
    {
        game->ray->wall_hit_x[i] = game->ray->v_wall_hit_x;
         game->ray->wall_hit_y[i] = game->ray->v_wall_hit_y;
        game->ray->distances[i] = v_distance;
    }

    // if(v_distance < h_distance)
    //     game->ray->to_hit[i] = true;
    // else
    //     game->ray->to_hit[i] = false;
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void cast_rays(t_game *game)
{
    game->ray->ray_angle = normalize_angle(game->player->rotation_angle) - (FOV_ANGLE / 2);
    
    int i = 0;
    while(i < NUM_RAYS)
    {
        game->player->rotation_angle = normalize_angle(game->player->rotation_angle);
        game->ray->ray_angles[i] = game->ray->ray_angle;
        game->ray->ray_angle = normalize_angle(game->ray->ray_angle);
        cast_v_h_rays(game, i);
        draw_line(game, game->player->x * MINI_MAP, game->player->y * MINI_MAP,
            game->ray->wall_hit_x[i] * MINI_MAP, game->ray->wall_hit_y[i] * MINI_MAP, ft_pixel(255,0,0,255));
        game->ray->ray_angle += FOV_ANGLE / NUM_RAYS;
        i++;
    }
}

void draw_sky(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->img->width)
    {
        j = 0;
        while (j < game->img->height / 2)
        {
            int pixel_x = i;
            int pixel_y = j;
            mlx_put_pixel(game->img, pixel_x, pixel_y, ft_pixel(0,0,0, 255));
            j++;
        }
        i++;
    }
}

void    draw_floor(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->img->width)
    {
        j = game->img->height / 2;
        while (j < game->img->height)
        {
            int pixel_x = i;
            int pixel_y = j;
            mlx_put_pixel(game->img, pixel_x, pixel_y, ft_pixel(0,0,0, 255));
            j++;
        }
        i++;
    }
}

void draw(void *param)
{
    t_game *game = (t_game *)param;
    draw_sky(game);
    draw_floor(game);
    projectd_wall(game);
    draw_map(game);
    draw_player(game);
    cast_rays(game);
    draw_wall2(game);
}

void draw_rect(t_game *game, int x, int y, int width, int height, int color)
{
for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // mlx_pixel_put(game->mlx, game->mlx_win, x + i, y + j, color);
            mlx_put_pixel(game->img, x + i, y + j, color);
        }
    }
}

int draw_player(t_game *game)
{
    // int playerRadius = 10; // Adjust the radius as needed
    
    for (int y = -game->player->radius; y <= game->player->radius; y++)
    {
        for (int x = -game->player->radius; x <= game->player->radius; x++)
        {
            // Check if the pixel is inside the circular boundary
            if (x * x + y * y <= game->player->radius * game->player->radius)
            {
                // Calculate the actual coordinates in the game window
                int drawX = game->player->x + x;
                int drawY = game->player->y + y;
                // Draw the pixel
                mlx_put_pixel(game->img, drawX * MINI_MAP, drawY * MINI_MAP, ft_pixel(255,0,0,255));
            }
        }
    }
    return (0);
}

void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        // mlx_pixel_put(game->mlx, game->mlx_win, x0, y0, color);
        mlx_put_pixel(game->img, x0, y0, color);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

// void draw_pixel(t_game *game, int x, int y, int color)
// {
//     for (int j = 0; j < TILE_SIZE; j++)
//     {
//         for (int i = 0; i < TILE_SIZE; i++)
//         {
//             int pixel_index = (y + j) * game->data->line_length + (x + i) * (game->data->bits_per_pixel / 8);

//             game->data->addr[pixel_index] = (color >> 16) & 0xFF;   
//             game->data->addr[pixel_index + 1] = (color >> 8) & 0xFF; 
//             game->data->addr[pixel_index + 2] = color & 0xFF;        
//         }
//     }
// }

// int draw_wall(t_game *game)
// {
//     int i = 0;
//     int j = 0;
//     while(map[j])
//     {
//         i = 0;
//         while(map[j][i])
//         {
//             if (map[j][i] == '1') 
//                 draw_pixel(game, i * TILE_SIZE, j * TILE_SIZE, 0x808080);
//             else
//                 draw_pixel(game, i * TILE_SIZE, j * TILE_SIZE, 0xFFFFFF);
//             i++;
//         }
//         j++;
//     }
//     return (0);
// }