/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:52:09 by ocartier          #+#    #+#             */
/*   Updated: 2021/11/17 22:00:56 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_UTILS_H
# define GET_NEXT_LINE_UTILS_H
# include <unistd.h>

long	charchr(const char *s, char c);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	shiftstr(char **str, size_t start);
#endif
