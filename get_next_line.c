/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:04:59 by ocartier          #+#    #+#             */
/*   Updated: 2021/11/12 16:28:37 by ocartier         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char	*init_empty_string()
{
	char	*str;

	str = (char *)malloc(sizeof(char));
	if (!str)
		return (NULL);
	str[0] = 0;
	return (str);
}

#include <stdio.h>
char	*get_next_line(int fd)
{
	int				ret;
	char			*buf;
	int				cur;
	char			*readed;
	int				is_end;
	static char		*previous;
	
	readed = init_empty_string();
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf || !readed)
		return (NULL);
	is_end = 0;
	ret = read(fd, buf, BUFFER_SIZE);
	if (!previous)
	{
		previous = init_empty_string();
		if (!previous)
			return (NULL);
	}
	readed = ft_strjoin(readed, previous);
	if (!readed)
		return (NULL);
	while (ret && !is_end)
	{
		buf[ret] = 0;
		cur = 0;
		while (buf[cur])
		{
			if (buf[cur] == '\n' && buf[cur + 1])
			{
				previous = ft_substr(buf, cur + 1, ret);
				buf = ft_substr(buf, 0, cur + 1);
				if (!previous || !buf)
					return (NULL);
				is_end = 1;
				break ;
			}
			cur++;
		}
		readed = ft_strjoin(readed, buf);
		if (!readed)
			return (NULL);
		if (!is_end)
			ret = read(fd, buf, BUFFER_SIZE);
	}
	return (readed);
}
