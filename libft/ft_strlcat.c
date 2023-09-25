/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:57:21 by dummy             #+#    #+#             */
/*   Updated: 2023/09/25 11:07:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	min(size_t a, size_t b)
{
	if (a < b)
	{
		return (a);
	}
	else
	{
		return (b);
	}
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	cat_begin;
	size_t	i;
	size_t	return_value;

	if (dstsize == 0)
	{
		return (ft_strlen(src));
	}
	return_value = min(ft_strlen(dst), dstsize) + ft_strlen(src);
	cat_begin = ft_strlen(dst);
	i = 0;
	while (cat_begin + i + 1 < dstsize && src[i] != '\0')
	{
		dst[cat_begin + i] = src[i];
		i++;
	}
	dst[cat_begin + i] = '\0';
	return (return_value);
}
