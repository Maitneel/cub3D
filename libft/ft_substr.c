/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:41:14 by dummy             #+#    #+#             */
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	substr_len;
	size_t	i;

	if (s == NULL)
		return (NULL);
	while (*s != '\0' && start)
	{
		s++;
		start--;
	}
	substr_len = min(len, ft_strlen(s) - start);
	if (start != 0)
		substr_len = 0;
	substr = malloc(sizeof(char) * substr_len + 1);
	if (substr == NULL)
		return (NULL);
	ft_bzero(substr, sizeof(char) * (substr_len + 1));
	i = 0;
	while (i < substr_len)
	{
		substr[i] = s[i + start];
		i++;
	}
	return (substr);
}
