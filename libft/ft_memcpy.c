/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:31:25 by dummy             #+#    #+#             */
/*   Updated: 2023/09/25 11:07:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*char_dst;
	char	*char_src;

	if (dst == NULL && src == NULL)
	{
		return (NULL);
	}
	char_dst = dst;
	char_src = (char *)(src);
	while (n)
	{
		*char_dst = *char_src;
		char_dst++;
		char_src++;
		n--;
	}
	return (dst);
}
