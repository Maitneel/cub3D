/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:52:58 by taksaito          #+#    #+#             */
/*   Updated: 2023/09/30 17:34:54 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR2D_H
# define VECTOR2D_H

typedef struct	s_vector2ds
{
	double	y;
	double	x;
}	t_vector2d;

// vector2d
t_vector2d	*add(t_vector2d *lhs, t_vector2d *rhs);
t_vector2d	*sub(t_vector2d *lhs, t_vector2d *rhs);
t_vector2d	*mult(t_vector2d *vec, double d);
double		mag(t_vector2d *vec);

#endif // VECTOR2D_H
