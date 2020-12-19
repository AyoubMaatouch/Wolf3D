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

int main(int ac, char **av)
{
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
		mlx_loop(g_mymlx.mlx_ptr);
	}
	else if (ac > 3)
		perror("ERORR\nYou've Entereed More then one Arguments.\n Please Try Again");
	else
		perror("Error\nNo map file Provided.\n");
	return (0);
}