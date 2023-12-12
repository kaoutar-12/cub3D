/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmouradi <kmouradi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:08:44 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/12 12:15:50 by kmouradi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	free_2d(char **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	free(data);
}

char	*allocate_space(int size)
{
	char	*str;

	str = malloc(size);
	ft_memset(str, 32, size);
	return (str);
}

void	garbage_collector(void	*ptr, int del)
{
	static t_list	*head;
	t_list			*node;

	if (del == 1 && head && head->content)
		ft_lstclear(&head, free);
	else
	{
		node = ft_lstnew(ptr);
		ft_lstadd_back(&head, node);
	}
}

void	custom_exit(int status)
{
	garbage_collector(NULL, -1);
	exit(status);
}

void	*gc_malloc(int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		error_msg();
	ft_memset(ptr, 0, size);
	garbage_collector (ptr, 0);
	return (ptr);
}
