/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 03:57:24 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/19 03:57:28 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init(void)
{
	g_in.yinterse = 0;
	g_in.xinterse = 0;
	g_in.xstep = 0;
	g_in.ystep = 0;
	g_in.x_check = 0;
	g_in.y_check = 0;
}

void	ft_horizntale_inter(double ray)
{
	init();
	g_in.yinterse = floor(g_myplayer.y / TILE) * TILE;
	g_in.yinterse += (g_cast.israyfacing_down) ? TILE : 0;
	g_in.xinterse = g_myplayer.x + (g_in.yinterse - g_myplayer.y) / tan(ray);
	g_in.ystep = TILE;
	g_in.ystep *= (g_cast.israyfacing_up) ? -1 : 1;
	g_in.xstep = TILE / tan(ray);
	g_in.xstep *= (g_cast.israyfacing_left && g_in.xstep > 0) ? -1 : 1;
	g_in.xstep *= (g_cast.israyfacing_right && g_in.xstep < 0) ? -1 : 1;
	while (g_in.xinterse >= 0 && g_in.xinterse <= (g_file.width * TILE) &&
		g_in.yinterse >= 0 && g_in.yinterse <= (g_file.hight * TILE))
	{
		g_in.x_check = g_in.xinterse;
		g_in.y_check = g_in.yinterse -
			((g_cast.israyfacing_up == 1) ? 1 : 0);
		if (iswall(g_in.x_check, g_in.y_check) == 1)
		{
			g_wallhits.horizwallhit_x = g_in.x_check;
			g_wallhits.horizwallhit_y = g_in.yinterse;
			g_wallhits.horizwallhit = 1;
			break ;
		}
		g_in.xinterse += g_in.xstep;
		g_in.yinterse += g_in.ystep;
	}
}

void	ft_verticale_inter(double ray)
{
	init();
	g_in.xinterse = floor(g_myplayer.x / TILE) * TILE;
	g_in.xinterse += (g_cast.israyfacing_right) ? TILE : 0;
	g_in.yinterse = g_myplayer.y + (g_in.xinterse - g_myplayer.x) * tan(ray);
	g_in.xstep = TILE;
	g_in.xstep *= (g_cast.israyfacing_left) ? -1 : 1;
	g_in.ystep = TILE * tan(ray);
	g_in.ystep *= (g_cast.israyfacing_up && g_in.ystep > 0) ? -1 : 1;
	g_in.ystep *= (g_cast.israyfacing_down && g_in.ystep < 0) ? -1 : 1;
	while (g_in.xinterse >= 0 && g_in.xinterse <= (g_file.width * TILE) &&
		g_in.yinterse >= 0 && g_in.yinterse <= (g_file.hight * TILE))
	{
		g_in.x_check = g_in.xinterse
			- ((g_cast.israyfacing_left == 1) ? 1 : 0);
		g_in.y_check = g_in.yinterse;
		if (iswall(g_in.x_check, g_in.y_check) == 1)
		{
			g_wallhits.vertwallhit_x = g_in.xinterse;
			g_wallhits.vertwallhit_y = g_in.y_check;
			g_wallhits.vertwallhit = 1;
			break ;
		}
		g_in.xinterse += g_in.xstep;
		g_in.yinterse += g_in.ystep;
	}
}
