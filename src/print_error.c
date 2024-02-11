/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:02:57 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:02:58 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

void	print_error(bool is_system_call_error, const char *optional_massage)
{
	write(STDERR_FILENO, "Error\n", ft_strlen("Error\n"));
	if (is_system_call_error)
	{
		perror(optional_massage);
	}
	else
	{
		write(STDERR_FILENO, optional_massage, ft_strlen(optional_massage));
	}
}
