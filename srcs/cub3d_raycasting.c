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

/**********************************
 *          3D RENDERING 
 * ********************************/

void ft_wall_data(int i)
{
    float correct_dis = g_ray[i].distance * cos(g_ray[i].ray_angle - g_myplayer.rotationAngle);
    float projection = (g_file.width_resolution / 2) / tan(d2r(30));
    float wallHeight = (TILE / correct_dis) * projection;
    int top = (g_file.height_resolution / 2) - ((int)wallHeight / 2);
    int bottom = top + (int)wallHeight;
    g_ray[i].top = top;
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
/***********************************************************************************************************************/

double Normlize_anlge(double angle)
{
    angle = remainder(angle, (2 * M_PI));
    if (angle < 0)
        angle = (2 * M_PI) + angle;
    return (angle);
}

double d2r(double degree)
{
    return (degree * (M_PI / 180));
}

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

      int index = 0;
    //   puts("============================NOT SORTED================================");
    // while (index < g_sp_index)
    // {
        
    //     printf ("SP %d x[%f] y[%f] distance[%f] size[%f]\n", index, g_sprite[index].x, g_sprite[index].y,g_sprite[index].dis, g_sprite[i].size );
       
    //     index++;
    // }
    // puts("===========================================================================");
    
      index = 0;
     
   i = 0;
    while (i < 2)
    {
        printf ("a SIZE[%f]\n",  g_sprite[i].size);
        ft_sp_data (i);
        i++;
    }
    //sort();
//     puts("===============================SORTED================================");
//     while (index < g_sp_index)
//     {
        
//         printf ("SP %d x[%f] y[%f] distance[%f] size[%f]\n", index, g_sprite[index].x, g_sprite[index].y,g_sprite[index].dis, g_sprite[i].size);
       
//         index++;
//     }
//     puts("===========================================================================");
    i = 0;
	

    while (i < 2)
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
void ft_horizntale_inter(double rayAngle)
{
    float yinterse, xinterse;
    float xstep, ystep;
    int s_index;

    s_index = -1;
    g_wallhits.HorizWallHit = 0;
    /********
     * This part is Responsible for the Horizntale INTERSECTIONS.
     * *************/

    //Calculating the Y cordination
    yinterse = floor(g_myplayer.y / TILE) * TILE;
    yinterse += (g_cast.isRayFacingDown) ? TILE : 0;
    xinterse = g_myplayer.x + (yinterse - g_myplayer.y) / tan(rayAngle);
    //ystep , xstep for the Horizontale part
    ystep = TILE;
    ystep *= (g_cast.isRayFacingUp) ? -1 : 1;
    xstep = TILE / tan(rayAngle);
    xstep *= (g_cast.isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (g_cast.isRayFacingRight && xstep < 0) ? -1 : 1;

    //Finding Wall Hits at X && Y
    while (xinterse >= 0 && xinterse <= (g_file.width * TILE) &&
           yinterse >= 0 && yinterse <= (g_file.hight * TILE))
    {
        float x_checkh = xinterse;
        float y_checkh = yinterse - ((g_cast.isRayFacingUp == 1) ? 1 : 0);
         if (iswall(x_checkh, y_checkh) == 2 && ++s_index <= g_sp_index)
            ft_get_sp_pos(x_checkh, y_checkh, s_index);
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
    float xinterse = 0;
    float yinterse = 0;
    float xstep = 0;
    float ystep = 0;
   int s_index = 0;
    /********
     * This part is Responsible for the Vertical INTERSECTIONS.
     * 
     * *************/

    //Calculating the X cordination
    xinterse = floor(g_myplayer.x / TILE) * TILE;
    xinterse += (g_cast.isRayFacingRight) ? TILE : 0;
    //Calculating the Y cordination
    yinterse = g_myplayer.y + (xinterse - g_myplayer.x) * tan(rayAngle);

    //ystep , xstep for the Vertical part
    xstep = TILE;
    xstep *= (g_cast.isRayFacingLeft) ? -1 : 1;
    ystep = TILE * tan(rayAngle);
    ystep *= (g_cast.isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (g_cast.isRayFacingDown && ystep < 0) ? -1 : 1;

    //Finding Wall Hits at X && Y
    while (xinterse >= 0 && xinterse <= (g_file.width * TILE) &&
           yinterse >= 0 && yinterse <= (g_file.hight * TILE))
    {
        float x_check = xinterse - ((g_cast.isRayFacingLeft == 1) ? 1 : 0);
        float y_check = yinterse;
        if (iswall(x_check, y_check) == 2 && ++s_index <= g_sp_index)
            ft_get_sp_pos(x_check, y_check, s_index);
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
