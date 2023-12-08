/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:51:51 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/08 17:49:26 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

int		ft_putstr(char *str);
char	*get_next_line(int fd);
size_t	ft_strlen_gnl(char *s);
char	*ft_strdup_gnl(char *s1);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strchr_gnl(char *s, int c);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000

# endif
#endif