/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:45:54 by dummy             #+#    #+#             */
/*   Updated: 2023/09/25 11:07:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
		ft_putchar_fd('0', fd);
	else if (n < 0)
	{
		write(fd, "-", 1);
		if (-10 < n)
			ft_putchar_fd((char)((n % 10) * (-1) + '0'), fd);
		else
		{
			ft_putnbr_fd((n / 10) * -1, fd);
			ft_putchar_fd((n % 10) * (-1) + '0', fd);
		}
	}
	else
	{
		if (!(n < 10))
		{
			ft_putnbr_fd(n / 10, fd);
		}
		ft_putchar_fd((char)((n % 10) + '0'), fd);
	}
	return ;
}
