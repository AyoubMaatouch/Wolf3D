/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 03:49:16 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/19 03:49:18 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_init(void)
{
	g_myplayer.turnDirection = 0;
	g_myplayer.walkDirection = 0;
	g_myplayer.move_speed = 25;
	g_myplayer.sidewalk = 0;
	g_myplayer.radius = 5;
	g_myplayer.rotation_speed = 2.5 * (M_PI / 180);
	g_myplayer.look = 0;
}

void	update(void)
{
	float x;
	float y;

	g_myplayer.rotationAngle += g_myplayer.turnDirection
		* g_myplayer.rotation_speed;
	x = cos(g_myplayer.rotationAngle) *
		(g_myplayer.move_speed * g_myplayer.walkDirection);
	y = sin(g_myplayer.rotationAngle) * (g_myplayer.move_speed
		* g_myplayer.walkDirection);
	if (g_myplayer.sidewalk != 0)
	{
		x = cos(g_myplayer.rotationAngle + d2r(90 * g_myplayer.sidewalk))
			* g_myplayer.move_speed;
		y = sin(g_myplayer.rotationAngle + d2r(90 * g_myplayer.sidewalk))
			* g_myplayer.move_speed;
	}
	if (iswall(g_myplayer.x + x, g_myplayer.y + y) != 1 &&
	iswall(g_myplayer.x + x, g_myplayer.y + y) != 2)
	{
		g_myplayer.x += x;
		g_myplayer.y += y;
	}
	g_myplayer.turnDirection = 0;
	g_myplayer.walkDirection = 0;
	g_myplayer.sidewalk = 0;
}

void	get_data_textures(void)
{
	int bbp;
	int size;
	int end;

	g_txt[0].img = mlx_xpm_file_to_image(g_mymlx.mlx_ptr, g_file.so_t,
		&g_txt[0].img_width, &g_txt[0].img_height);
	if (!g_txt[0].img)
		ft_error("Error\n'SO' file texture is correpted Or Not Found!");
	g_txt[0].data = (int *)mlx_get_data_addr(g_txt[0].img,
		&bbp, &size, &end);
	g_txt[1].img = mlx_xpm_file_to_image(g_mymlx.mlx_ptr, g_file.no_t,
		&g_txt[1].img_width, &g_txt[1].img_height);
	if (!g_txt[1].img)
		ft_error("Error\n'NO' file texture is correpted Or Not Found!");
	g_txt[1].data = (int *)mlx_get_data_addr(g_txt[1].img, &bbp, &size, &end);
	g_txt[2].img = mlx_xpm_file_to_image(g_mymlx.mlx_ptr, g_file.ea_t,
	&g_txt[2].img_width, &g_txt[2].img_height);
	if (!g_txt[2].img)
		ft_error("Error\n'EA' file texture is correpted Or Not Found!");
	g_txt[2].data = (int *)mlx_get_data_addr(g_txt[2].img, &bbp, &size, &end);
	ft_get_data_textures_2();
}

void	ft_get_data_textures_2(void)
{
	int bbp;
	int size;
	int end;

	g_txt[3].img = mlx_xpm_file_to_image(g_mymlx.mlx_ptr, g_file.we_t,
		&g_txt[3].img_width, &g_txt[3].img_height);
	if (!g_txt[3].img)
		ft_error("Error\n'WE' file texture is correpted Or Not Found!");
	g_txt[3].data = (int *)mlx_get_data_addr(g_txt[3].img, &bbp, &size, &end);
	g_txt[4].img = mlx_xpm_file_to_image(g_mymlx.mlx_ptr,
		g_file.sprit, &g_txt[4].img_width, &g_txt[4].img_height);
	if (!g_txt[4].img)
		ft_error("Error\n'WE' file texture is correpted Or Not Found!");
	g_txt[4].data = (int *)mlx_get_data_addr(g_txt[4].img, &bbp, &size, &end);
}
