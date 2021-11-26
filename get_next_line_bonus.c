/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:04:59 by ocartier          #+#    #+#             */
/*   Updated: 2021/11/26 11:31:42 by ocartier         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void	shiftstr(char **str, size_t start)
{
	char	*tmp;

	tmp = *str;
	*str = ft_substr(*str, start, ft_strlen(*str));
	free(tmp);
}

prev_list	*new_prevs(int fd)
{
	prev_list	*elem;

	elem = malloc(sizeof(prev_list));
	if (!elem)
		return (NULL);
	elem->fd = fd;
	elem->previous = (char *)malloc(sizeof(char));
	if (elem->previous == NULL)
		return (NULL);
	elem->previous[0] = 0;
	elem->next = NULL;
	return (elem);
}

prev_list *add_prevs(prev_list **prevs, char *buf, int fd)
{
	prev_list *curr;
	prev_list *elem;

	curr = *prevs;
	if (curr->fd == fd)
	{
		curr->previous = ft_strjoin(curr->previous, buf);
		return (curr);
	}
	while (curr)
	{
		if (curr->fd == fd)
		{
			curr->previous = ft_strjoin(curr->previous, buf);
			return (curr);
		}
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	elem = new_prevs(fd);
	if (!elem)
		return (NULL);
	elem->previous = ft_strjoin(elem->previous, buf);
	curr->next = elem;
	return (elem);
}

prev_list *delete_prev(prev_list *prevs, int fd)
{
    prev_list *next;

    if (prevs->fd == fd)
	{
        next = prevs->next;
        free(prevs->previous);
		free(prevs);
        return (next);
    }
	else
	{
        prevs->next = delete_prev(prevs->next, fd);
        return (prevs);
    }
}

/*
char	*get_readed(prev_list *prevs, prev_list *cur_prev, int fd)
{
	char	*readed;
	long	cur;

	cur = charchr(cur_prev->previous, '\n');
	if (cur >= 0)
	{
		readed = ft_substr(cur_prev->previous, 0, cur + 1);
		shiftstr(&(cur_prev->previous), cur + 1);
	}
	else
	{
		readed = ft_substr(cur_prev->previous, 0, ft_strlen(cur_prev->previous));
		prevs = delete_prev(prevs, fd);
	}
	if (ft_strlen(readed) == 0)
	{
		free(readed);
		return (NULL);
	}
	return (readed);
}
*/

char	*get_next_line(int fd)
{
	ssize_t				ret;
	char				*buf;
	static prev_list	*prevs = NULL;
	prev_list			*cur_prev = NULL;
	char	*readed;
	long	cur;

	if (!BUFFER_SIZE || BUFFER_SIZE < 1 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!prevs)
	{
		prevs = new_prevs(fd);
		if (!prevs)
			return (NULL);
	}
	cur_prev = add_prevs(&prevs, "", fd);
	if (!(buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (NULL);
	while (charchr(cur_prev->previous, '\n') < 0 && (ret = read(fd, buf, BUFFER_SIZE)))
	{
		buf[ret] = 0;
		cur_prev = add_prevs(&prevs, buf, fd);
	}
	free(buf);
	cur = charchr(cur_prev->previous, '\n');
	if (cur >= 0)
	{
		readed = ft_substr(cur_prev->previous, 0, cur + 1);
		shiftstr(&(cur_prev->previous), cur + 1);
	}
	else
	{
		readed = ft_substr(cur_prev->previous, 0, ft_strlen(cur_prev->previous));
		prevs = delete_prev(prevs, fd);
	}
	if (ft_strlen(readed) == 0)
	{
		free(readed);
		return (NULL);
	}
	return (readed);
}
