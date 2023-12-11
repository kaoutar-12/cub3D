# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 10:30:09 by kmouradi          #+#    #+#              #
#    Updated: 2023/12/10 15:13:17 by mboukaiz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CL=ar -rc
CN=rm -rf
FLAGS=-Wall -Wextra -Werror
SRC=	ft_atoi.c \
		ft_bzero.c \
		ft_isalnum.c \
		ft_isdigit.c \
		ft_libft.c \
		ft_libft_extra.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memset.c \
		ft_strcpy.c \
		ft_strncmp.c \
		ft_strtrim.c \
		lst_funcs.c \
		lst_funcs_extra.c \
		ft_memory.c \
		ft_strlcpy.c \

OBJ=${SRC:.c=.o}

NAME=libft.a

all:${NAME}

${NAME}:${OBJ} libft.h
	${CL} ${NAME} ${OBJ}

%.o: %.c  libft.h
	${CC} ${FLAGS} -c $<

clean:
	${CN} ${OBJ}

fclean: clean
	${CN} ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re