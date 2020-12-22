/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:03:12 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/08 18:54:35 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void df_player_angle(char position)
{
  g_myplayer.ishere += 1;
  if (g_myplayer.ishere > 1)
        ft_error("Error\nMORE THEN ONE PLAYER IN MAP");
  if (g_myplayer.ishere == 1)
    {if (position == 'N')
      g_myplayer.rotationAngle = 270.0 * (M_PI / 180);
    if (position == 'S')
      g_myplayer.rotationAngle = 90.0 * (M_PI / 180);
    if (position == 'E')
      g_myplayer.rotationAngle = 0.0 * (M_PI / 180);
    if (position == 'W')
      g_myplayer.rotationAngle = 180.0 * (M_PI / 180);
      }
      
      
}
void ft_map()
{
  ft_map_error_check();

  int i;
  size_t j;

  i = 0;
  g_sp_index = 0;
  while (i < g_file.hight)
  {
    j = 0;
    while (j < ft_strlen(g_file.map[i]))
    {
      int tx = j * TILE + TILE / 2;
      int ty = i * TILE + TILE / 2;
     
      if (iswall(tx, ty) == 2)
          ft_get_sp_pos(tx, ty, g_sp_index++);
      if (g_file.map[i][j] == 'N' || g_file.map[i][j] == 'S' || g_file.map[i][j] == 'E' || g_file.map[i][j] == 'W')
      {
        df_player_angle(g_file.map[i][j]);
        if (!g_myplayer.x && !g_myplayer.y)
        {
          g_myplayer.x = tx;
          g_myplayer.y = ty;
        }
        g_file.map[i][j] = '0';
      };
      j++;
    }
    i++;
  }
  if (g_myplayer.ishere == 0)
       ft_error("Error\nNO PLAYER IN MAP");
//sort();
}