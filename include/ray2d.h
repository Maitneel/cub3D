/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:13:47 by taksaito          #+#    #+#             */
/*   Updated: 2023/09/30 17:42:22 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY2D_H
# define RAY2D_H

# include "vector2d.h"

typedef struct s_ray2d
{
	t_vector2d	*pos;
	t_vector2d	*way;
}	t_ray2d;

t_vector2d	*get_begin(t_ray2d *ray);
t_vector2d	*get_end(t_ray2d *ray);
t_vector2d	*intersection(t_ray2d *ray1, t_ray2d *ray2);

#endif // RAY2D_H
