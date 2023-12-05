/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:08:44 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/05 13:24:22 by mboukaiz         ###   ########.fr       */
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
		printf ("size of nodes is : %d\n", ft_lstsize(head));
	}
}

void	*gc_malloc(int size)
{
	void	*ptr;

	ptr = malloc (size);
	ft_memset(ptr, 0, size);
	garbage_collector (ptr, 0);
	return (ptr);
}