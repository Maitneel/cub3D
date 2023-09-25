/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:11:46 by dummy             #+#    #+#             */
/*   Updated: 2023/09/25 11:07:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_trim(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_substr(s1, 0, ft_strlen(s1)));
	start = 0;
	while (s1[start] != '\0' && is_trim(s1[start], set))
	{
		start++;
	}
	end = ft_strlen(s1) - 1;
	while (s1[end] != '\0' && is_trim(s1[end], set) && start <= end)
	{
		end--;
		if (end == 0)
		{
			break ;
		}
	}
	end++;
	return (ft_substr(s1, start, end - start));
}
