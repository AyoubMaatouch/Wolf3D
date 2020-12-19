/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:37:11 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/08 18:16:38 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_init_mlx(void)
{
	g_mymlx.mlx_ptr = mlx_init();
	if (!g_bmp)
		g_mymlx.win_ptr = mlx_new_window(g_mymlx.mlx_ptr, g_file.width_resolution, g_file.height_resolution, "cub3D");
	g_data.img = mlx_new_image(g_mymlx.mlx_ptr, g_file.width_resolution, g_file.height_resolution);
	g_data.addr = mlx_get_data_addr(g_data.img, &g_data.bits_per_pixel, &g_data.line_length, &g_data.endian);
}

int check()
{
	/**************************/
	get_data_textures();
	/****************************/

	//mlx_mouse_move(g_mymlx.win_ptr, xx, y);
	//mlx_mouse_get_pos( g_mymlx.win_ptr , &xx, &y );

	
	if (!g_bmp)
		{
			
			mlx_hook(g_mymlx.win_ptr, 2, 1L << 0, ft_key_input, (void *)0);
			mlx_hook(g_mymlx.win_ptr, 6, (1L << 6), ft_mouse, (void *)0);
			
		}
	
	/*********
	 * The looping Functions
	 * *********/
	ft_map();
	update();

	cast_rays();
	
	/**************************************************************/

	if (!g_bmp)
	{
		mlx_clear_window(g_mymlx.mlx_ptr, g_mymlx.win_ptr);
		mlx_put_image_to_window(g_mymlx.mlx_ptr, g_mymlx.win_ptr, g_data.img, 0, 0);
		mlx_destroy_image(g_mymlx.mlx_ptr, g_data.img);
	}
	if (g_bmp)
		ft_create_screenshot();
	g_data.img = mlx_new_image(g_mymlx.mlx_ptr, g_file.width_resolution, g_file.height_resolution);
	g_data.addr = mlx_get_data_addr(g_data.img, &g_data.bits_per_pixel, &g_data.line_length, &g_data.endian);

	return (0);
}


void ft_openfile(char *r_file)
{
	int fd = open(r_file, O_RDONLY);
	static int map_count;
	char *line;

	int i = 0;
	while ((get_next_line(fd, &line)))
	{
		if (ft_isalpha(ft_strtrim(line, " ")[0]))
		{
			ft_get_handle(ft_strtrim(line, " "));
			i++;
		}
		if (ft_isalnum(ft_strtrim(line, " ")[0]))
			map_count++;
	}
	if (ft_isdigit(ft_strtrim(line, " ")[0]))
	{
		map_count++;
		i++;
	}
	free(line);
	close(fd);
	if (i != 9)
	{
		ft_putstr("Error\nFile Error\n");
		exit(0);
	}
	ft_map_handle(r_file, map_count);
}
int ft_close (int key)
{
	exit(0);
	return (key);
}

int main(int ac, char **av)
{
	g_bmp = 0;
	if (ac == 2 || ac == 3)
	{
		ft_map_arg_check(av[1]);
		
		if (ac == 3)
		{
			ft_save_arg_check(av[2]);
			g_bmp = 1;
		}
		ft_init();
		ft_openfile(av[1]);
		ft_init_mlx();
		mlx_loop_hook(g_mymlx.mlx_ptr, check, 0);
		if (!g_bmp)
			mlx_hook(g_mymlx.win_ptr, 17, 0, ft_close, (void *)0);
		mlx_loop(g_mymlx.mlx_ptr);
	}
	else if (ac > 3)
		perror("ERORR\nYou've Entereed More then one Arguments.\n Please Try Again");
	else
		perror("Error\nNo map file Provided.\n");
	return (0);
}