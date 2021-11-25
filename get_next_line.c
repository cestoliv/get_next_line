/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:04:59 by ocartier          #+#    #+#             */
/*   Updated: 2021/11/25 13:15:36 by ocartier         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char	*init_empty_string(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char));
	if (!str)
		return (NULL);
	str[0] = 0;
	return (str);
}

void	shiftstr(char **str, size_t start)
{
	char	*tmp;

	tmp = *str;
	*str = ft_substr(*str, start, ft_strlen(*str));
	free(tmp);
}

char	*get_next_line(int fd)
{
	ssize_t			ret;
	char			*buf;
	int				cur;
	char			*readed;
	static char		*previous = NULL;

	if (!BUFFER_SIZE || BUFFER_SIZE < 1 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!previous && !(previous = init_empty_string()))
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
		shiftstr(&previous, cur + 1);
	}
	else
	{
		readed = ft_substr(previous, 0, ft_strlen(previous));
		free(previous);
		previous = NULL;
	}
	if (ft_strlen(readed) == 0)
	{
		free(readed);
		return (NULL);
	}
	return (readed);
}
