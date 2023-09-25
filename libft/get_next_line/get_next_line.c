/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_lien.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:20:12 by dummy             #+#    #+#             */
/*   Updated: 2023/09/25 14:30:57 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

char	*get_next_line(int fd)
{
	static t_buffer	buf;
	t_string		result;
	char			temp[1];

	result.str = NULL;
	result.max_size = 0;
	result.size = 0;
	buf.loop_flag = read(fd, temp, 0);
	while (buf.loop_flag == 0)
	{
		if (buf.start == 0)
		{
			buf.read_ret = read(fd, buf.str, BUFFER_SIZE);
			if (buf.read_ret <= 0)
				break ;
		}
		add_back_string(&result, &buf);
	}
	if (buf.loop_flag == -1 || buf.read_ret == -1)
	{
		free(result.str);
		result.str = NULL;
	}
	return (result.str);
}

void	add_back_string(t_string *data, t_buffer *buf)
{
	char	*new_str;
	size_t	i;

	new_str = malloc(sizeof(char) * (data->size + (buf->read_ret - buf->start)
				+ 1));
	if (new_str == NULL)
		buf->loop_flag = -1;
	else
		data->max_size = data->size + (buf->read_ret - buf->start) + 1;
	i = -1;
	while (++i < data->size && buf->loop_flag == 0)
		new_str[i] = data->str[i];
	free(data->str);
	if (buf->loop_flag != 0)
		return ;
	while (buf->start < buf->read_ret && buf->loop_flag == 0)
	{
		new_str[data->size++] = buf->str[buf->start++];
		if (buf->str[buf->start - 1] == '\n')
			buf->loop_flag = 1;
	}
	new_str[data->size] = '\0';
	if (buf->start == buf->read_ret)
		buf->start = 0;
	data->str = new_str;
}
