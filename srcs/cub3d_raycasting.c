/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:53:52 by aymaatou          #+#    #+#             */
/*   Updated: 2020/11/30 17:19:04 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**********************************
 *          3D RENDERING 
 * ******************/

void ft_wall_data(int i)
{
    float dis = g_ray[i].distance * cos(g_ray[i].ray_angle - g_myplayer.rotationAngle);
    float projection = (g_file.width_resolution / 2) / tan(d2r(30));
    float wallHeight = (TILE / dis) * projection;
    int top = (g_file.height_resolution / 2) - ((int)wallHeight / 2);
    int bottom = top + wallHeight;
    g_ray[i].top = top;
    g_ray[i].bottom = bottom;
    g_ray[i].wallheight = wallHeight;
}

void ft_draw_celling(int i)
{
    int a = 0;

    while (a < g_ray[i].top )
    {
        my_mlx_pixel_put(&g_data, i, a, GRAY);
        a++;
    }
    a = g_ray[i].bottom;

    while (a < g_file.height_resolution)
    {
        my_mlx_pixel_put(&g_data, i, a, YELLOW);
        a++;
    }
}
void BuildWall(int i)
{
    int t = g_ray[i].top;
    int b = g_ray[i].bottom;
 
    if (t < 0)
        t =  0;
    if (b > g_file.height_resolution)
        b = g_file.height_resolution;
        
    while (t < b)
    {
        my_mlx_pixel_put(&g_data, i, t, WHITE);
        t++;
    }
}
/***********************************************************************************************************************/

double Normlize_anlge(double angle)
{
    //angle = angle % ((double)(2 * M_PI));
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

    // ft_rayCaster(i, ray_angle);

    while (i < g_file.width_resolution)
    {
        ft_rayCaster(i, ray_angle);
        ray_angle += d2r(60) / g_file.width_resolution;
        i++;
    }
   i = 0;
    while (i < g_file.width_resolution)
    {
        ft_wall_data(i);
        // ft_draw_celling(i);
        // BuildWall(i);
        i++;
    }
      i = 0;
    while (i < g_file.width_resolution)
    {
       // ft_wall_data(i);
        ft_draw_celling(i);
       // BuildWall(i);
        i++;
    }
      i = 0;
    while (i < g_file.width_resolution)
    {
        // ft_wall_data(i);
        // ft_draw_celling(i);
        BuildWall(i);
        i++;
    }



    
}

double ft_distance_between(double x1, double y1, double x2, double y2)
{
    return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}
void ft_rayCaster(int i, double rayAngle)
{
    rayAngle = Normlize_anlge(rayAngle);
    int isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
    int isRayFacingUp = !isRayFacingDown;
    int isRayFacingRight = rayAngle < (0.5 * M_PI) || rayAngle > (1.5 * M_PI);
    int isRayFacingLeft = !isRayFacingRight;

    float yinterse, xinterse;
    float xstep, ystep;
    /********
     * This part is Responsible for the Horizntale INTERSECTIONS.
     * 
     * *************/

    int HorizWallHit = 0;
    float HorizWallHitX = 0;
    float HorizWallHitY = 0;

    //Calculating the Y cordination
    yinterse = floor(g_myplayer.y / TILE) * TILE;

    yinterse += (isRayFacingDown) ? TILE : 0;

    xinterse = g_myplayer.x + (yinterse - g_myplayer.y) / tan(rayAngle);

    //ystep , xstep for the Horizontale part
    ystep = TILE;

    ystep *= (isRayFacingUp) ? -1 : 1;

    xstep = TILE / tan(rayAngle);
    xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorizX = xinterse;
    float nextHorizY = yinterse;

    //Finding Wall Hits at X && Y
    while (nextHorizX >= 0 && nextHorizX <= g_file.width_resolution /*(g_file.width * TILE)*/ &&
           nextHorizY >= 0 && nextHorizY <= g_file.height_resolution /*(g_file.hight * TILE)*/)
    {
        float x_checkh = nextHorizX;
        float y_checkh = nextHorizY + ((isRayFacingUp) ? -1 : 0);


        if (iswall(x_checkh, y_checkh) == 1)
        {
            HorizWallHitX = x_checkh;
            HorizWallHitY = y_checkh;
            HorizWallHit = 1;
            break;
        }
        else
        {
            nextHorizX += xstep;
            nextHorizY += ystep;
        }
    }

    xinterse = 0;
    yinterse = 0;
    xstep = 0;
    ystep = 0;

    /********
     * This part is Responsible for the Vertical INTERSECTIONS.
     * 
     * *************/

    int VertWallHit = 0;
    float VertWallHitX = 0;
    float VertWallHitY = 0;

    //Calculating the X cordination
    xinterse = floor(g_myplayer.x / TILE) * TILE;
    xinterse += (isRayFacingRight) ? TILE : 0;
    //Calculating the Y cordination
    yinterse = g_myplayer.y + (xinterse - g_myplayer.x) * tan(rayAngle);

    //ystep , xstep for the Vertical part
    xstep = TILE;
    xstep *= (isRayFacingLeft) ? -1 : 1;

    ystep = TILE * tan(rayAngle);
    ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

    float nextVertX = xinterse;
    float nextVertY = yinterse;

    //Finding Wall Hits at X && Y
    while (nextVertX >= 0 && nextVertX <= g_file.width_resolution /*(g_file.width * TILE)*/ &&
           nextVertY >= 0 && nextVertY <= g_file.height_resolution /*(g_file.hight * TILE)*/)
    {
        float x_check = nextVertX + ((isRayFacingLeft) ? -1 : 0);
        float y_check = nextVertY;

                                                           
        if (iswall(x_check, y_check) == 1)
        {
            VertWallHitX = x_check;
            VertWallHitY = y_check;
            VertWallHit = 1;
            break;
        }
        else
        {
            nextVertX += xstep;
            nextVertY += ystep;
        }
    }
    /**********************
     * 
     * Calculation the Vertical && Horizontal Hits and choosing the colosest one.
     * 
     */

    float HorizDistance = HorizWallHit ? ft_distance_between(g_myplayer.x, g_myplayer.y, HorizWallHitX, HorizWallHitY) : INT_MAX;

    float VertDistance = VertWallHit ? ft_distance_between(g_myplayer.x, g_myplayer.y, VertWallHitX, VertWallHitY) : INT_MAX;

    // printf("======H[%f]=====V[%f]====\n", HorizDistance, VertDistance);
    float finalDistace = 0;

    if (HorizDistance > VertDistance)
    {
        finalDistace = VertDistance;
        g_ray[i].wasVerticale = 1;
        g_ray[i].wallHitx = VertWallHitX;
        g_ray[i].wallHity = VertWallHitY;
    }
    else
    {
        finalDistace = HorizDistance;
        //puts("FOUND HORIZ HIT !!!!") ;
        g_ray[i].wasVerticale = 0;
        g_ray[i].wallHitx = HorizWallHitX;
        g_ray[i].wallHity = HorizWallHitY;
    }
    g_ray[i].ray_angle = rayAngle;
    g_ray[i].distance = finalDistace;
    g_ray[i].rayfacingUP = isRayFacingUp;
    g_ray[i].rayfacingDown = isRayFacingDown;
    draw_line(g_myplayer.x, g_myplayer.y, g_ray[i].wallHitx, g_ray[i].wallHity);
}
