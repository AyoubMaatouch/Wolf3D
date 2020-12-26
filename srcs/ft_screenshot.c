/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screenshot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:22:53 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/10 10:22:55 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_create_2(int fd)
{
	int i;
	int j;
	int pos;

	i = 0;
	pos = 0;
	write(fd, &i, sizeof(int));
	write(fd, &i, sizeof(int));
	write(fd, &i, sizeof(int));
	write(fd, &i, sizeof(int));
	write(fd, &i, sizeof(int));
	write(fd, &i, sizeof(int));
	i = g_file.height_resolution - 1;
	j = 0;
	while (i >= 0)
	{
		j = 0;
		while (j < g_file.width_resolution)
		{
			pos = (j + g_file.width_resolution * i) * 4;
			write(fd, (unsigned int *)(g_data.addr + pos), 4);
			j++;
		}
		i--;
	}
}

void	ft_create_screenshot(void)
{
	int fd;
	int i;

	fd = open("first_rendered_image.bmp", O_RDWR | O_TRUNC | O_CREAT, 0666);
	write(fd, "BM", 2);
	i = g_file.height_resolution * g_file.width_resolution * 4 + 54;
	write(fd, &i, sizeof(int));
	i = 0;
	write(fd, &i, 2);
	write(fd, &i, 2);
	i = 54;
	write(fd, &i, sizeof(int));
	i = 40;
	write(fd, &i, 4);
	write(fd, &g_file.width_resolution, sizeof(int));
	write(fd, &g_file.height_resolution, sizeof(int));
	i = 1;
	write(fd, &i, 2);
	i = 32;
	write(fd, &i, 2);
	ft_create_2(fd);
	close(fd);
	exit(0);
}
