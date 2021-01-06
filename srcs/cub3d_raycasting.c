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
	g_ray = malloc(sizeof(t_ray) * 3200);
	ray_angle = g_myplayer.rotation_angle - d2r(30);
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
	g_ray = NULL;
	free(g_ray);
}

void	ft_init_var(void)
{
	g_cast.israyfacing_down = 0;
	g_cast.israyfacing_up = 0;
	g_cast.israyfacing_right = 0;
	g_cast.israyfacing_left = 0;
	g_wallhits.horizwallhit_x = 0;
	g_wallhits.horizwallhit_y = 0;
	g_wallhits.horizwallhit = 0;
	g_wallhits.vertwallhit_x = 0;
	g_wallhits.vertwallhit_y = 0;
	g_wallhits.vertwallhit = 0;
}

void	ft_ray(int i, double rayangle)
{
	rayangle = normlize_anlge(rayangle);
	ft_init_var();
	g_cast.israyfacing_down = rayangle > 0 && rayangle < M_PI;
	g_cast.israyfacing_up = !g_cast.israyfacing_down;
	g_cast.israyfacing_right = rayangle < (0.5 * M_PI)
		|| rayangle >= (1.5 * M_PI);
	g_cast.israyfacing_left = !g_cast.israyfacing_right;
	ft_horizntale_inter(rayangle);
	ft_verticale_inter(rayangle);
	ft_get_distance(i);
	g_ray[i].ray_angle = rayangle;
	g_ray[i].rayfacing_up = g_cast.israyfacing_up;
	g_ray[i].rayfacing_down = g_cast.israyfacing_down;
	g_ray[i].rayfacing_right = g_cast.israyfacing_right;
	g_ray[i].rayfacing_left = g_cast.israyfacing_left;
}

void	ft_get_distance(int i)
{
	float horizdistance;
	float vertdistance;

	horizdistance = g_wallhits.horizwallhit ? ft_distance_between(g_myplayer.x,
		g_myplayer.y,
			g_wallhits.horizwallhit_x, g_wallhits.horizwallhit_y)
				: INT_MAX;
	vertdistance = g_wallhits.vertwallhit ? ft_distance_between(g_myplayer.x,
		g_myplayer.y, g_wallhits.vertwallhit_x, g_wallhits.vertwallhit_y)
			: INT_MAX;
	if (horizdistance < vertdistance)
	{
		g_ray[i].distance = horizdistance;
		g_ray[i].was_verticale = 0;
		g_ray[i].wall_hit_x = g_wallhits.horizwallhit_x;
		g_ray[i].wall_hit_y = g_wallhits.horizwallhit_y;
	}
	else
	{
		g_ray[i].distance = vertdistance;
		g_ray[i].was_verticale = 1;
		g_ray[i].wall_hit_x = g_wallhits.vertwallhit_x;
		g_ray[i].wall_hit_y = g_wallhits.vertwallhit_y;
	}
}
