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

void	ft_sp_data (int i)
{
	/*
	*	Preparing sprite data for drawing the wall
	*/
	///g_sprite[i].dis = ft_distance_between (g_myplayer.x, g_sprite[i].x, g_myplayer.y, g_sprite[i].y);
	float angle = atan2(g_sprite[i].y - g_myplayer.y, g_sprite[i].x - g_myplayer.x);
	while (angle - g_myplayer.rotationAngle > M_PI)
		angle -= 2 * M_PI;
	while (angle - g_myplayer.rotationAngle < -M_PI)
		angle += 2 * M_PI;
	angle = angle - g_myplayer.rotationAngle;
	
	if (g_file.height_resolution > g_file.width_resolution)
		g_sprite[i].size = (g_file.height_resolution / g_sprite[i].dis) * TILE;
	else
		g_sprite[i].size = (g_file.width_resolution / g_sprite[i].dis) * TILE;
	
	
	
	//float cor_dis = g_sprite[i].dis * cos(angle);
    // float pr = (g_file.width_resolution / 2) / tan(d2r(30));
    // g_sprite[i].size = (TILE / cor_dis) * pr;


   	g_sprite[i].y_off = (g_file.height_resolution / 2) - (g_sprite[i].size / 2);
    g_sprite[i].x_off = ((angle * g_file.width_resolution) / d2r(60)) + ((g_file.width_resolution / 2) - (g_sprite[i].size / 2)); //g_sprite[i].start + (int)g_sprite[i].size;	
}


/**************************
 * 
 * *********************/

void	sprite_put_pixels(int id, int i, int j)
{
	int *add;
	int color;

	add = g_txt[4].data;
	color = add[((int)g_txt[4].img_width * (j * (int)g_txt[4].img_height /(int)g_sprite[id].size)) + (i * (int)g_txt[4].img_width / (int)g_sprite[id].size)];
	if (color != 0)
	{
		my_mlx_pixel_put(&g_data, g_sprite[id].x_off + i, g_sprite[id].y_off + j, color);
	}
}

void	draw_sprite(int id)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < g_sprite[id].size - 1)
	{
		if (g_sprite[id].x_off + i < 0 || g_sprite[id].x_off + i > g_file.width_resolution)
			continue;
		if (g_sprite[id].dis > g_ray[(int)g_sprite[id].x_off + i].distance)
			continue;
		j = -1;
		while (++j < g_sprite[id].size - 1)
		{
			if (g_sprite[id].y + j < 0 || g_sprite[id].y_off + j > g_file.height_resolution)
				continue;
			sprite_put_pixels(id, i, j);
		}
	}
	
}   