/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:34:54 by taksaito          #+#    #+#             */
/*   Updated: 2023/10/07 18:06:45 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CASTING_H
# define RAY_CASTING_H

# include "cub3d_structs.h"
# include "ray2d.h"
# include <stdbool.h>

t_vector2d	get_intersection_with_wall(t_cub3d *cub3d, double direction);
bool	is_wall(t_vector2d *vec);

#endif // RAY_CASTING_H
