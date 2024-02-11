/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:02:21 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:02:21 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_structs.h"
#include "libft.h"
#include "get_next_line.h"
#include "util_lib.h"
#include "print_lib.h"
#include "free_lib.h"
#include "cub3d_structs.h"
#include "valid_map.h"

#include <stdlib.h>
#include <stdio.h>

t_map_element	**get_map(const int fd_of_move_to_end_of_graphic_info)
{
	char			**char_map;
	t_map_element	**converted_map;

	char_map = read_map(fd_of_move_to_end_of_graphic_info);
	converted_map = convert_to_map_element((const char **)(char_map));
	free_string_array(char_map);
	if (!is_correct_map((const t_map_element **)(converted_map)))
	{
		free_map(converted_map);
		return (NULL);
	}
	return (converted_map);
}
