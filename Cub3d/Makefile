# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/29 18:08:33 by mboukaiz          #+#    #+#              #
#    Updated: 2023/12/06 15:56:14 by mboukaiz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#this makefile is temporary

CC = cc

# CFLAGS = -Wall -Wextra -Werror

NAME = Cub3d

USER = mboukaiz

LINKS = MLX42/build/libmlx42.a -Iinclude -lglfw -L /Users/$(USER)/.brew/opt/glfw/lib/

HEADER = cub3d.h libft/libft.h gnl/get_next_line.h

SOURCE = main.c \
		 cast_rays.c \
		 ft_draw.c \
		 ft_game.c \
		 helpers.c \
		 keys_hooks.c \
		 cast_horizontal.c \
		 cast_vertical.c \
		 movements.c \
		 draw_minimap.c \
		 init.c \
		 parsing/map_operations.c parsing/read_map.c parsing/allocation.c\
		 libft/ft_libft.c libft/ft_libft_extra.c\
		 libft/ft_memcpy.c libft/ft_memset.c libft/ft_strtrim.c libft/ft_isdigit.c\
		 libft/ft_strcpy.c libft/lst_funcs.c\
		 gnl/get_next_line.c gnl/get_next_line_utils.c \
		 libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_atoi.c\

all : $(NAME)

$(NAME) : $(SOURCE) $(HEADER)
	$(CC) $(SOURCE) $(CFLAGS) $(LINKS) -o $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re