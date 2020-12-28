/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filecheck.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <aymaatou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:49:26 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/08 18:54:17 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_check_color(char *value)
{
	int i;
	int check;

	i = 0;
	check = 0;
	while (value[i])
	{
		if (!ft_isdigit(value[i]) && value[i] != ',')
			ft_error("Error\nWrong 'C' or 'F' Color Value!");
		if (value[i] == ',')
			check++;
		i++;
	}
	if (check != 2)
		ft_error("Error\nWrong 'C' or 'F' Color Value!");
}

void	ft_get_cf(char c, char *value)
{
	int		r;
	int		g;
	int		b;
	char	**temp;

	ft_check_color(value);
	r = 0;
	g = 0;
	b = 0;
	temp = ft_split(value, ',');
	r = ft_atoi(temp[0]);
	g = ft_atoi(temp[1]);
	b = ft_atoi(temp[2]);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		ft_error("Error\n Wrong 'C' 'F' color value");
	if (c == 'F')
		g_file.flor = 65536 * r + 256 * g + b;
	else
		g_file.cilng = 65536 * r + 256 * g + b;
}

void	ft_sprite_info(char *g_value, char **temp)
{
	if (g_value[1] != ' ' || temp[2])
		ft_error("Error\nPlease Check Your Sprite input!");
	ft_get_sprit(temp[1]);
}

void	ft_get_handle(char *g_value)
{
	char **temp;

	temp = ft_split(g_value, ' ');
	if (!ft_memcmp(g_value, "R", 1))
	{
		if (g_value[1] != ' ' || temp[3])
			ft_error("Error\nPlease Check Your Resolution input!");
		ft_get_resolution(ft_atoi(temp[2]), ft_atoi(temp[1]));
	}
	else if (!ft_memcmp(g_value, "WE", 2) || !ft_memcmp(g_value, "NO", 2)
		|| !ft_memcmp(g_value, "SO", 2) || !ft_memcmp(g_value, "EA", 2))
	{
		if (g_value[2] != ' ' || temp[2])
			ft_error("Error\nPlease Check Your Texture input!");
		ft_get_texture(g_value[0], temp[1]);
	}
	else if (g_value[0] == 'F' || g_value[0] == 'C')
	{
		if (g_value[1] != ' ' || temp[2])
			ft_error("Error\nPlease Check Your 'C' or 'F' input!");
		ft_get_cf(g_value[0], temp[1]);
	}
	else if (!ft_memcmp(g_value, "S", 1))
		ft_sprite_info(g_value, temp);
	free(temp);
}

void	ft_map_handle(char *r_file, int map_size)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(r_file, O_RDONLY);
	i = 0;
	g_file.hight = map_size;
	g_file.map = malloc(sizeof(char *) * (map_size + 1));
	g_file.map[map_size] = NULL;
	while ((get_next_line(fd, &line)))
	{
		if (!g_file.width || g_file.width < (int)ft_strlen(line))
			g_file.width = (int)ft_strlen(line);
		if (ft_isdigit(ft_strtrim(line, " ")[0]))
		{
			g_file.map[i] = ft_strdup(line);
			i++;
		}
		free(line);
	}
	if (ft_isdigit(ft_strtrim(line, " ")[0]))
		g_file.map[i] = ft_strdup(line);
	free(line);
}
