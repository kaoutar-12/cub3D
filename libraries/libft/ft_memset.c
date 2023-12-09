/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:01:45 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/08 18:07:27 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*str;
	int				i;

	i = 0;
	str = (char *)b;
	while (len-- > 0)
	{
		str[i] = (char)c;
		i++;
	}
	str[i] = '\0';
	return (str);
}
