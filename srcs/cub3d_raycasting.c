/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:53:52 by aymaatou          #+#    #+#             */
/*   Updated: 2020/11/26 14:44:35 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double Normlize_anlge(double angle)
{
     //angle = angle % ((double)(2 * M_PI));
    angle = remainder(angle, (2 * M_PI));
    ;
    if (angle < 0)
        angle = (2 * M_PI) + angle;
    return (angle);
}

double d2r(double degree)
{
  return (degree * (M_PI /180));
}



void cast_rays(void)
{
    float ray_angle = 0;
    int i = 0;
    printf("angle   [%f]\n",g_myplayer.rotationAngle);
    ray_angle = g_myplayer.rotationAngle - d2r(30);
    ft_rayCaster(i, ray_angle);
   
   /* while (i < g_file.width_resolution)
    {
        ft_rayCaster(i, ray_angle);
        ray_angle += d2r(60) / g_file.width_resolution;
        i++;
    }
*/
    
  
}


double ft_distance_between(double x1, double y1, double x2, double y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
void ft_rayCaster(int i, double rayAngle)
{
     int isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
    int isRayFacingUp = isRayFacingDown;

    int isRayFacingRight = rayAngle > (0.5 * M_PI) || rayAngle < (1.5 * M_PI);
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
  //  int HorizWallContent = 0;

    //Calculating the Y cordination
    yinterse = floor(g_myplayer.y / TILE) * TILE;
   
    yinterse += isRayFacingDown ? TILE : 0;
    xinterse = g_myplayer.x + ((yinterse - g_myplayer.y) / tan(rayAngle));

    //ystep , xstep for the Horizontale part
    ystep = TILE;
    ystep *= isRayFacingUp ? -1 : 1;

    xstep = TILE / tan(rayAngle);
    xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorizX = xinterse;
    float nextHorizY = yinterse;

    //Finding Wall Hits at X && Y
    while (nextHorizX >= 0 && nextHorizX <= g_file.width_resolution &&
           nextHorizY >= 0 && nextHorizY <= g_file.height_resolution)
    {
        float x_checkh = nextHorizX;
        float y_checkh = nextHorizY + ((isRayFacingUp == 1) ? -1 : 0);
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
    /********
     * This part is Responsible for the Vertical INTERSECTIONS.
     * 
     * *************/

    int VertWallHit = 0;
    float VertWallHitX = 0;
    float VertWallHitY = 0;

    //Calculating the X cordination
    xinterse = floor(g_myplayer.x / TILE) * TILE;
    xinterse += isRayFacingRight ? TILE : 0;
    //Calculating the Y cordination
    yinterse = g_myplayer.y + ((xinterse - g_myplayer.x) / tan(rayAngle));

    //ystep , xstep for the Vertical part
    xstep = TILE;
    xstep *= isRayFacingLeft ? -1 : 1;

    ystep = TILE / tan(rayAngle);
    ystep *= (isRayFacingUp && xstep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown && xstep < 0) ? -1 : 1;

    float nextVertX = xinterse;
    float nextVertY = yinterse;

    //Finding Wall Hits at X && Y
    while (nextVertX > 0 && nextVertX < g_file.width_resolution &&
           nextVertY > 0 && nextVertY < g_file.height_resolution)
    {
        float x_check = nextVertX + ((isRayFacingLeft == 1) ? -1 : 0);
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
 //   printf ("======Final Calculation Distance OF RAY [%d]=========\nWallHitV X[%f], wallHitV Y[%f]\nWallHitH X[%f], wallHitH Y[%f]\n H Distance [%f]\nV Distance [%f]\n===========================================================\n", i, VertWallHitX,VertWallHitY , HorizWallHitX, HorizWallHitY, HorizDistance, VertDistance);
}









