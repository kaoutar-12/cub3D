/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:08:44 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/05 15:36:08 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void	garbage_collector(void	*ptr, int delete)
{
	static t_list	*head;
	t_list			*node;

	if (delete)
		ft_lstclear(&head, free);
	else
	{
		node = ft_lstnew(ptr);
		ft_lstadd_back(&head, node);
	}
}

void	custom_exit(int status)
{
	garbage_collector(NULL, 1);
	exit(status);
}

void	*gc_malloc(int size)
{
	void	*ptr;

	ptr = malloc (size);
	ft_memset(ptr, 0, size);
	garbage_collector (ptr, 0);
	return (ptr);
}