/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:04:59 by ocartier          #+#    #+#             */
/*   Updated: 2021/11/17 22:16:10 by ocartier         ###   ########.fr       */
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
	static char		*previous;

	if (!BUFFER_SIZE || BUFFER_SIZE < 1 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);	
	if (!previous)
		if (!(previous = init_empty_string()))
			return (NULL);
	if (!(buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (NULL);
	while (charchr(previous, '\n') < 0 && (ret = read(fd, buf, BUFFER_SIZE)))
	{
		buf[ret] = 0;
		previous = ft_strjoin(previous, buf);
	}
	free(buf);
	cur = charchr(previous, '\n');
	if (cur >= 0)
	{
		readed = ft_substr(previous, 0, cur + 1);
		previous = ft_substr(previous, cur + 1, ft_strlen(previous));
		//shiftstr(&previous, cur + 1);
	}
	else
	{
		readed = ft_substr(previous, 0, ft_strlen(previous));
		free(previous);
	}
	if (ft_strlen(readed) == 0)
	{
		free(readed);
		return (NULL);
	}
	return (readed);
}
