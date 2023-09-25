/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:55:23 by dummy             #+#    #+#             */
/*   Updated: 2023/09/25 11:07:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	moving(char *char_dst, char *char_src, size_t len)
{
	size_t	i;

	if (char_dst < char_src)
	{
		i = 0;
		while (i < len)
		{
			char_dst[i] = char_src[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (0 < i)
		{
			char_dst[i - 1] = char_src[i - 1];
			i--;
		}
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*char_dst;
	char	*char_src;

	if (dst == NULL && src == NULL)
	{
		return (NULL);
	}
	char_dst = (char *)(dst);
	char_src = (char *)(src);
	moving(char_dst, char_src, len);
	return (dst);
}
