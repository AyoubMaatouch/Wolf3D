/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:03:12 by aymaatou          #+#    #+#             */
/*   Updated: 2020/11/26 14:32:43 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void line (float X, float Y)
{
  int i = 0;
  
  while (i < 20) 
    { 
      my_mlx_pixel_put(&g_data,  X + (cos(g_myplayer.rotationAngle) * i), Y + (sin(g_myplayer.rotationAngle) * i), YELLOW);
      /* if (iswall( X + (cos(g_myplayer.rotationAngle) * i), Y + (sin(g_myplayer.rotationAngle) * i)) == 1)
         break;*/
      i++;
    }
}

void   draw_line(int x0,int y0,int x1,int y1)
{
//Bresenham's Line Drawing Algorithm
  int dx =  abs (x1 - x0);
  int dy = -abs (y1 - y0);
  int sx = x0 < x1 ? 1 : -1;
  int sy = y0 < y1 ? 1 : -1;
  int p = dx + dy; //p step
  int p2;
  while(1)
  {
    //setPixel (x0,y0);
    //mlx_pixel_put(mlx, window, x0, y0, BLUE);
   // img_data[(WINDOW_WIDTH * y0) + x0] = RED;
    my_mlx_pixel_put(&g_data, x0, y0, YELLOW);
    if (x0 == x1 && y0 == y1)
        break;
    p2 = 2 * p;
    if (p2 >= dy)
    {
        p += dy;
        x0 += sx;
    } // e_xy+e_x > 0
    if (p2 <= dx)
    {
        p += dx;
        y0 += sy;
    }  //
  }
}

void square(int y, int x, int color)
{
  int save = y;
  int lenx = 0;
  int leny = 0;

  while (lenx < TILE)
  {
    while (leny < TILE)
    {
      my_mlx_pixel_put(&g_data, y, x, color);
      leny++;
      y++;
    }
    leny = 0;
    y = save;
    lenx++;
    x++;
  }
}
void  circle (float x, float y)
{
  float angle = 0;
  
  while (angle <= 360)
  {
    x += 2 * cos(angle);
    y += 2 * sin(angle);
    my_mlx_pixel_put(&g_data,  x, y, YELLOW);
  angle++;
  }
}
void ft_drw_player (char view)
{
  if (view == 'N')
       {
         //g_myplayer.rotationAngle = 270.0 * (M_PI / 180);
         circle (g_myplayer.x, g_myplayer.y);
         //line(g_myplayer.x, g_myplayer.y);
         
           draw_line(g_myplayer.x, g_myplayer.y, g_myplayer.x + (cos(g_myplayer.rotationAngle)  * 30), g_myplayer.y + (sin(g_myplayer.rotationAngle)  * 30));
         
       } 
        
      
}

void ft_map()
{
  int i = 0;
  size_t j = 0;
  
  while ( i < g_file.hight)
  {
    j = 0;
    while (j < ft_strlen(g_file.map[i]))
    {
    int tx = j * TILE;
    int ty = i * TILE;
      if (g_file.map[i][j] == '1')
        square(tx, ty, PURPLE);
      if (g_file.map[i][j] == 'N' || g_file.map[i][j] == 'S' || g_file.map[i][j] == 'E' || g_file.map[i][j] == 'W')
        { 
          if (! g_myplayer.x && !g_myplayer.y )
          {
            g_myplayer.x = tx;
            g_myplayer.y = ty;
          }
          ft_drw_player(g_file.map[i][j]);
        };
      
      j++;
    } 
    i++;
  }
}