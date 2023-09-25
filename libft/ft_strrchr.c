/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:36:45 by dummy             #+#    #+#             */
/*   Updated: 2023/09/25 11:07:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	s_length;
	size_t	i;

	s_length = ft_strlen(s);
	i = s_length + 1;
	while (0 < i)
	{
		i--;
		if ((unsigned char)(s[i]) == (unsigned char)(c))
		{
			return ((char *)(s + (sizeof(char) * i)));
		}
	}
	return (NULL);
}
