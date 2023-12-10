/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funcs_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:35:19 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/12/10 13:56:52 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	tmp = *lst;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
	free(tmp);
}

char	*ft_substr2(char const *s, unsigned int start, size_t len)
{
	char			*result;
	unsigned int	size;

	size = ft_strlen(s);
	if (!s)
		return (NULL);
	if (size < start)
		len = 0;
	if (size - start < len)
		len = size - start;
	result = (char *)gc_malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	result = ft_memmove(result, s + start, len);
	return (result);
}
