/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:01:56 by dummy             #+#    #+#             */
/*   Updated: 2023/09/25 11:07:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	long_len(long n)
{
	size_t	result;

	result = 0;
	while (1)
	{
		result++;
		n /= 10;
		if (n == 0)
		{
			break ;
		}
	}
	return (result);
}

static long	min(long a, long b)
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

static long	format_long(int signal, size_t i, long result)
{
	if (long_len(LONG_MAX) < i)
	{
		result = LONG_MIN;
	}
	if (!(signal < 0) && result == LONG_MIN)
	{
		result++;
	}
	if (!(signal < 0))
	{
		result *= -1;
	}
	return (result);
}

static long	ft_atol(const char *str, int signal)
{
	long	result;
	size_t	i;

	i = 0;
	result = 0;
	while (*str == '0')
	{
		str++;
	}
	while ('0' <= str[i] && str[i] <= '9' && i <= long_len(LONG_MIN)
		&& result != (LONG_MIN / 10))
	{
		result *= 10;
		result -= (str[i] - '0');
		i++;
	}
	if ('0' <= str[i] && str[i] <= '9' && result == LONG_MIN / 10)
	{
		result *= 10;
		result -= min(str[i] - '0', (LONG_MIN % 10) * -1);
	}
	return (format_long(signal, i, result));
}

int	ft_atoi(const char *str)
{
	int		signal;
	size_t	i;

	signal = 0;
	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		signal ^= (str[i] == '-') * -1;
		i++;
	}
	return ((int)(ft_atol(str + i, signal)));
}
