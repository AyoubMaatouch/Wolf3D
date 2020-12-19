/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_loops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 03:51:27 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/19 03:51:47 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int ft_key_input(int key)
{
	if (key == UP)
		g_myplayer.look += 20;
	if (key == UP_l)
		g_myplayer.walkDirection = 1;
	if (key == DOWN)
		g_myplayer.look -= 20;
	if (key == DOWN_l)
		g_myplayer.walkDirection = -1;
	if (key == RIGHT)
		g_myplayer.turnDirection = -1;
	if (key == LEFT)
		g_myplayer.turnDirection = 1;
	if (key == LEFT_l)
		g_myplayer.sidewalk = 1;
	if (key == RIGHT_l)
		g_myplayer.sidewalk = -1;
	if (key == 53)
		exit(0);
	return key;
}

int ft_mouse(int x, int key, int y)
{
	if (x > 0 && x < g_file.width_resolution && key > 0 && key < g_file.height_resolution)
	{
		if (x > g_file.width_resolution / 2)
			g_myplayer.turnDirection = 1;
		if (x < g_file.width_resolution / 2)
			g_myplayer.turnDirection = -1;
	}
	return (y);
}

int check()
{
	/**************************/
	get_data_textures();
	/****************************/

	//mlx_mouse_move(g_mymlx.win_ptr, xx, y);
	//mlx_mouse_get_pos( g_mymlx.win_ptr , &xx, &y );

	mlx_hook(g_mymlx.win_ptr, 6, (1L << 6), ft_mouse, (void *)0);
	if (!g_bmp)
		mlx_hook(g_mymlx.win_ptr, 2, 1L << 0, ft_key_input, (void *)0);
	/*********
	 * The looping Functions
	 * *********/
	ft_map();
	update();

	cast_rays();
	if (g_bmp)
		creat_screenshot();
	/**************************************************************/

	if (!g_bmp)
	{
		mlx_clear_window(g_mymlx.mlx_ptr, g_mymlx.win_ptr);
		mlx_put_image_to_window(g_mymlx.mlx_ptr, g_mymlx.win_ptr, g_data.img, 0, 0);
		mlx_destroy_image(g_mymlx.mlx_ptr, g_data.img);
	}
	g_data.img = mlx_new_image(g_mymlx.mlx_ptr, g_file.width_resolution, g_file.height_resolution);
	g_data.addr = mlx_get_data_addr(g_data.img, &g_data.bits_per_pixel, &g_data.line_length, &g_data.endian);

	return (0);
}
