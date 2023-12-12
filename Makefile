# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 12:49:56 by kmouradi          #+#    #+#              #
#    Updated: 2023/12/12 12:17:33 by kmouradi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= Cub3d
NAME_B= Cub3d_bonus
CC= cc
CN= rm -rf
FLAGS= -Wall -Wextra -Werror 
LINKS= libraries/MLX42/build/libmlx42.a -Iinclude -lglfw -L /Users/kmouradi/Homebrew/opt/glfw/lib/

PREFIX = ./obj/

SOURCE =	mandatory/cast_rays.c \
			mandatory/ft_draw.c \
			mandatory/ft_game.c \
			mandatory/helpers.c \
			mandatory/keys_hooks.c \
			mandatory/cast_horizontal.c \
			mandatory/cast_vertical.c \
			mandatory/main.c \
			mandatory/movements.c \
			mandatory/init.c \
			mandatory/exit.c \
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
			bonus/init.c \
			bonus/exit.c \
			bonus/sprites_bonus.c \
			bonus/minimap_bonus.c \
			bonus/parsing/config_setup.c \
			bonus/parsing/data_processing.c \
			bonus/parsing/map_operations.c \
			bonus/parsing/map_processing.c \
			bonus/parsing/map_reading.c \
			bonus/parsing/map_validation.c \
			bonus/parsing/memory_management.c \
			bonus/parsing/string_manipulation.c \
			libraries/gnl/get_next_line.c \
			libraries/gnl/get_next_line_utils.c \


OBJECT = $(addprefix ${PREFIX}, $(SOURCE:.c=.o))

OBJECT_B = $(addprefix ${PREFIX}, $(SOURCE_B:.c=.o))

all: ${NAME}

libmlx42:
	cmake -B ./libraries/MLX42/build ./libraries/MLX42
	make -C libraries/MLX42/build

libft:
	make -C libraries/libft

${PREFIX}:
	mkdir -p ${PREFIX}
	mkdir -p ${PREFIX}mandatory
	mkdir -p ${PREFIX}mandatory/parsing
	mkdir -p ${PREFIX}libraries/gnl
	mkdir -p ${PREFIX}bonus
	mkdir -p ${PREFIX}bonus/parsing
	mkdir -p ${PREFIX}bonus/gnl

${NAME}: ${PREFIX} ${OBJECT} libft libmlx42
	${CC} ${FLAGS} ${OBJECT} libraries/libft/libft.a ${LINKS} -o ${NAME}

${PREFIX}%.o: %.c mandatory/cub3d.h bonus/cub3d_bonus.h
	${CC} ${FLAGS} -c $< -o $@

bonus: ${PREFIX} ${OBJECT_B} libft libmlx42 ${NAME}
	${CC} ${FLAGS} ${OBJECT_B} libraries/libft/libft.a ${LINKS} -o ${NAME_B}

clean:
	${CN} ${PREFIX}
	${CN} ${PREFIX}mandatory
	${CN} ${PREFIX}mandatory/parsing
	${CN} ${PREFIX}libraries/gnl
	${CN} ${OBJECT}
	${CN} ${PREFIX}bonus
	${CN} ${PREFIX}bonus/parsing
	${CN} ${PREFIX}bonus/gnl
	${CN} ${OBJECT_B}
	make -C libraries/MLX42/build clean
	make -C libraries/libft clean

fclean: clean
	${CN} ${NAME}
	${CN} ${NAME_B}
	make -C libraries/libft fclean

re: fclean all

.PHONY: all bonus clean fclean re
