/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 20:37:11 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/23 18:23:27 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_file_data(char *line)
{
	int i;

	i = 0;
	if (ft_isalpha(ft_strtrim(line, " ")[0]))
	{
		ft_get_handle(ft_strtrim(line, " "));
		i++;
	}
	return (i);
}

void	ft_openfile(char *r_file)
{
	int			fd;
	static int	map_count;
	char		*line;
	int			i;

	i = 0;
	fd = open(r_file, O_RDONLY);
	while ((get_next_line(fd, &line)))
	{
		i += ft_file_data(line);
		if (((line[0] == ' ' && ft_strtrim(line, " ")[0] == '\0')))
			ft_error("Error\nOne Or more Empty Lines in The File!");
		if (ft_isalnum(ft_strtrim(line, " ")[0]))
		{
			if (i != 8)
				ft_error("Error\nWrong Data Order!");
			map_count++;
		}
		// free(line);
		// line = NULL;
	}
	if (ft_isdigit(ft_strtrim(line, " ")[0]) && map_count++ && i++)
		free(line);
	close(fd);
	if (i != 9)
		ft_error("Error\nFile Error\n");
	ft_map_handle(r_file, map_count);
}

int		ft_close(int key)
{
	exit(0);
	return (key);
}

int		main(int ac, char **av)
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
		ft_map();
		get_data_textures();
		check(0);
		mlx_hook(g_mymlx.win_ptr, 2, 1L << 0, check, 0);
		if (!g_bmp)
			mlx_hook(g_mymlx.win_ptr, 17, 0, ft_close, (void *)0);
		mlx_loop(g_mymlx.mlx_ptr);
	}
	else if (ac > 3)
		perror("ERORR\nYou've Entereed More then one Arguments\n");
	else
		perror("Error\nNo map file Provided.\n");
	return (0);
}
