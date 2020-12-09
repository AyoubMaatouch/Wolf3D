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

void ft_init(void)
{
	g_myplayer.turnDirection = 0; // -1 left && +1 right
	g_myplayer.walkDirection = 0; // -1 down && +1 up
	g_myplayer.move_speed = 25;
	g_myplayer.sidewalk = 0;
	g_myplayer.radius = 5;
	g_myplayer.rotation_speed = 2.5 * (M_PI / 180);
	
}
void 		ft_init_mlx()
{
	g_mymlx.mlx_ptr = mlx_init();
	g_mymlx.win_ptr = mlx_new_window(g_mymlx.mlx_ptr, g_file.width_resolution, g_file.height_resolution, "cub3D");
	g_data.img = mlx_new_image(g_mymlx.mlx_ptr, g_file.width_resolution, g_file.height_resolution);
	g_data.addr = mlx_get_data_addr(g_data.img, &g_data.bits_per_pixel, &g_data.line_length, &g_data.endian);
}

void update()
{
	g_myplayer.rotationAngle += g_myplayer.turnDirection * g_myplayer.rotation_speed;

	float x = cos(g_myplayer.rotationAngle) * (g_myplayer.move_speed * g_myplayer.walkDirection);
	float y = sin(g_myplayer.rotationAngle) * (g_myplayer.move_speed * g_myplayer.walkDirection);
	if (g_myplayer.sidewalk != 0)
		{
			x = cos(g_myplayer.rotationAngle + d2r(90 * g_myplayer.sidewalk))  * g_myplayer.move_speed;
			y = sin(g_myplayer.rotationAngle + d2r(90 * g_myplayer.sidewalk)) *  g_myplayer.move_speed ;
		}
	if (iswall(g_myplayer.x + x, g_myplayer.y + y) != 1)
	{
		g_myplayer.x += x;
		g_myplayer.y += y;
	}

	g_myplayer.turnDirection = 0;
	g_myplayer.walkDirection = 0;
	g_myplayer.sidewalk = 0;
}
int ft_key_input(int key)
{
	if (key == UP || key == UP_l)
		g_myplayer.walkDirection = 1;
	if (key == DOWN || key == DOWN_l)
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
void get_data_textures ()
{
	/*********************************
  * *    	Tesitng Textures		 *
  **********************************/
    int bbp;
    int size, end;
  
	g_txt[0].img = mlx_xpm_file_to_image(g_mymlx.mlx_ptr, g_file.so_t, &g_txt[0].img_width, &g_txt[0].img_height);
	g_txt[0].data = (int*)mlx_get_data_addr(g_txt[0].img,&bbp, &size, &end ); 
	g_txt[1].img = mlx_xpm_file_to_image(g_mymlx.mlx_ptr,g_file.no_t, &g_txt[1].img_width, &g_txt[1].img_height);
	g_txt[1].data = (int*)mlx_get_data_addr(g_txt[1].img,&bbp, &size, &end ); 
	g_txt[2].img = mlx_xpm_file_to_image(g_mymlx.mlx_ptr, g_file.ea_t, &g_txt[2].img_width, &g_txt[2].img_height);
	g_txt[2].data = (int*)mlx_get_data_addr(g_txt[2].img,&bbp, &size, &end ); 
	g_txt[3].img = mlx_xpm_file_to_image(g_mymlx.mlx_ptr, g_file.we_t, &g_txt[3].img_width, &g_txt[3].img_height);
	g_txt[3].data = (int*)mlx_get_data_addr(g_txt[3].img,&bbp, &size, &end ); 	
}
int check()
{
	/**************************/
	get_data_textures();
	/****************************/
	mlx_hook(g_mymlx.win_ptr, 2, 1L << 0, ft_key_input, (void *)0);
	/*********
	 * The looping Functions
	 * *********/
	update();
	ft_map();
	cast_rays();
	/**************************************************************/
	mlx_clear_window(g_mymlx.mlx_ptr, g_mymlx.win_ptr);
	mlx_put_image_to_window(g_mymlx.mlx_ptr, g_mymlx.win_ptr, g_data.img, 0, 0);
	mlx_destroy_image(g_mymlx.mlx_ptr, g_data.img);
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
	if (i != 9 )
		{
			ft_putstr("Error\nFile Error\n");
			exit(0);
		}
	ft_map_handle(r_file, map_count);
}

int main(int ac, char **av)
{
	if (ac == 2 || ac == 3)
	{
		ft_map_arg_check(av[1]);
		if (ac == 3)
			ft_save_arg_check(av[2]);
		ft_init();
		ft_openfile(av[1]);
		ft_init_mlx();
		mlx_loop_hook(g_mymlx.mlx_ptr, check, 0);
		mlx_loop(g_mymlx.mlx_ptr);
		
	}
	else if (ac > 3)
			perror("ERORR\nYou've Entereed More then one Arguments.\n Please Try Again");
		else 
			perror("Error\nNo map file Provided.\n");
		
	return (0);
}