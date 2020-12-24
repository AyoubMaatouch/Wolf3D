/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3d_rendring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 03:59:03 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/19 03:59:06 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** 3D RENDERING
*/

void	ft_wall_data(int i)
{
	float	correct_dis;
	float	projection;
	float	wallheight;
	int		top;
	int		bottom;

	correct_dis = g_ray[i].distance *
		cos(g_ray[i].ray_angle - g_myplayer.rotationAngle);
	projection = (g_file.width_resolution / 2) / tan(d2r(30));
	wallheight = (TILE / correct_dis) * projection;
	top = (g_file.height_resolution / 2)
		- ((int)wallheight / 2) + (g_myplayer.look);
	bottom = top + (int)wallheight;
	g_ray[i].top = top > 0 || top < g_file.height_resolution ?
		top : g_ray[i].top;
	g_ray[i].bottom = bottom;
	g_ray[i].wallheight = wallheight;
}

void	ft_draw_celling(int i)
{
	int start;

	start = 0;
	while (start < g_ray[i].top)
	{
		my_mlx_pixel_put(&g_data, i, start, g_file.cilng);
		start++;
	}
	start = g_ray[i].bottom;
	while (start < g_file.height_resolution)
	{
		my_mlx_pixel_put(&g_data, i, start, g_file.flor);
		start++;
	}
}

int		get_side(int i)
{
	int nb;

	nb = 0;
	if (g_ray[i].rayfacingUP && !g_ray[i].wasVerticale)
		nb = 0;
	if (g_ray[i].rayfacingDown && !g_ray[i].wasVerticale)
		nb = 1;
	if (g_ray[i].rayfacingLeft && g_ray[i].wasVerticale)
		nb = 2;
	if (g_ray[i].rayfacingRight && g_ray[i].wasVerticale)
		nb = 3;
	return (nb);
}

void	ft_buildwall(int i)
{
	int t;
	int b;
	int offeset_y;
	int offeset_x;
	int nb;

	nb = get_side(i);
	t = g_ray[i].top;
	b = g_ray[i].bottom;
	if (g_ray[i].wasVerticale)
		 offeset_x = (int)g_ray[i].wallHity % TILE;
	else
		offeset_x = (int)g_ray[i].wallHitx % TILE;
	if (t < 0)
		t = 0;
	if (b > g_file.height_resolution)
		b = g_file.height_resolution;
	while (t < b)
	{
		offeset_y = (t - g_ray[i].top) * ((float)TILE / g_ray[i].wallheight);
		my_mlx_pixel_put(&g_data, i, t,
			g_txt[nb].data[(g_txt[nb].img_width * offeset_y) + offeset_x]);
		t++;
	}
}
