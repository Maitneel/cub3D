/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:49:27 by dummy             #+#    #+#             */
/*   Updated: 2023/09/25 11:07:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current_node;
	t_list	*next_node;

	if (lst == NULL || del == NULL)
	{
		return ;
	}
	current_node = *lst;
	while (current_node != NULL)
	{
		next_node = current_node->next;
		(*del)(current_node->content);
		current_node->next = NULL;
		free(current_node);
		current_node = NULL;
		current_node = next_node;
	}
	*lst = NULL;
	return ;
}
