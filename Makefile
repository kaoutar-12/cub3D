# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 12:49:56 by kmouradi          #+#    #+#              #
#    Updated: 2023/12/11 15:31:37 by mboukaiz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= Cub3d
NAME_B= Cub3d_bonus
CC= cc
CN= rm -rf
FLAGS= -fsanitize=address
# LINKS= libraries/MLX42/build/libmlx42.a -Iinclude -lglfw -L /Users/mboukaiz/.brew/opt/glfw/lib/

PREFIX = ./obj/

SOURCE =	mandatory/main.c \
			mandatory/parsing/config_setup.c \
			mandatory/parsing/data_processing.c \
			mandatory/parsing/map_operations.c \
			mandatory/parsing/map_processing.c \
			mandatory/parsing/map_reading.c \
			mandatory/parsing/map_validation.c \
			mandatory/parsing/memory_management.c \
			mandatory/parsing/string_manipulation.c \
			libraries/gnl/get_next_line.c \
			libraries/gnl/get_next_line_utils.c \

SOURCE_B = 	bonus/cast_rays.c \
			bonus/ft_draw.c \
			bonus/ft_game.c \
			bonus/helpers.c \
			bonus/keys_hooks.c \
			bonus/cast_horizontal.c \
			bonus/cast_vertical.c \
			bonus/main.c \
			bonus/movements.c \
			bonus/draw_minimap.c \
			bonus/init.c \

all : $(NAME)

libft : 
	make -C libraries/libft

$(NAME) : $(SOURCE) $(HEADER) libft
	$(CC) $(SOURCE) $(FLAGS) $(LINKS) libraries/libft/libft.a -o $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)
	make fclean -C libraries/libft

re: fclean all

.PHONY: all clean fclean re
