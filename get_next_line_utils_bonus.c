/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:50:24 by ocartier          #+#    #+#             */
/*   Updated: 2021/11/25 14:13:56 by ocartier         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	cur;

	cur = 0;
	while (s[cur])
		cur++;
	return (cur);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	cur;

	if (size == 0)
		return (ft_strlen(src));
	cur = 0;
	while (src[cur] && cur < (size - 1))
	{
		dst[cur] = src[cur];
		cur++;
	}
	dst[cur] = 0;
	return (ft_strlen(src));
}

long	charchr(const char *s, char c)
{
	long	cur;

	cur = 0;
	while (s[cur])
	{
		if (s[cur] == (unsigned char)c)
			return (cur);
		cur++;
	}
	if (s[cur] == (unsigned char)c)
		return (cur);
	return (-1);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, s1_len + 1);
	ft_strlcpy((join + s1_len), s2, s2_len + 1);
	free(s1);
	return (join);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	new_len;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		sub = malloc(sizeof(char));
		sub[0] = 0;
		if (!sub)
			return (NULL);
	}
	else
	{
		new_len = ft_strlen(s + start);
		if (!(new_len < len))
			new_len = len;
		sub = (char *)malloc((new_len + 1) * sizeof(char));
		if (!sub)
			return (NULL);
		sub[new_len] = 0;
		while (new_len-- > 0)
			sub[new_len] = s[start + new_len];
	}
	return (sub);
}
