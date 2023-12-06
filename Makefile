# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 12:49:56 by kmouradi          #+#    #+#              #
#    Updated: 2023/12/06 12:55:29 by kmouradi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= Cub3d
CC= cc
CN= rm -rf
FLAGS= -Wall -Wextra -Werror -g -fsanitize=address
LINKS= libraries/MLX42/build/libmlx42.a -Iinclude -lglfw -L /Users/kmouradi/homebrew/opt/glfw/lib/

PREFIX = ./obj/

SOURCE= mandatory/cast_rays.c \
		mandatory/ft_draw.c \
		mandatory/ft_game.c \
		mandatory/helpers.c \
		mandatory/keys_hooks.c \
		mandatory/cast_horizontal.c \
		mandatory/cast_vertical.c \
		mandatory/main.c \
		mandatory/movements.c \
		mandatory/draw_minimap.c \
		mandatory/init.c \


OBJECT = $(addprefix ${PREFIX}, $(SOURCE:.c=.o))

all: ${NAME}

libmlx42:
	make -C libraries/MLX42/build

${PREFIX}:
	mkdir -p ${PREFIX}
	mkdir -p ${PREFIX}mandatory

${NAME}: ${PREFIX} ${OBJECT}
	${CC} ${FLAGS} ${OBJECT} ${LINKS} -o ${NAME}

${PREFIX}%.o: %.c mandatory/cub3d.h libmlx42
	${CC} ${FLAGS} -c $< -o $@

clean:
	${CN} ${PREFIX}
	${CN} ${PREFIX}mandatory
	${CN} ${OBJECT}
	make -C libraries/MLX42/build clean

fclean: clean
	${CN} ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re
