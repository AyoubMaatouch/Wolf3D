/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:37:11 by aymaatou          #+#    #+#             */
/*   Updated: 2020/11/25 12:08:57 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void update(int key)
{

}
int ft_key_input(int key)
{
   // printf ("[%d]]\n", key);
   update(key);
   
    return key;
}

int check()
{
	
	mlx_hook(g_mymlx.win_ptr, 2, 1L << 0, ft_key_input, (void *)0);  
	/*********
	 * put here the hooked fuctions
	 * *********/
	ft_map();
	
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