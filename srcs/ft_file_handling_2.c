/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_handling_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymaatou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:22:32 by aymaatou          #+#    #+#             */
/*   Updated: 2021/01/06 12:22:34 by aymaatou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_map_char(char c)
{
	if (c != '0' && c != '1' && c != '2' && c != ' ' &&
	c != 'N' && c != 'S' && c != 'E' && c != 'W')
	{
		ft_error("Error\nCheck Your Map!");
	}
}

void	ft_check_con(void)
{
	int i;
	int j;

	i = 0;
	while (i < g_file.hight)
	{
		j = 0;
		while (j < (int)ft_strlen(g_file.map[i]))
		{
			ft_map_char(g_file.map[i][j]);
			j++;
		}
		i++;
	}
}
