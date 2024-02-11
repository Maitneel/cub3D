/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_operation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:00:56 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:00:57 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_OPERATION_H
# define PLAYER_OPERATION_H

void	rotate_player(int key_code, t_player *player);
void	move_player(int key_code, t_player *player, t_map_element **map);

#endif