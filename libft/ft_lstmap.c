/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:02:44 by dummy             #+#    #+#             */
/*   Updated: 2023/09/25 11:07:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	**new_list;
	t_list	*node;

	new_list = malloc(sizeof(t_list *));
	if (lst == NULL || new_list == NULL)
	{
		return (NULL);
	}
	*new_list = NULL;
	while (lst != NULL)
	{
		node = ft_lstnew(f(lst->content));
		if (node == NULL || node->content == NULL)
		{
			ft_lstclear(new_list, del);
			free(new_list);
			return (NULL);
		}
		ft_lstadd_back(new_list, node);
		lst = lst->next;
	}
	node = *new_list;
	free(new_list);
	return (node);
}
