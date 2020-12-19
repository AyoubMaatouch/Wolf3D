/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3D_rendring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 03:59:03 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/19 03:59:06 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
/**********************************
 *          3D RENDERING 
 * ********************************/
void ft_wall_data(int i)
{
    float correct_dis = g_ray[i].distance * cos(g_ray[i].ray_angle - g_myplayer.rotationAngle);
    float projection = (g_file.width_resolution / 2) / tan(d2r(30));
    float wallHeight = (TILE / correct_dis) * projection;
    int top = (g_file.height_resolution / 2) - ((int)wallHeight / 2 )  + (g_myplayer.look ); // here yo can add the up and down configuration
    int bottom = top + (int)wallHeight;
  //  printf("T[%d]\n", top);
    g_ray[i].top = top > 0 || top < g_file.height_resolution ? top :  g_ray[i].top;
    g_ray[i].bottom = bottom;
    g_ray[i].wallheight = wallHeight;
}

void ft_draw_celling(int i)
{
    int a = 0;

    while (a < g_ray[i].top)
    {
        my_mlx_pixel_put(&g_data, i, a, g_file.cilng);
        a++;
    }
    a = g_ray[i].bottom;

    while (a < g_file.height_resolution)
    {
        my_mlx_pixel_put(&g_data, i, a, g_file.flor);
        a++;
    }
}

int get_side(int i)
{
    int nb = 0;
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

void BuildWall(int i)
{
    int t = g_ray[i].top;
    int b = g_ray[i].bottom;

    //     /************
    //      *  playing around with textures
    //      * ***********/

    int offeset_y, offeset_x;
    if (g_ray[i].wasVerticale)
    {
        offeset_x = (int)g_ray[i].wallHity % TILE;
    }
    else
    {
        offeset_x = (int)g_ray[i].wallHitx % TILE;
    }

    int nb = get_side(i);
    /************************************************/
    if (t < 0)
        t = 0;
    if (b > g_file.height_resolution)
        b = g_file.height_resolution;
    while (t < b)
    {
        offeset_y = (t - g_ray[i].top) * ((float)TILE / g_ray[i].wallheight);
        unsigned int color = g_txt[nb].data[(g_txt[nb].img_width * offeset_y) + offeset_x];

        my_mlx_pixel_put(&g_data, i, t, color);
        t++;
    }
}