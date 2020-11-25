/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:03:12 by aymaatou          #+#    #+#             */
/*   Updated: 2020/11/25 18:31:15 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
        circle (g_myplayer.x, g_myplayer.y);
      
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
          g_myplayer.x = tx;
          g_myplayer.y = ty;
          ft_drw_player(g_file.map[i][j]);
        };
      
      j++;
    } 
    i++;
  }
}