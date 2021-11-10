/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:04:59 by ocartier          #+#    #+#             */
/*   Updated: 2021/11/10 10:48:57 by ocartier         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	int				ret;
	char			buf[2];
	int				cur;
	char			*readed;	
	//static size_t	start;
	//size_t			cur_start;

	/*
	if(!start)
		start = 0;
	*/
	readed = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!readed)
		return (NULL);
	cur = 0;
	//cur_start = 0;
	ret = read(fd, buf, 1);
	while (ret && cur < BUFFER_SIZE)
	{
		buf[ret] = 0;
		/*
		if (cur_start < start)
			cur_start++;
		else
		{*/
			readed[cur] = buf[0];
			cur++;
		//}
		ret = read(fd, buf, 1);
	}
	//start += cur - 1;
	readed[cur] = 0;
	return (readed);
}
