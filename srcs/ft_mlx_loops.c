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
		{
			g_myplayer.look += 20;
			if ( g_myplayer.look > 800)
				g_myplayer.look = 800;

		}
	if (key == UP_l)
		g_myplayer.walkDirection = 1;
	if (key == DOWN)
		{
			g_myplayer.look -= 20;
			if ( g_myplayer.look < -800)
				g_myplayer.look = -800;
		}
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


