/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 19:36:33 by dummy             #+#    #+#             */
/*   Updated: 2023/09/25 11:07:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	pow;
	void	*alloced_memory;

	pow = count * size;
	if (pow == 0)
	{
		alloced_memory = malloc(1);
		if (alloced_memory != NULL)
		{
			ft_bzero(alloced_memory, 1);
		}
		return (alloced_memory);
	}
	if (count > SIZE_MAX / size)
	{
		return (NULL);
	}
	alloced_memory = malloc(pow);
	if (alloced_memory == NULL)
	{
		return (alloced_memory);
	}
	ft_bzero(alloced_memory, pow);
	return (alloced_memory);
}
