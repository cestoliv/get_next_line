/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:04:59 by ocartier          #+#    #+#             */
/*   Updated: 2021/11/25 14:39:25 by ocartier         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
void	shiftstr(char **str, size_t start)
{
	char	*tmp;

	tmp = *str;
	*str = ft_substr(*str, start, ft_strlen(*str));
	free(tmp);
}

prev_list	*new_prevs(int fd)
{
	prev_list *elem;

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
	prev_list *elem;

	while ((*prevs)->next)
	{
		if ((*prevs)->fd == fd)
		{
			(*prevs)->previous = ft_strjoin((*prevs)->previous, buf);
			return (*prevs);
		}
		*(prevs) = (*prevs)->next;
	}
	elem = new_prevs(fd);
	if (!elem)
		return (NULL);
	free(elem->previous);
	elem->previous = ft_substr(buf, 0, ft_strlen(buf));
	(*prevs)->next = elem;
	return (elem);
}

void	remove_prevs(prev_list **prevs, int fd)
{
	prev_list	*to_remove;
	prev_list	*curr_elem;

	curr_elem = (*prevs);
	if (curr_elem && curr_elem->fd == fd)
	{
		(*prevs) = (*prevs)->next;
		free(curr_elem->previous);
		free(curr_elem);
	}
	curr_elem = (*prevs);
	while (curr_elem && curr_elem->next)
	{
		if (curr_elem->next->fd == fd)
		{
			to_remove = curr_elem->next;
			curr_elem->next = curr_elem->next->next;
			free(to_remove->previous);
			free(to_remove);
		}
		else
			curr_elem = curr_elem->next;
	}
}

char	*get_next_line(int fd)
{
	ssize_t				ret;
	char				*buf;
	int					cur;
	char				*readed;
	static prev_list	*prevs = NULL;
	prev_list			*cur_prev = NULL;

	if (!BUFFER_SIZE || BUFFER_SIZE < 1 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!prevs)
	{
		prevs = new_prevs(fd);
		if (!prevs)
			return (NULL);
	}
	if (!(buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (NULL);
	while (charchr(prevs->previous, '\n') < 0 && (ret = read(fd, buf, BUFFER_SIZE)))
	{
		buf[ret] = 0;
		cur_prev = add_prevs(&prevs, buf, fd);
	}
	free(buf);
	cur = charchr(prevs->previous, '\n');
	if (cur >= 0)
	{
		readed = ft_substr(prevs->previous, 0, cur + 1);
		shiftstr(&(prevs->previous), cur + 1);
	}
	else
	{
		readed = ft_substr(prevs->previous, 0, ft_strlen(prevs->previous));
		//free(previous);
		//previous = NULL;
		remove_prevs(&prevs, fd);
	}
	if (ft_strlen(readed) == 0)
	{
		free(readed);
		return (NULL);
	}
	return (readed);
}
