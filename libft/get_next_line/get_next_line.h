/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_lien.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:20:06 by dummy             #+#    #+#             */
/*   Updated: 2023/09/25 14:31:16 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

typedef struct s_buffer
{
	char	str[BUFFER_SIZE + 1];
	ssize_t	start;
	ssize_t	read_ret;
	ssize_t	loop_flag;
}			t_buffer;

typedef struct s_string
{
	char	*str;
	size_t	size;
	size_t	max_size;
}			t_string;

char		*get_next_line(int fd);
void		add_back_string(t_string *data, t_buffer *buf);

#endif
