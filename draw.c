/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:09:07 by kmouradi          #+#    #+#             */
/*   Updated: 2023/11/23 15:33:47 by kmouradi         ###   ########.fr       */
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

    double x_to_check = next_h_xintercept;
    double y_to_check = next_h_yintercept;
    
    while((next_h_xintercept >= 0 && next_h_xintercept <= WINDOW_WIDTH)
        && (next_h_yintercept >= 0 && next_h_yintercept <= WINDOW_HEIGHT))
    {
        if (game->ray->is_ray_facing_up[i])
            y_to_check--;
        if (isWall(x_to_check, y_to_check) == 1)
        {
            game->ray->found_h_wall_hit[i] = true;
            game->ray->h_wall_hit_x = --next_h_xintercept;
            game->ray->h_wall_hit_y = --next_h_yintercept;
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

    double x_to_check = next_v_xintercept;
    double y_to_check = next_v_yintercept;

    while((next_v_xintercept >= 0 && next_v_xintercept <= WINDOW_WIDTH) 
        && (next_v_yintercept >= 0 && next_v_yintercept <= WINDOW_HEIGHT))
    {
        if (game->ray->is_ray_facing_left[i])
            x_to_check--;
        if(isWall(x_to_check, y_to_check) == 1 )
        {
            game->ray->found_v_wall_hit[i] = true;
            game->ray->v_wall_hit_x = --next_v_xintercept;
            game->ray->v_wall_hit_y = --next_v_yintercept;
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
    cast_horizontal_rays(game, i);
    // cast vertical rays
    cast_vertical_rays(game, i);
    // calculate the distance

    double h_distance = 0;
    double v_distance = 0;

    if(game->ray->found_h_wall_hit[i])
    {
        h_distance = distance_between_points(game->player->x, game->player->y, game->ray->h_wall_hit_x, game->ray->h_wall_hit_y);
    }
    else
    {
        h_distance = INT_MAX;
    }
    if(game->ray->found_v_wall_hit)
    {
        v_distance = distance_between_points(game->player->x, game->player->y, game->ray->v_wall_hit_x, game->ray->v_wall_hit_y);
    }
    else
    {
        v_distance = INT_MAX;
    }
    
    if(h_distance < v_distance)
    {
        game->ray->wall_hit_x[i] = game->ray->h_wall_hit_x;
    }
    else
    {
        game->ray->wall_hit_x[i] = game->ray->v_wall_hit_x;
    }
    
    if (h_distance < v_distance)
    {
        game->ray->wall_hit_y[i] = game->ray->h_wall_hit_y;
    }
    else
    {
        game->ray->wall_hit_y[i] = game->ray->v_wall_hit_y;
    }
    
    if(h_distance < v_distance)
    {
        game->ray->distances[i] = h_distance;
    }
    else
    {
        game->ray->distances[i] = v_distance;
    }
    if(v_distance < h_distance)
    {
        game->ray->to_hit[i] = true;
    }
    else
    {
        game->ray->to_hit[i] = false;
    }
}

void cast_rays(t_game *game)
{
    game->ray->ray_angle = game->player->rotation_angle - (FOV_ANGLE / 2);
    
    int i = 0;
    while(i < NUM_RAYS)
    {
        game->player->rotation_angle = normalize_angle(game->player->rotation_angle);
        game->ray->ray_angles[i] = game->ray->ray_angle;
        cast_v_h_rays(game, i);
        draw_line(game, game->player->x, game->player->y, game->ray->wall_hit_x[i], game->ray->wall_hit_y[i], 0x00FF0000);
        game->ray->ray_angle += FOV_ANGLE / NUM_RAYS;
        i++;
    }
}

int draw(t_game *game)
{
    printf("rotation angle: %f\n", game->player->rotation_angle);
    mlx_clear_window(game->mlx, game->mlx_win);
    draw_wall(game);
    mlx_put_image_to_window(game->mlx, game->mlx_win, game->data->img, 0, 0);
    draw_player(game);
    cast_rays(game);
    return 0;
}

int draw_player(t_game *game)
{
    int i = 0;
    int j = 0;
    int playerSize = 10;

    // Draw the player as a square
    while (j < playerSize)
    {
        i = 0;
        while (i < playerSize)
        {
            mlx_pixel_put(game->mlx, game->mlx_win, game->player->x + i, game->player->y + j, 0x00FF0000);
            i++;
        }
        j++;
    }
    
    // Calculate the line end point
    double lineLength = 300;
    double lineEndX = game->player->x + lineLength * cos(game->player->rotation_angle);
    double lineEndY = game->player->y + lineLength * sin(game->player->rotation_angle);

    // Draw the line from the center of the player to the calculated end point
    // draw_line(game, game->player->x + 5, game->player->y , lineEndX + 5, lineEndY , 0x00FF0000);
    return (0);
}

void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
    // int dx = abs(x1 - x0);
    // int dy = abs(y1 - y0);
    // int sx = (x0 < x1) ? 1 : -1;
    // int sy = (y0 < y1) ? 1 : -1;
    // int err = dx - dy;

    // while (1)
    // {
    //     mlx_pixel_put(game->mlx, game->mlx_win, x0, y0, color);

    //     if (x0 == x1 && y0 == y1)
    //         break;

    //     int e2 = 2 * err;
    //     if (e2 > -dy)
    //     {
    //         err -= dy;
    //         x0 += sx;
    //     }
    //     if (e2 < dx)
    //     {
    //         err += dx;
    //         y0 += sy;
    //     }
    // }

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int steps = fmax(dx, dy);

    float xIncrement = (float)(x1 - x0) / steps;
    float yIncrement = (float)(y1 - y0) / steps;

    float x = x0;
    float y = y0;

    for (int i = 0; i <= steps; i++)
    {
        mlx_pixel_put(game->mlx, game->mlx_win, round(x), round(y), color);
        x += xIncrement;
        y += yIncrement;
    }
}

void draw_pixel(t_game *game, int x, int y, int color)
{
    for (int j = 0; j < TILE_SIZE; j++)
    {
        for (int i = 0; i < TILE_SIZE; i++)
        {
            int pixel_index = (y + j) * game->data->line_length + (x + i) * (game->data->bits_per_pixel / 8);

            game->data->addr[pixel_index] = (color >> 16) & 0xFF;   
            game->data->addr[pixel_index + 1] = (color >> 8) & 0xFF; 
            game->data->addr[pixel_index + 2] = color & 0xFF;        
        }
    }
}

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