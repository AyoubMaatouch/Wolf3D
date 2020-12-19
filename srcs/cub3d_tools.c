/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:51:27 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/19 05:05:42 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	iswall(float x, float y)
{
	int int_x;
	int int_y;

	int_x = x / TILE;
	int_y = y / TILE;
	if (int_y < 0 || int_y >= g_file.hight || int_x < 0 || int_x >
			(int)ft_strlen(g_file.map[int_y]))
		return (1);
	if (g_file.map[int_y][int_x] == '1')
		return (1);
	else if (g_file.map[int_y][int_x] == '2')
		return (2);
	else if (g_file.map[int_y][int_x] == ' ')
		return (1);
	return (0);
}

void	*ft_error(char *str)
{
	ft_putstr(str);
	exit(0);
}

double	normlize_anlge(double angle)
{
	angle = remainder(angle, (2 * M_PI));
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

double	d2r(double degree)
{
	return (degree * (M_PI / 180));
}
