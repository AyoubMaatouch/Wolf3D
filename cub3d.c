/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:37:11 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/02 06:05:00 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_init (void)
{
	g_myplayer.turnDirection = 0;   // -1 left && +1 right
	g_myplayer.walkDirection = 0;  // -1 down && +1 up
	g_myplayer.move_speed = 50;
	g_myplayer.radius = 3;
	//g_myplayer.rotationAngle = 2 * M_PI;
	g_myplayer.rotation_speed = 2 * (M_PI / 180);
	
}
void update()
{
	g_myplayer.rotationAngle += g_myplayer.turnDirection * g_myplayer.rotation_speed;
	
	float x = cos(g_myplayer.rotationAngle) * (g_myplayer.move_speed * g_myplayer.walkDirection);
	float y = sin(g_myplayer.rotationAngle) * (g_myplayer.move_speed * g_myplayer.walkDirection);
	
	if (iswall(g_myplayer.x + x, g_myplayer.y + y) != 1)
	{
		g_myplayer.x += x;
		g_myplayer.y += y;
	}
 
	g_myplayer.turnDirection = 0;
	g_myplayer.walkDirection = 0;
	

}
int ft_key_input(int key)
{
    //printf ("[%d]]\n", key);
	if (key == UP || key == UP_l)
		g_myplayer.walkDirection = 1;
	if (key == DOWN || key == DOWN_l)
		g_myplayer.walkDirection = -1;
	if (key == RIGHT || key == RIGHT_l)
		g_myplayer.turnDirection = -1;
	if (key == LEFT || key == LEFT_l)
		g_myplayer.turnDirection = 1;
	if (key == 53)
		exit(0);
   //update();
   //ft_map();
   
    return key;
}

int check()
{
	
	mlx_hook(g_mymlx.win_ptr, 2, 1L << 0, ft_key_input, (void *)0);  
	/*********
	 * put here the hooked fuctions
	 * *********/
	update();
	ft_map();
	//ft_drw_player();
	cast_rays();
	//ft_map();

	/***********************/
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
	while ((get_next_line(fd, &line)))
	{
		if (ft_isalpha(ft_strtrim(line, " ")[0]))
			ft_get_handle(ft_strtrim(line, " "));
		if (ft_isalnum(ft_strtrim(line, " ")[0]))
			map_count++;
	}
	if (ft_isdigit(ft_strtrim(line, " ")[0]))
		map_count++;
	free(line);
	close(fd);
	ft_map_handle(r_file, map_count);
}

int main(int ac, char **av)
{
    if (ac == 2)
    {
		ft_init ();
        ft_openfile(av[1]);
        g_mymlx.mlx_ptr = mlx_init();
        g_mymlx.win_ptr = mlx_new_window(g_mymlx.mlx_ptr, g_file.width_resolution, g_file.height_resolution, av[1]);
        g_data.img = mlx_new_image(g_mymlx.mlx_ptr, g_file.width_resolution, g_file.height_resolution);
        g_data.addr = mlx_get_data_addr(g_data.img, &g_data.bits_per_pixel, &g_data.line_length, &g_data.endian);
        mlx_loop_hook(g_mymlx.mlx_ptr, check, 0);
        mlx_loop(g_mymlx.mlx_ptr);
        return (0);
    }
}