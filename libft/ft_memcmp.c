/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:51:34 by dummy             #+#    #+#             */
/*   Updated: 2023/09/25 11:07:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*char_s1;
	unsigned char	*char_s2;
	size_t			i;

	char_s1 = (unsigned char *)(s1);
	char_s2 = (unsigned char *)(s2);
	if (n == 0)
	{
		return (0);
	}
	i = 0;
	while (i < n)
	{
		if (char_s1[i] != char_s2[i])
		{
			return (char_s1[i] - char_s2[i]);
		}
		i++;
	}
	return (0);
}
