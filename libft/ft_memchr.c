/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:31:13 by dummy             #+#    #+#             */
/*   Updated: 2023/09/25 11:07:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*char_s;
	unsigned char	char_c;

	char_s = (unsigned char *)(s);
	char_c = (unsigned char)(c);
	if (n == 0)
	{
		return (NULL);
	}
	while (*char_s != char_c && n - 1)
	{
		char_s++;
		n--;
	}
	if (*char_s == char_c)
	{
		return (char_s);
	}
	else
	{
		return (NULL);
	}
}
