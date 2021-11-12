/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:07:53 by ocartier          #+#    #+#             */
/*   Updated: 2021/11/12 16:28:41 by ocartier         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int cur = 0;
	int fd = open("file.test", O_RDONLY);
	char *str;
	while (cur < 3)
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
		cur++;
	}
	close(fd);
}
