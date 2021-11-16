/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:04:59 by ocartier          #+#    #+#             */
/*   Updated: 2021/11/16 14:53:36 by ocartier         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
char	*init_empty_string()
{
	char	*str;

	str = (char *)malloc(sizeof(char));
	if (!str)
		return (NULL);
	str[0] = 0;
	return (str);
}

char	*get_next_line(int fd)
{
	ssize_t			ret;
	char			*buf;
	int				cur;
	char			*readed;
	int				is_end;
	char			*tmp;
	static char		*previous;

	if (!BUFFER_SIZE || BUFFER_SIZE < 1 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);	
	readed = init_empty_string();
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf || !readed)
		return (NULL);
	is_end = 0;
	if (!previous)
	{
		previous = init_empty_string();
		if (!previous)
			return (NULL);
	}
	else
	{
		long	nlindex = charchr(previous, 10);
		//printf("nl : %zu\n", nlindex);
		if (nlindex >= 0)
		{
			tmp = ft_substr(previous, 0, nlindex + 1);
			readed = ft_strjoin(readed, tmp);
			previous = ft_substr(previous, nlindex + 1, ft_strlen(previous) + 1);
			//free(tmp);
			if (ft_strlen(readed) == 0)
			{
				//free(readed);
				return (NULL);
			}
			return (readed);
		}
		//printf("previous : %s\n", previous);
		//return (NULL);
	}
	readed = ft_strjoin(readed, previous);
	if (!readed)
		return (NULL);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret && !is_end)
	{
		buf[ret] = 0;
		/*
		cur = charchr(buf, '\n');	
		if (cur >= 0)
		{
			printf("nl en %zd, %s\n", ret, buf);
			previous = ft_substr(buf, cur + 1, ret);
			buf = ft_substr(buf, 0, cur + 1);
			if (!previous || !buf)
				return (NULL);
			break ;
		}
		*/
		
		cur = 0;
		while (buf[cur])
		{
			if (buf[cur] == '\n')
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
	//free(buf);
	if (!ret)
	{
		//free(previous);
		//previous = NULL;
		printf("free2");
	}
	if (ft_strlen(readed) == 0)
	{
		//free(readed);
		printf("free1");
		return (NULL);
	}
	return (readed);
}
