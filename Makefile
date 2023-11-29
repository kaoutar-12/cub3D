# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 12:49:56 by kmouradi          #+#    #+#              #
#    Updated: 2023/11/29 15:14:59 by kmouradi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CN=rm -rf
FLAGS=
LINKS= MLX42/build/libmlx42.a -Iinclude -lglfw -L /Users/kmouradi/homebrew/opt/glfw/lib/


SOURCE= cast_rays.c\
		ft_draw.c\
		ft_game.c\
		helpers.c\
		keys_hooks.c\
		cast_horizontal.c\
		cast_vertical.c\
		main.c\
		movements.c\
		draw_minimap.c\
		init.c\


OBJECT=${SOURCE:.c=.o}

NAME=Cub3d

all: ${NAME}

${NAME}:${OBJECT}
	${CC} ${FLAGS} ${OBJECT} ${LINKS} -o ${NAME}

%.o: %.c  cub3d.h
	${CC} ${FLAGS} -c $<

clean:
	${CN} ${OBJECT}

fclean: clean
	${CN} ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re
