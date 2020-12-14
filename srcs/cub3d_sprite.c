/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:49:03 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/12 20:49:04 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
/*
    getting x, y hits and calculating the distance from player to sprite,
    then sorting them according to the farthest to the closest one.
    after you that DRAW  
*/


// void ft_sprite_data(int i)
// {
//     float correct_dis = g_sprit.sprit_dis * cos(g_ray[i].ray_angle - g_myplayer.rotationAngle);
//     float projection = (g_file.width_resolution / 2) / tan(d2r(30));
//     float wallHeight = (TILE / correct_dis) * projection;
//     int top = (g_file.height_resolution / 2) - ((int)wallHeight / 2);
//     int bottom = top + (int)wallHeight;

// }
void	sort(void)
{
	int			i;
	int			j;
	t_sprite_info	tmp;

	i = -1;
	while (++i < g_sp_index)
	{
		j = -1;
		while (++j < g_sp_index - i)
		{
			if (g_sprite[j].dis < g_sprite[j + 1].dis)
			{
				tmp = g_sprite[j];
				g_sprite[j] = g_sprite[j + 1];
				g_sprite[j + 1] = tmp;
			}
		}
	}
}
void    ft_get_sp_pos(float x, float y, int i)
{
    /*
    * sprite x, y Position 
    */
    g_sprite[i].x = x;
    g_sprite[i].y = y;

    /*
    * Getting RAW distance
    */
    g_sprite[i].dis = ft_distance_between (g_myplayer.x, g_sprite[i].x, g_myplayer.y, g_sprite[i].y);
    
}


