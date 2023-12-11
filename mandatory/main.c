/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:05:03 by kmouradi          #+#    #+#             */
/*   Updated: 2023/12/11 15:08:21 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_msg(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

void	set_player_direction(t_game *game)
{
	if (game->parse->player_direction == NORTH)
		game->player->rotation_angle = M_PI * 1.5;
	else if (game->parse->player_direction == SOUTH)
		game->player->rotation_angle = M_PI / 2;
	else if (game->parse->player_direction == EAST)
		game->player->rotation_angle = 0;
	else if (game->parse->player_direction == WEST)
		game->player->rotation_angle = M_PI;
}

void	fun()
{
	system("leaks Cub3d");
}

void	close_all()
{
	int	i;

	i = 3;
	while (i < 255)
	{
		close(i);
		i++;
	}
}

void	print_all_vars(t_parse *vars)
{
	printf("vars->a_map\n");
	for (int i = 0; vars->actual_map[i]; i++)
		printf("|%s|\n", vars->actual_map[i]);
	printf("vars->map\n");
	for (int i = 0; vars->map[i]; i++)
		printf("|%s|\n", vars->map[i]);

	printf("vars->c_rgb.red\n");
	printf("|%d|\n", vars->c_rgb.red);
	printf("vars->c_rgb.green\n");
	printf("|%d|\n", vars->c_rgb.green);
	printf("vars->c_rgb.blue\n");
	printf("|%d|\n", vars->c_rgb.blue);
	
	printf("vars->f_rgb.red\n");
	printf("|%d|\n", vars->f_rgb.red);
	printf("vars->f_rgb.green\n");
	printf("|%d|\n", vars->f_rgb.green);
	printf("vars->f_rgb.blue\n");
	printf("|%d|\n", vars->f_rgb.blue);

	printf("vars->ea\n");
	printf("|%s|\n", vars->ea);
	printf("vars->we\n");
	printf("|%s|\n", vars->we);
	printf("vars->so\n");
	printf("|%s|\n", vars->so);
	printf("vars->no\n");
	printf("|%s|\n", vars->no);

	printf("x |%d|\n", vars->player_x);
	printf("y |%d|\n", vars->player_y);

	printf("h |%d|\n", vars->map_h);
	printf("w |%d|\n", vars->map_w);
}

int	main(int ac, char **av)
{
	t_game		*game;
	t_player	*player;
	t_ray		*ray;
	t_parse		parse;

	if (ac == 2)
	{
		map_operations(av[1], &parse);
		print_all_vars(&parse);
		// while (1);
		// char *ptr = ft_strtrim_fh("   \nmakram\nmakram", " \n");
		// ptr = ft_strtrim_fh("   \nmakram\nmakram2", " \n");
		// ptr = ft_strtrim_fh("   \nmakram\nmakram3", " \n");
		// ptr = ft_strtrim_fh("   \nmakram\nmakram4", " \n");
		// ptr = ft_strtrim_fh("\n", " \n");
		// char *line = ft_strjoin(ptr, "\nks\nmakram");
		// line = ft_strjoin(ptr, "\nks\nmakra2m");
		// ptr = ft_strjoin(ptr, line);
		// char **map = ft_split(ptr, '\n');
		// for (int i = 0; map[i]; i++)
		// {
		// 	printf ("%s\n", map[i]);
		// }
		// free(map);
		// custom_exit(0);

		// char *ptr = ft_strdup("makram\nmakram");
		// while (1);
		// custom_exit(0);
		// game = malloc(sizeof(t_game));
		// player = malloc(sizeof(t_player));
		// ray = malloc(sizeof(t_ray));
		// if (!game || !player || !ray)
		// 	error_msg();
		// init_rays(ray);
		// init_player(player);
		// game->player = player;
		// game->ray = ray;
		// game->parse = &parse;
		// game->player->y = game->parse->player_x * TILE_SIZE + TILE_SIZE / 2;
		// game->player->x = game->parse->player_y * TILE_SIZE + TILE_SIZE / 2;
		// set_player_direction(game);
		// ft_game(game);
		// garbage_collector(NULL, 1);
		// free (parse.map);
	}
	else
		error_msg();
}
