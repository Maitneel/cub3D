/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:58:50 by dummy             #+#    #+#             */
/*   Updated: 2023/09/25 11:07:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	int_length(int n)
{
	size_t	result;

	result = 0;
	if (n < 0)
	{
		result++;
	}
	if (n == 0)
	{
		result = 1;
	}
	while (n)
	{
		result++;
		n /= 10;
	}
	return (result);
}

static int	ft_abs(int n)
{
	if (n < 0)
	{
		return (-n);
	}
	else
	{
		return (n);
	}
}

char	*ft_itoa(int n)
{
	char	*string;
	size_t	len;

	len = int_length(n);
	string = malloc(sizeof(char) * (len + 1));
	if (string == NULL)
	{
		return (NULL);
	}
	ft_bzero(string, sizeof(char) * (len + 1));
	if (n == 0)
	{
		string[0] = '0';
	}
	if (n < 0)
	{
		string[0] = '-';
	}
	while (n)
	{
		string[len - 1] = (char)(ft_abs(n % 10) + '0');
		n /= 10;
		len--;
	}
	return (string);
}
