/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:53:52 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/08 18:20:13 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"



/***********************************************************************************************************************/



void cast_rays(void)
{
    float ray_angle = 0;
    int i = 0;
    ray_angle = g_myplayer.rotationAngle - d2r(30);

    while (i <= g_file.width_resolution)
    {
        //  ft_rayCaster(i, ray_angle);
        ft_ray(i, ray_angle);
        ray_angle += d2r(60) / g_file.width_resolution;
        i++;
    }
    i = 0;
    while (i < g_file.width_resolution)
    {
        ft_wall_data(i);
        ft_draw_celling(i);
        BuildWall(i);
        i++;
    }
    
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

double ft_distance_between(double x1, double y1, double x2, double y2)
{
    return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

/********************************************************************************************
 *                                        Function Normé
 * **************************************************************************************/

void ft_init_var(void)
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

void ft_ray(int i, double rayAngle)
{
    rayAngle = Normlize_anlge(rayAngle);
    ft_init_var();
    g_cast.isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
    g_cast.isRayFacingUp = !g_cast.isRayFacingDown;
    g_cast.isRayFacingRight = rayAngle < (0.5 * M_PI) || rayAngle >= (1.5 * M_PI);
    g_cast.isRayFacingLeft = !g_cast.isRayFacingRight;

    ft_horizntale_inter(rayAngle);
    ft_verticale_inter(rayAngle);
    ft_get_distance(rayAngle, i);
}


void ft_get_distance(double rayAngle, int i)
{
    float HorizDistance = g_wallhits.HorizWallHit ? ft_distance_between(g_myplayer.x, g_myplayer.y,
     g_wallhits.HorizWallHitX, g_wallhits.HorizWallHitY) : INT_MAX;

    float VertDistance = g_wallhits.VertWallHit ? ft_distance_between(g_myplayer.x, g_myplayer.y,
     g_wallhits.VertWallHitX, g_wallhits.VertWallHitY) : INT_MAX;


    if (HorizDistance < VertDistance)
    {
        g_ray[i].distance  = HorizDistance;
        g_ray[i].wasVerticale = 0;
        g_ray[i].wallHitx = g_wallhits.HorizWallHitX;
        g_ray[i].wallHity = g_wallhits.HorizWallHitY;
    }
    else
    {
        g_ray[i].distance  = VertDistance;
        g_ray[i].wasVerticale = 1;
        g_ray[i].wallHitx = g_wallhits.VertWallHitX;
        g_ray[i].wallHity = g_wallhits.VertWallHitY;
    }
    g_ray[i].ray_angle = rayAngle;
    g_ray[i].rayfacingUP = g_cast.isRayFacingUp;
    g_ray[i].rayfacingDown = g_cast.isRayFacingDown;
    g_ray[i].rayfacingRight = g_cast.isRayFacingRight;
    g_ray[i].rayfacingLeft = g_cast.isRayFacingLeft;
}
