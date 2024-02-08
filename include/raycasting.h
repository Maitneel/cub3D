/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:41:53 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/07 23:02:02 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d_structs.h"
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>

t_mlx_image				*new_raycasting_image(t_cub3d *cub3d, t_mlx *mlx,
							const int width, const int height);
bool					is_wall(t_cub3d *cub3d, int y, int x);
double					get_distance(t_point *start, t_point *end);

// util
double					norm_dir(double dir);
bool					is_west(double ray_dir);
bool					is_east(double ray_dir);
bool					is_south(double ray_dir);
bool					is_north(double ray_dir);

// collistion_point
t_coll_point			get_collision_point(t_cub3d *cub3d, double dir);

void					set_ver_step_if_east(t_player player, int *step,
							int *side_x);
void					set_ver_step_if_west(t_player player, int *step,
							int *side_x);
void					set_hz_step_if_north(t_player player, int *step,
							int *side_y);
void					set_hz_step_if_south(t_player player, int *step,
							int *side_y);

// distance

bool					is_wall(t_cub3d *cub3d, int y, int x);
double					get_distance(t_point *start, t_point *end);
double					get_adj_dis(t_player *player, double ray_dir,
							t_point *start, t_point *end);
double					get_wall_ratio(double wall_distance);

// texture

t_texture				*get_texture(t_cub3d *cub3d, t_coll_point *coll_pt);
double					get_texture_position(t_cub3d *cub3d,
							t_coll_point *coll_pt);

// raycasting_helper

t_point					get_screen_point(const t_point focus_point,
							const double direction);
double					get_direction_across_screen_position(
							const t_point player_position,
							const t_point screen_left,
							const t_point screen_right,
							const int screen_position);
t_mlx_image				*paste_black_image(t_mlx_image *image);
t_paste_texture_info	new_paste_texxture_info(double mag, double texture_pos,
							size_t image_x);
t_mlx_image				*draw_world(t_cub3d *cub3d, t_mlx_image *image,
							t_point screen_left, t_point screen_right);

#endif // RAYCASTING_H
