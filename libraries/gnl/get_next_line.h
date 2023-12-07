/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:51:51 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/07 10:42:50 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "../../mandatory/cub3d.h"

char	*get_next_line(int fd);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
char	*ft_strchr2(char *s, int c);
char	*ft_strjoin2(char *s1, char *s2);
char	*ft_strdup2(char *s1);
size_t	ft_strlen2(char *s);

# endif
#endif