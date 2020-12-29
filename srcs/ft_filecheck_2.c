/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filecheck_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:44:57 by aymaatou          #+#    #+#             */
/*   Updated: 2020/12/26 14:44:59 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_get_resolution(int hight, int width)
{
	int sizex;
	int sizey;

	mlx_get_screen_size(g_mymlx.mlx_ptr, &sizex, &sizey);
	g_file.height_resolution = hight;
	if (hight <= 0 || width <= 0)
		ft_error("Error\nYour Resolution Value Sould be more then 10!");
	if (hight < 10 || width < 10)
		ft_error("Error\nYour Resolution Value Sould be more then 10!");
	if (hight > sizey)
		g_file.height_resolution = sizey;
	else
		g_file.height_resolution = hight;
	if (width > sizex)
		g_file.width_resolution = sizex;
	else
		g_file.width_resolution = width;
}

void	ft_get_texture(char c, char *value)
{
	if (c == 'N')
		if (g_file.no_t)
			ft_error("Error\nDuplicated 'NO' Texture File\n");
		else
			g_file.no_t = value;
	else if (c == 'W')
		if (g_file.we_t)
			ft_error("Error\nDuplicated 'WE' Texture File\n");
		else
			g_file.we_t = value;
	else if (c == 'E')
		if (g_file.ea_t)
			ft_error("Error\nDuplicated 'EA' Texture File\n");
		else
			g_file.ea_t = value;
	else
	{
		if (g_file.so_t)
			ft_error("Error\nDuplicated 'SO' Texture File\n");
		else
			g_file.so_t = value;
	}
}

void	ft_get_sprit(char *value)
{
	if (g_file.sprit)
		ft_error("Error\nDuplicated 'Sprite' File\n");
	g_file.sprit = value;
}

char	*ft_c(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			ft_error("Error\nPlease Check Your Resolution input!");
		i++;
	}
	return (str);
}
