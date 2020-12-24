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

void ft_horizntale_inter(double rayAngle)
{
    float yinterse, xinterse;
    float xstep, ystep;
    
    g_wallhits.HorizWallHit = 0;
    yinterse = floor(g_myplayer.y / TILE) * TILE;
    yinterse += (g_cast.isRayFacingDown) ? TILE : 0;
    xinterse = g_myplayer.x + (yinterse - g_myplayer.y) / tan(rayAngle);
    ystep = TILE;
    ystep *= (g_cast.isRayFacingUp) ? -1 : 1;
    xstep = TILE / tan(rayAngle);
    xstep *= (g_cast.isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (g_cast.isRayFacingRight && xstep < 0) ? -1 : 1;
    while (xinterse >= 0 && xinterse <= (g_file.width * TILE) &&
           yinterse >= 0 && yinterse <= (g_file.hight * TILE))
    {
        float x_checkh = xinterse;
        float y_checkh = yinterse - ((g_cast.isRayFacingUp == 1) ? 1 : 0);
       
        if (iswall(x_checkh, y_checkh) == 1)
        {
            g_wallhits.HorizWallHitX = x_checkh;
            g_wallhits.HorizWallHitY = yinterse;
            g_wallhits.HorizWallHit = 1;
            break;
        }
        xinterse += xstep;
        yinterse += ystep;
    }
}

void ft_verticale_inter(double rayAngle)
{
    float xinterse;
    float yinterse;
    float xstep;
    float ystep;

    xinterse = floor(g_myplayer.x / TILE) * TILE;
    xinterse += (g_cast.isRayFacingRight) ? TILE : 0;
    yinterse = g_myplayer.y + (xinterse - g_myplayer.x) * tan(rayAngle);
    xstep = TILE;
    xstep *= (g_cast.isRayFacingLeft) ? -1 : 1;
    ystep = TILE * tan(rayAngle);
    ystep *= (g_cast.isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (g_cast.isRayFacingDown && ystep < 0) ? -1 : 1;
    while (xinterse >= 0 && xinterse <= (g_file.width * TILE) &&
           yinterse >= 0 && yinterse <= (g_file.hight * TILE))
    {
        float x_check = xinterse - ((g_cast.isRayFacingLeft == 1) ? 1 : 0);
        float y_check = yinterse;

        if (iswall(x_check, y_check) == 1)
        {
            g_wallhits.VertWallHitX = xinterse;
            g_wallhits.VertWallHitY = y_check;
            g_wallhits.VertWallHit = 1;
            break;
        }
        xinterse += xstep;
        yinterse += ystep;
    }
}