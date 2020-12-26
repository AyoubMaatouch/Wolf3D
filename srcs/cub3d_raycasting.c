/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:53:52 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/24 16:03:57 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_sprit_rendring(void)
{
	int i;

	i = 0;
	while (i < g_sp_index)
	{
		ft_sp_data(i);
		i++;
	}
	sort();
	i = 0;
	while (i < g_sp_index)
	{
		draw_sprite(i);
		i++;
	}
}

void	cast_rays(void)
{
	float	ray_angle;
	int		i;

	i = 0;
	ray_angle = g_myplayer.rotationAngle - d2r(30);
	while (i <= g_file.width_resolution)
	{
		ft_ray(i, ray_angle);
		ray_angle += d2r(60) / g_file.width_resolution;
		i++;
	}
	i = 0;
	while (i < g_file.width_resolution)
	{
		ft_wall_data(i);
		ft_draw_celling(i);
		ft_buildwall(i);
		i++;
	}
	ft_sprit_rendring();
}

void	ft_init_var(void)
{
	g_cast.isRayFacingDown = 0;
	g_cast.isRayFacingUp = 0;
	g_cast.isRayFacingRight = 0;
	g_cast.isRayFacingLeft = 0;
	g_wallhits.HorizWallHitX = 0;
	g_wallhits.HorizWallHitY = 0;
	g_wallhits.HorizWallHit = 0;
	g_wallhits.VertWallHitX = 0;
	g_wallhits.VertWallHitY = 0;
	g_wallhits.VertWallHit = 0;
}

void	ft_ray(int i, double rayangle)
{
	rayangle = normlize_anlge(rayangle);
	ft_init_var();
	g_cast.isRayFacingDown = rayangle > 0 && rayangle < M_PI;
	g_cast.isRayFacingUp = !g_cast.isRayFacingDown;
	g_cast.isRayFacingRight = rayangle < (0.5 * M_PI)
		|| rayangle >= (1.5 * M_PI);
	g_cast.isRayFacingLeft = !g_cast.isRayFacingRight;
	ft_horizntale_inter(rayangle);
	ft_verticale_inter(rayangle);
	ft_get_distance(i);
	g_ray[i].ray_angle = rayangle;
	g_ray[i].rayfacingUP = g_cast.isRayFacingUp;
	g_ray[i].rayfacingDown = g_cast.isRayFacingDown;
	g_ray[i].rayfacingRight = g_cast.isRayFacingRight;
	g_ray[i].rayfacingLeft = g_cast.isRayFacingLeft;
}

void	ft_get_distance(int i)
{
	float horizdistance;
	float vertdistance;

	horizdistance = g_wallhits.HorizWallHit ? ft_distance_between(g_myplayer.x,
		g_myplayer.y,
			g_wallhits.HorizWallHitX, g_wallhits.HorizWallHitY)
				: INT_MAX;
	vertdistance = g_wallhits.VertWallHit ? ft_distance_between(g_myplayer.x,
		g_myplayer.y, g_wallhits.VertWallHitX, g_wallhits.VertWallHitY)
			: INT_MAX;
	if (horizdistance < vertdistance)
	{
		g_ray[i].distance = horizdistance;
		g_ray[i].wasVerticale = 0;
		g_ray[i].wallHitx = g_wallhits.HorizWallHitX;
		g_ray[i].wallHity = g_wallhits.HorizWallHitY;
	}
	else
	{
		g_ray[i].distance = vertdistance;
		g_ray[i].wasVerticale = 1;
		g_ray[i].wallHitx = g_wallhits.VertWallHitX;
		g_ray[i].wallHity = g_wallhits.VertWallHitY;
	}
}
