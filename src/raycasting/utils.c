/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:50:19 by taksaito          #+#    #+#             */
/*   Updated: 2024/01/28 21:18:00 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

double	norm_dir(double dir)
{
	return (fmod(fabs(dir + 2 * M_PI), 2 * M_PI));
}

bool	is_west(double ray_dir)
{
	double	dir;

	dir = norm_dir(ray_dir - M_PI_2);
	if (0 < dir && dir < M_PI)
		return (true);
	return (false);
}

bool	is_east(double ray_dir)
{
	double	dir;

	dir = norm_dir(ray_dir - M_PI_2);
	if (dir > M_PI && dir < 2 * M_PI)
		return (true);
	return (false);
}

bool	is_south(double ray_dir)
{
	double	dir;

	dir = norm_dir(ray_dir - M_PI_2);
	if (dir < M_PI_2 || dir > M_PI_2 * 3)
		return (true);
	return (false);
}

bool	is_north(double ray_dir)
{
	double	dir;

	dir = norm_dir(ray_dir - M_PI_2);
	if (dir > M_PI_2 && dir < M_PI_2 * 3)
		return (true);
	return (false);
}
