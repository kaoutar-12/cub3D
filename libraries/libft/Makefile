# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 10:30:09 by kmouradi          #+#    #+#              #
#    Updated: 2023/12/07 10:31:29 by kmouradi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CL=ar -rc
CN=rm -rf
FLAGS=-Wall -Wextra -Werror
SRC=	ft_atoi.c \
		ft_bzero.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_libft.c \
		ft_libft_extra.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strcpy.c \
		ft_striteri.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_tolower.c \
		ft_toupper.c \
		lst_funcs.c \

OBJ=${SRC:.c=.o}

NAME=libft.a

all:${NAME}

${NAME}:${OBJ}
	${CL} ${NAME} ${OBJ}

%.o: %.c  libft.h
	${CC} ${FLAGS} -c $<

clean:
	${CN} ${OBJ}

fclean: clean
	${CN} ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re