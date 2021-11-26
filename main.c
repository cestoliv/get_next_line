/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:07:53 by ocartier          #+#    #+#             */
/*   Updated: 2021/11/26 11:18:35 by ocartier         ###   ########lyon.fr   */
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
	int fd = open("empty.test", O_RDONLY);
	char *str;
	while (cur < 5)
	{
		str = get_next_line(fd);
		printf("%s(\\n)\n", str);
		cur++;
	}

	printf("\n AUTRE\n\n");

	cur = 0;
	int fd2 = open("file2.test", O_RDONLY);
	while (cur < 14)
	{
		str = get_next_line(fd2);
		printf("%s(\\n)\n", str);
		cur++;
	}

	printf("\n RE AUTRE\n\n");
	str = get_next_line(fd);
	printf("%s(\\n)\n", str);
	
	close(fd);
	close(fd2);
}
