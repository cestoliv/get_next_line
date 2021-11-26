/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:04:59 by ocartier          #+#    #+#             */
/*   Updated: 2021/11/26 12:55:25 by ocartier         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

t_prev_list	*new_prevs(int fd)
{
	t_prev_list	*elem;

	elem = malloc(sizeof(t_prev_list));
	if (!elem)
		return (NULL);
	elem->fd = fd;
	elem->prev = (char *)malloc(sizeof(char));
	if (elem->prev == NULL)
		return (NULL);
	elem->prev[0] = 0;
	elem->next = NULL;
	return (elem);
}

t_prev_list	*add_prevs(t_prev_list **prevs, char *buf, int fd)
{
	t_prev_list	*curr;
	t_prev_list	*elem;

	curr = *prevs;
	while (curr)
	{
		if (curr->fd == fd)
		{
			curr->prev = ft_strjoin(curr->prev, buf);
			return (curr);
		}
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	elem = new_prevs(fd);
	if (!elem)
		return (NULL);
	elem->prev = ft_strjoin(elem->prev, buf);
	curr->next = elem;
	return (elem);
}

t_prev_list	*delete_prev(t_prev_list *prevs, int fd)
{
	t_prev_list	*next;

	if (prevs->fd == fd)
	{
		next = prevs->next;
		free(prevs->prev);
		free(prevs);
		return (next);
	}
	else
	{
		prevs->next = delete_prev(prevs->next, fd);
		return (prevs);
	}
}

t_prev_list	*get_prev(t_prev_list **prevs, int fd)
{
	t_prev_list			*cur_prev;
	ssize_t				ret;
	char				*buf;

	if (!BUFFER_SIZE || BUFFER_SIZE < 1 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!(*prevs))
		*prevs = new_prevs(fd);
	if (!(*prevs))
		return (NULL);
	cur_prev = add_prevs(prevs, "", fd);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret)
	{
		buf[ret] = 0;
		cur_prev = add_prevs(prevs, buf, fd);
		if (charchr(cur_prev->prev, '\n') >= 0)
			break ;
		ret = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (cur_prev);
}

char	*get_next_line(int fd)
{
	static t_prev_list	*prevs = NULL;
	t_prev_list			*cur_prev;
	char				*readed;
	long				cur;

	cur_prev = get_prev(&prevs, fd);
	if (!cur_prev)
		return (NULL);
	cur = charchr(cur_prev->prev, '\n');
	if (cur >= 0)
	{
		readed = ft_substr(cur_prev->prev, 0, cur + 1);
		shiftstr(&(cur_prev->prev), cur + 1);
	}
	else
	{
		readed = ft_substr(cur_prev->prev, 0, ft_strlen(cur_prev->prev));
		prevs = delete_prev(prevs, fd);
	}
	if (ft_strlen(readed) == 0)
	{
		free(readed);
		return (NULL);
	}
	return (readed);
}
