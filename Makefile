# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 12:49:56 by kmouradi          #+#    #+#              #
#    Updated: 2023/12/06 13:05:31 by kmouradi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= Cub3d
NAME_B= Cub3d_bonus
CC= cc
CN= rm -rf
FLAGS= -Wall -Wextra -Werror -g -fsanitize=address
LINKS= libraries/MLX42/build/libmlx42.a -Iinclude -lglfw -L /Users/kmouradi/homebrew/opt/glfw/lib/

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


OBJECT = $(addprefix ${PREFIX}, $(SOURCE:.c=.o))

OBJECT_B = $(addprefix ${PREFIX}, $(SOURCE_B:.c=.o))

all: ${NAME}

libmlx42:
	make -C libraries/MLX42/build

${PREFIX}:
	mkdir -p ${PREFIX}
	mkdir -p ${PREFIX}mandatory
	mkdir -p ${PREFIX}bonus

${NAME}: ${PREFIX} ${OBJECT}
	${CC} ${FLAGS} ${OBJECT} ${LINKS} -o ${NAME}

${PREFIX}%.o: %.c mandatory/cub3d.h libmlx42
	${CC} ${FLAGS} -c $< -o $@

bonus: ${PREFIX} ${OBJECT_B}
	${CC} ${FLAGS} ${OBJECT_B} ${LINKS} -o ${NAME_B}

clean:
	${CN} ${PREFIX}
	${CN} ${PREFIX}mandatory
	${CN} ${OBJECT}
	${CN} ${PREFIX}bonus
	${CN} ${OBJECT_B}
	make -C libraries/MLX42/build clean

fclean: clean
	${CN} ${NAME}
	${CN} ${NAME_B}

re: fclean all

.PHONY: all bonus clean fclean re
