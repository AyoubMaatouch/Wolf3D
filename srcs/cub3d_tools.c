/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:51:27 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/08 18:19:27 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;
	
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int iswall(float x, float y)
{
	
	if ((int)x >= g_file.width * TILE || (int)x <= 0 ||
		(int)y >= g_file.hight * TILE || (int)y <= 0)
		return (1);
	return (g_file.map[(int)(y / TILE)][(int)(x / TILE)] - '0');
}

void 	*ft_error(char *str)
{
	ft_putstr(str);
	exit(0);
}