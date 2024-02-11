/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito < taksaito@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:00:59 by taksaito          #+#    #+#             */
/*   Updated: 2024/02/11 17:01:00 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_LIB_H
# define PRINT_LIB_H

# include <stdbool.h>

void	print_error(bool is_system_call_error, const char *optional_massage);

#endif