/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:31:34 by dummy             #+#    #+#             */
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

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*char_haystack;
	size_t	i;
	size_t	j;

	if (ft_strlen(needle) == 0)
		return ((char *)(haystack));
	if (len == 0)
		return (NULL);
	char_haystack = (char *)(haystack);
	i = 0;
	while (i + ft_strlen(needle) <= min(len, ft_strlen(haystack)))
	{
		j = 0;
		while (j < ft_strlen(needle) && i + j < min(len, ft_strlen(haystack)))
		{
			if (char_haystack[i + j] != needle[j])
				break ;
			if (j == ft_strlen(needle) - 1)
				return (&char_haystack[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
